// #include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "TestCppClient.h"

using namespace std;

// TODO: Connect to API and get the price of something
const unsigned MAX_ATTEMPTS = 10;
const unsigned SLEEP_TIME = 10;
int main()
{
    const char* host = "127.0.0.1";
    int port = 7496;
    int client_id = 0;
    // const char* connectOptions = "";
    unsigned attempts = 0;
    printf("Start of C++ Socket Client Paper\n");
    TestCppClient client;
    while(attempts < 5)
    {
        client.connect(host, port, client_id);
        if(client.isConnected())
            break;
        printf("Sleeping %u seconds before next attempt\n", SLEEP_TIME);
        this_thread::sleep_for(chrono::seconds(SLEEP_TIME));
        attempts++;
    }
    if(client.isConnected())
    {
        for(;;)
        {
            client.processMessages();
        } 
    }
    printf("End of C++ Socket Client Test\n");
}