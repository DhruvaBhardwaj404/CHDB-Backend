#ifndef PARAMDEFINITIONS_H
#define PARAMDEFINITIONS_H

//Standard libraries
#include<vector>
#include<fstream>
#include<map>
#include<bitset>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<iostream>
#include<unistd.h>
#include<algorithm>
#include<unordered_map>
#include<functional>
#include<iomanip>
#include<ctype.h>
#include<cstdio>
#include<string>
#include<thread>
#include<memory>
#include<queue>
#include<future>
#include<atomic>
#include<list>
#include<mutex>
#include<ctime>
#include<tuple>
#include<unordered_map>




//Boost libraries
#include<asio.hpp>
#include<asio/ip/tcp.hpp>
#include<boost/interprocess/managed_shared_memory.hpp>
#include<boost/interprocess/mapped_region.hpp>

//MAIN
#define DEBUG_MAIN false
#define BIP boost::interprocess

//Connection Handler
#define DEBUG_CONN true
#define MAX_THREADS 5
#define MAX_PAC_SIZE 256
#define MAX_WAIT 10
#define MDB_FILENAME "MDB"
#define CON_HAN_PATH "~/CHDB/CHDATA"

//Alive Handler
#define MAX_THREADS 5
#define DEBUG_ALIVE true
#define MAX_MESS_SIZE 1024
#define AH_NUM_SOCK 5

//Query Parser
#define DEBUG_QUE true
#define QUERY_PATH "~/CHDB/data"

//shared memory
#define MAX_QUEUE_ALIQUE 16
#define MAX_QUEUE_CONALI 16
#define SHARED_MEM_SIZE_A2Q 2048
#define SHARED_MEM_SIZE_C2A 2048


#define SHARED_MEM_ALIQUE "AliQue"
#define SHARED_MEM_CONALI "ConAli"

#define ALIQUE_AQUEUE "AQ"
#define ALIQUE_QQUEUE "QQ"
#define ALIQUE_AMESSAGE_BUFFER "AMB"
#define ALIQUE_QMESSAGE_BUFFER "QMB"
#define ALIQUE_META "AM"
#define ALIQUE_MUTEX "AQMUT"

#define CONALI_CQUEUE "CQ"
#define CONALI_AQUEUE "AQ"
#define CONALI_CMESSAGE_BUFFER "CMB"
#define CONALI_AMESSAGE_BUFFER "AMB"
#define CONALI_META "CM"
#define CONALI_MUTEX "CAMUT"

//socket addresses and ports
#define SOCKET_ALIVE_IP "127.0.0.1"
#define SOCKET_ALIVE_PORT 5010
#define SOCKET_CONHAN_IP "127.0.0.1"
#define SOCKET_CONHAN_PORT  5009
#define SOCKET_QPAR_IP "127.0.0.1"
#define SOCKET_QPAR_PORT 5008

// shorthands for containers
#define VVPSS vector<vector<pair<string,string> > >

#endif // PARAMDEFINITIONS_H

