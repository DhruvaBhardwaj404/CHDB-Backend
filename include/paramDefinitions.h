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
#define DEBUG_MAIN true
#define BIP boost::interprocess

//Connection Handler
#define DEBUG_CONN true
#define MAX_THREADS 5
#define MAX_PAC_SIZE 256
#define MAX_WAIT 10

//Alive Handler
#define MAX_THREADS 5
#define DEBUG_ALIVE true

//Query Parser
#define DEBUG_QUE true

//DATABASE CLASS DEFINITIONS
#define MAX_DB_NAME 20
#define HASH_SIZE 3135

//FUNCTIONS DB CLASS

#define TYPE_SIZE 7

//HANDLER CLASS
#define MAX_COL_NAME 20

//COL HANDLER CLASS
#define MAX_TAB_NAME 20

//SQL CLASS DEFINTIONS
#define MAX_COL 100
#define MAX_RPP 4
#define MAX_SIZE_NAME 20
#define MAX_COL_NAME_SIZE 20

//NSQL CLASS DEFINTIONS
#define MAX_ATTR 100
#define MAX_SBS 1000
#define MAX_SIZE_NAME 20
#define MAX_COL_NAME_SIZE 20
#define SIZE_ATTR_NAME 20
#define SIZE_ATTR_INFO 1
#define SIZE_KEY 2
#define MAX_CHUNCKS 100
#define SIZE_FCHUNCKS 50
#define SIZE_SMALL_CHUNKS 25
#define SIZE_BIG_CHUNKS 100
#define SIZE_HEAD 1
#define SIZE_TAIL 3

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

#endif // PARAMDEFINITIONS_H

