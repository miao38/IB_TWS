CXX=g++
CXXFLAGS=-pthread -Wall -Wno-switch -Wpedantic -Wno-unused-function -std=c++11
ROOT_DIR=../source/cppclient
BASE_SRC_DIR=${ROOT_DIR}/client
INCLUDES=-I${BASE_SRC_DIR} -I${ROOT_DIR}
SHARD_LIBS=${BASE_SRC_DIR}/libTwsSocketClient.so
TARGET=Roy_IB_Client

$(TARGET):
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BASE_SRC_DIR)/*.cpp ./*.cpp $(BASE_SRC_DIR)/lib/libbid.so -o$(TARGET)

clean:
	rm -f $(TARGET) *.o