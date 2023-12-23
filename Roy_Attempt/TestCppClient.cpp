// #include "StdAfx.h"
#include "EClientSocket.h"
#include "EPosixClientSocketPlatform.h"
#include "TestCppClient.h"
#include "EClientSocket.h"
#include "Contract.h"
#include "Order.h"
#include "OrderState.h"
#include "Execution.h"
#include "CommissionReport.h"
// #include "ContractSamples.h"
// #include "OrderSamples.h"
// #include "ScannerSubscription.h"
// #include "ScannerSubscriptionSamples.h"
// #include "executioncondition.h"
// #include "PriceCondition.h"
// #include "MarginCondition.h"
// #include "PercentChangeCondition.h"
// #include "TimeCondition.h"
// #include "VolumeCondition.h"
// #include "AvailableAlgoParams.h"
// #include "FAMethodSamples.h"
// #include "CommonDefs.h"
// #include "AccountSummaryTags.h"
#include "Utils.h"

#include <stdio.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <ctime>
#include <fstream>
#include <cstdint>

TestCppClient::TestCppClient():
    m_osSignal(2000),
    m_pClient(new EClientSocket(this, &m_osSignal)),
    m_state(ST_CONNECT),
    m_sleepDeadline(0),
    m_orderId(0),
    m_extraAuth(false)
    {
    }

TestCppClient::~TestCppClient()
{
    // destroy the reader before teh client
    if(m_pReader)
        m_pReader.reset();
    delete m_pClient;
}

bool TestCppClient::connect(const char* host, int port, int client_id)
{
	printf( "Connecting to %s:%d clientId:%d\n", !( host && *host) ? "127.0.0.1" : host, port, client_id);
    bool bRes = m_pClient->eConnect(host, port, client_id, m_extraAuth);
    if(bRes)
    {
        printf( "Connected to %s:%d clientId:%d\n", m_pClient->host().c_str(), m_pClient->port(), client_id);
        m_pReader = unique_ptr<EReader>(new EReader(m_pClient, &m_osSignal));
        m_pReader->start();
    }
    else
        printf( "Cannot connect to %s:%d clientId:%d\n", m_pClient->host().c_str(), m_pClient->port(), client_id);
    return bRes;
}

void TestCppClient::disconnect() const
{
    m_pClient->eDisconnect();
    printf("Disconnected\n");
}

bool TestCppClient::isConnected() const
{
    return m_pClient->isConnected();
}

void TestCppClient::processMessages()
{
	// time_t now = time(NULL);

	/*****************************************************************/
    /* Below are few quick-to-test examples on the IB API functions grouped by functionality. Uncomment the relevant methods. */
    /*****************************************************************/
    Contract c;
    c.symbol = "AAPL";
    c.secType = "Stocks";
    c.exchange = "NASDAQ";
    std::cout << "req historic data" << endl;
    m_pClient->reqHistoricalData(1, c, "20231222 05:00:00", "1 M", "1 day", "MIDPOINT", 1, true, false, TagValueListSPtr());

	m_osSignal.waitForSignal();
	errno = 0;
    std::cout << "process message" << endl;
	m_pReader->processMsgs();
}

void TestCppClient::historicalData(TickerId reqId, const Bar& bar)
{
    std::cout << "high: " << bar.high << endl;
}

void TestCppClient::error(int id, int errorCode, const std::string& errorString, const std::string& advancedOrderRejectJson)
{
    std::cout << "Error id: " << id << "\nError code: " << errorCode << "\nError String: " << errorString << endl;
}