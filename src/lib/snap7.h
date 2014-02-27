/*=============================================================================|
|  PROJECT SNAP7                                                         1.2.0 |
|==============================================================================|
|  Copyright (C) 2013, 2014 Davide Nardella                                    |
|  All rights reserved.                                                        |
|==============================================================================|
|  SNAP7 is free software: you can redistribute it and/or modify               |
|  it under the terms of the Lesser GNU General Public License as published by |
|  the Free Software Foundation, either version 3 of the License, or           |
|  (at your option) any later version.                                         |
|                                                                              |
|  It means that you can distribute your commercial software linked with       |
|  SNAP7 without the requirement to distribute the source code of your         |
|  application and without the requirement that your application be itself     |
|  distributed under LGPL.                                                     |
|                                                                              |
|  SNAP7 is distributed in the hope that it will be useful,                    |
|  but WITHOUT ANY WARRANTY; without even the implied warranty of              |
|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               |
|  Lesser GNU General Public License for more details.                         |
|                                                                              |
|  You should have received a copy of the GNU General Public License and a     |
|  copy of Lesser GNU General Public License along with Snap7.                 |
|  If not, see  http://www.gnu.org/licenses/                                   |
|==============================================================================|
|                                                                              |
|  C/C++ Snap 7 classes/Imports definitions                                    |
|                                                                              |
|=============================================================================*/
#ifndef _snap7_h
#define _snap7_h
//---------------------------------------------------------------------------
// Platform detection
//---------------------------------------------------------------------------
#if defined (_WIN32)||defined(_WIN64)||defined(__WIN32__)||defined(__WINDOWS__)
# define OS_WINDOWS
#endif

// Visual Studio needs this to use the correct time_t size
#if defined (_WIN32) && !defined(_WIN64)
# define _USE_32BIT_TIME_T 
#endif

#if defined(unix) || defined(__unix__) || defined(__unix)
# define PLATFORM_UNIX
#endif

#if defined(__SVR4) || defined(__svr4__)
# define OS_SOLARIS
#endif

#if BSD>=0
# define OS_BSD
#endif

#if defined(__APPLE__)
# define OS_OSX
#endif

#if defined(PLATFORM_UNIX) || defined(OS_OSX)
# include <unistd.h>
# if defined(_POSIX_VERSION)
#   define POSIX
# endif
#endif

//---------------------------------------------------------------------------
// C++ Library
//---------------------------------------------------------------------------
#ifdef __cplusplus
#include <string>
#include <time.h>

// Visual C++ not C99 compliant (VS2008--)
#ifdef _MSC_VER
# if _MSC_VER >= 1600
#  include <stdint.h>  // VS2010++ have it 
# else
   typedef signed __int8     int8_t;
   typedef signed __int16    int16_t;
   typedef signed __int32    int32_t;
   typedef signed __int64    int64_t;
   typedef unsigned __int8   uint8_t;
   typedef unsigned __int16  uint16_t;
   typedef unsigned __int32  uint32_t;
   typedef unsigned __int64  uint64_t;
   #ifdef _WIN64
     typedef unsigned __int64  uintptr_t;
   #else
     typedef unsigned __int32  uintptr_t;
   #endif
# endif
#else
# include <stdint.h>
#endif

extern "C" {
#endif
//---------------------------------------------------------------------------
// C exact length types
//---------------------------------------------------------------------------
#ifndef __cplusplus

#ifdef OS_BSD
#  include <stdint.h>
#  include <time.h>
#endif

#ifdef OS_OSX
#  include <stdint.h>  
#  include <time.h>
#endif

#ifdef OS_SOLARIS
#  include <stdint.h>  
#  include <time.h>
#endif

#if defined(_UINTPTR_T_DEFINED)
#  include <stdint.h>
#  include <time.h>
#endif

#if !defined(_UINTPTR_T_DEFINED) && !defined(OS_SOLARIS) && !defined(OS_BSD) && !defined(OS_OSX)
  typedef unsigned char   uint8_t;  //  8 bit unsigned integer
  typedef unsigned short  uint16_t; // 16 bit unsigned integer
  typedef unsigned int    uint32_t; // 32 bit unsigned integer
  typedef unsigned long   uintptr_t;// 64 bit unsigned integer
#endif

#endif

#ifdef OS_WINDOWS
# define S7API __stdcall
#else
# define S7API
#endif

#pragma pack(1)
//******************************************************************************
//                                   COMMON
//******************************************************************************
// Exact length types regardless of platform/processor
typedef uint8_t    byte;
typedef uint16_t   word;
typedef uint32_t   longword;
typedef byte       *pbyte;
typedef word       *pword;
typedef uintptr_t  S7Object; // multi platform/processor object reference
                             // DON'T CONFUSE IT WITH AN OLE OBJECT, IT'S SIMPLY
                             // AN INTEGER VALUE (32 OR 64 BIT) USED AS HANDLE.

#ifndef __cplusplus
typedef struct
{
  int   tm_sec;
  int   tm_min;
  int   tm_hour;
  int   tm_mday;
  int   tm_mon;
  int   tm_year;
  int   tm_wday;
  int   tm_yday;
  int   tm_isdst;
}tm;

typedef int bool;
#define false 0;
#define true  1;
#endif

const int errLibInvalidParam;
const int errLibInvalidObject;

// CPU status
#define S7CpuStatusUnknown  0x00
#define S7CpuStatusRun      0x08
#define S7CpuStatusStop     0x04

// ISO Errors
extern const longword errIsoConnect; // Connection error
extern const longword errIsoDisconnect; // Disconnect error
extern const longword errIsoInvalidPDU; // Bad format
extern const longword errIsoInvalidDataSize; // Bad Datasize passed to send/recv buffer is invalid
extern const longword errIsoNullPointer; // Null passed as pointer
extern const longword errIsoShortPacket; // A short packet received
extern const longword errIsoTooManyFragments; // Too many packets without EoT flag
extern const longword errIsoPduOverflow; // The sum of fragments data exceded maximum packet size
extern const longword errIsoSendPacket; // An error occurred during send
extern const longword errIsoRecvPacket; // An error occurred during recv
extern const longword errIsoInvalidParams; // Invalid TSAP params
extern const longword errIsoResvd_1; // Unassigned
extern const longword errIsoResvd_2; // Unassigned
extern const longword errIsoResvd_3; // Unassigned
extern const longword errIsoResvd_4; // Unassigned

//------------------------------------------------------------------------------
//                                  PARAMS LIST            
//------------------------------------------------------------------------------
extern const int p_u16_LocalPort  	;
extern const int p_u16_RemotePort 	;
extern const int p_i32_PingTimeout	;
extern const int p_i32_SendTimeout;
extern const int p_i32_RecvTimeout;
extern const int p_i32_WorkInterval;
extern const int p_u16_SrcRef;
extern const int p_u16_DstRef;
extern const int p_u16_SrcTSap;
extern const int p_i32_PDURequest;
extern const int p_i32_MaxClients;
extern const int p_i32_BSendTimeout;
extern const int p_i32_BRecvTimeout;
extern const int p_u32_RecoveryTime;
extern const int p_u32_KeepAliveTime5;

// Client/Partner Job status 
extern const int JobComplete;
extern const int JobPending;

//******************************************************************************
//                                   CLIENT
//******************************************************************************

// Error codes
extern const longword errNegotiatingPDU;
extern const longword errCliInvalidParams;
extern const longword errCliJobPending;
extern const longword errCliTooManyItems;
extern const longword errCliInvalidWordLen;
extern const longword errCliPartialDataWritten;
extern const longword errCliSizeOverPDU;
extern const longword errCliInvalidPlcAnswer;
extern const longword errCliAddressOutOfRange;
extern const longword errCliInvalidTransportSize;
extern const longword errCliWriteDataSizeMismatch;
extern const longword errCliItemNotAvailable;
extern const longword errCliInvalidValue;
extern const longword errCliCannotStartPLC;
extern const longword errCliAlreadyRun;
extern const longword errCliCannotStopPLC;
extern const longword errCliCannotCopyRamToRom;
extern const longword errCliCannotCompress;
extern const longword errCliAlreadyStop;
extern const longword errCliFunNotAvailable;
extern const longword errCliUploadSequenceFailed;
extern const longword errCliInvalidDataSizeRecvd;
extern const longword errCliInvalidBlockType;
extern const longword errCliInvalidBlockNumber;
extern const longword errCliInvalidBlockSize;
extern const longword errCliDownloadSequenceFailed;
extern const longword errCliInsertRefused;
extern const longword errCliDeleteRefused;
extern const longword errCliNeedPassword;
extern const longword errCliInvalidPassword;
extern const longword errCliNoPasswordToSetOrClear;
extern const longword errCliJobTimeout;
extern const longword errCliPartialDataRead;
extern const longword errCliBufferTooSmall;
extern const longword errCliFunctionRefused;
extern const longword errCliDestroying;
extern const longword errCliInvalidParamNumber;
extern const longword errCliCannotChangeParam;

extern const int MaxVars; // Max vars that can be transferred with MultiRead/MultiWrite
 
// Client Connection Type
extern const word CONNTYPE_PG;  // Connect to the PLC as a PG
extern const word CONNTYPE_OP;  // Connect to the PLC as an OP
extern const word CONNTYPE_BASIC;  // Basic connection

// Area ID
extern const byte S7AreaPE;
extern const byte S7AreaPA;
extern const byte S7AreaMK;
extern const byte S7AreaDB;
extern const byte S7AreaCT;
extern const byte S7AreaTM;

// Word Length
extern const int S7WLBit;
extern const int S7WLByte;
extern const int S7WLWord;
extern const int S7WLDWord;
extern const int S7WLReal;
extern const int S7WLCounter;
extern const int S7WLTimer;

// Block type
extern const byte Block_OB;
extern const byte Block_DB;
extern const byte Block_SDB;
extern const byte Block_FC;
extern const byte Block_SFC;
extern const byte Block_FB;
extern const byte Block_SFB;

// Sub Block Type
extern const byte SubBlk_OB;
extern const byte SubBlk_DB;
extern const byte SubBlk_SDB;
extern const byte SubBlk_FC;
extern const byte SubBlk_SFC;
extern const byte SubBlk_FB;
extern const byte SubBlk_SFB;

// Block languages
extern const byte BlockLangAWL;
extern const byte BlockLangKOP;
extern const byte BlockLangFUP;
extern const byte BlockLangSCL;
extern const byte BlockLangDB;
extern const byte BlockLangGRAPH;

// Read/Write Multivars
typedef struct{
   int   Area;
   int   WordLen;
   int   Result;
   int   DBNumber;
   int   Start;
   int   Amount;
   void  *pdata;
} TS7DataItem, *PS7DataItem;

//typedef int TS7ResultItems[MaxVars];
//typedef TS7ResultItems *PS7ResultItems;

// List Blocks
typedef struct {
   int OBCount;
   int FBCount;
   int FCCount;
   int SFBCount;
   int SFCCount;
   int DBCount;
   int SDBCount;
} TS7BlocksList, *PS7BlocksList;

// Blocks info
typedef struct {
   int BlkType;    // Block Type (OB, DB) 
   int BlkNumber;  // Block number
   int BlkLang;    // Block Language
   int BlkFlags;   // Block flags
   int MC7Size;    // The real size in bytes
   int LoadSize;   // Load memory size
   int LocalData;  // Local data
   int SBBLength;  // SBB Length
   int CheckSum;   // Checksum
   int Version;    // Block version
   // Chars info
   char CodeDate[11]; // Code date
   char IntfDate[11]; // Interface date 
   char Author[9];    // Author
   char Family[9];    // Family
   char Header[9];    // Header
} TS7BlockInfo, *PS7BlockInfo;

typedef word TS7BlocksOfType[0x2000];
typedef TS7BlocksOfType *PS7BlocksOfType;

// Order code
typedef struct {
   char Code[21];
   byte V1;
   byte V2;
   byte V3;
} TS7OrderCode, *PS7OrderCode;

// CPU Info
typedef struct {
   char ModuleTypeName[33];
   char SerialNumber[25];
   char ASName[25];
   char Copyright[27];
   char ModuleName[25];
} TS7CpuInfo, *PS7CpuInfo;

// CP Info
typedef struct {
   int MaxPduLengt;
   int MaxConnections;
   int MaxMpiRate;
   int MaxBusRate;
} TS7CpInfo, *PS7CpInfo;

// See §33.1 of "System Software for S7-300/400 System and Standard Functions"
// and see SFC51 description too
typedef struct {
   word LENTHDR;
   word N_DR;
} SZL_HEADER, *PSZL_HEADER;

typedef struct {
   SZL_HEADER Header;
   byte Data[0x4000-4];
} TS7SZL, *PS7SZL;

// SZL List of available SZL IDs : same as SZL but List items are big-endian adjusted
typedef struct {
   SZL_HEADER Header;
   word List[0x2000-2];
} TS7SZLList, *PS7SZLList;

// See §33.19 of "System Software for S7-300/400 System and Standard Functions"
typedef struct {
   word  sch_schal;
   word  sch_par;
   word  sch_rel;
   word  bart_sch;
   word  anl_sch;
} TS7Protection, *PS7Protection;

// Client completion callback
typedef void (S7API *pfn_CliCompletion) (void *usrPtr, int opCode, int opResult);
//------------------------------------------------------------------------------
//  Import prototypes
//------------------------------------------------------------------------------
S7Object S7API Cli_Create();
void S7API Cli_Destroy(S7Object *Client);
int S7API Cli_ConnectTo(S7Object Client, const char *Address, int Rack, int Slot);
int S7API Cli_SetConnectionParams(S7Object Client, const char *Address, word LocalTSAP, word RemoteTSAP);
int S7API Cli_SetConnectionType(S7Object Client, word ConnectionType);
int S7API Cli_Connect(S7Object Client);
int S7API Cli_Disconnect(S7Object Client);
int S7API Cli_GetParam(S7Object Client, int ParamNumber, void *pValue);
int S7API Cli_SetParam(S7Object Client, int ParamNumber, void *pValue);
int S7API Cli_SetAsCallback(S7Object Client, pfn_CliCompletion pCompletion, void *usrPtr);
// Data I/O main functions
int S7API Cli_ReadArea(S7Object Client, int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
int S7API Cli_WriteArea(S7Object Client, int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
int S7API Cli_ReadMultiVars(S7Object Client, PS7DataItem Item, int ItemsCount);
int S7API Cli_WriteMultiVars(S7Object Client, PS7DataItem Item, int ItemsCount);
// Data I/O Lean functions
int S7API Cli_DBRead(S7Object Client, int DBNumber, int Start, int Size, void *pUsrData);
int S7API Cli_DBWrite(S7Object Client, int DBNumber, int Start, int Size, void *pUsrData);
int S7API Cli_MBRead(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_MBWrite(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_EBRead(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_EBWrite(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_ABRead(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_ABWrite(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_TMRead(S7Object Client, int Start, int Amount, void *pUsrData);
int S7API Cli_TMWrite(S7Object Client, int Start, int Amount, void *pUsrData);
int S7API Cli_CTRead(S7Object Client, int Start, int Amount, void *pUsrData);
int S7API Cli_CTWrite(S7Object Client, int Start, int Amount, void *pUsrData);
// Directory functions
int S7API Cli_ListBlocks(S7Object Client, TS7BlocksList *pUsrData);
int S7API Cli_GetAgBlockInfo(S7Object Client, int BlockType, int BlockNum, TS7BlockInfo *pUsrData);
int S7API Cli_GetPgBlockInfo(S7Object Client, void *pBlock, TS7BlockInfo *pUsrData, int Size);
int S7API Cli_ListBlocksOfType(S7Object Client, int BlockType, TS7BlocksOfType *pUsrData, int *ItemsCount);
// Blocks functions
int S7API Cli_Upload(S7Object Client, int BlockType, int BlockNum, void *pUsrData, int *Size);
int S7API Cli_FullUpload(S7Object Client, int BlockType, int BlockNum, void *pUsrData, int *Size);
int S7API Cli_Download(S7Object Client, int BlockNum, void *pUsrData, int Size);
int S7API Cli_Delete(S7Object Client, int BlockType, int BlockNum);
int S7API Cli_DBGet(S7Object Client, int DBNumber, void *pUsrData, int *Size);
int S7API Cli_DBFill(S7Object Client, int DBNumber, int FillChar);
// Date/Time functions
int S7API Cli_GetPlcDateTime(S7Object Client, tm *DateTime);
int S7API Cli_SetPlcDateTime(S7Object Client, tm *DateTime);
int S7API Cli_SetPlcSystemDateTime(S7Object Client);
// System Info functions
int S7API Cli_GetOrderCode(S7Object Client, TS7OrderCode *pUsrData);
int S7API Cli_GetCpuInfo(S7Object Client, TS7CpuInfo *pUsrData);
int S7API Cli_GetCpInfo(S7Object Client, TS7CpInfo *pUsrData);
int S7API Cli_ReadSZL(S7Object Client, int ID, int Index, TS7SZL *pUsrData, int *Size);
int S7API Cli_ReadSZLList(S7Object Client, TS7SZLList *pUsrData, int *ItemsCount);
// Control functions
int S7API Cli_PlcHotStart(S7Object Client);
int S7API Cli_PlcColdStart(S7Object Client);
int S7API Cli_PlcStop(S7Object Client);
int S7API Cli_CopyRamToRom(S7Object Client, int Timeout);
int S7API Cli_Compress(S7Object Client, int Timeout);
int S7API Cli_GetPlcStatus(S7Object Client, int *Status);
// Security functions
int S7API Cli_GetProtection(S7Object Client, TS7Protection *pUsrData);
int S7API Cli_SetSessionPassword(S7Object Client, char *Password);
int S7API Cli_ClearSessionPassword(S7Object Client);
// Low level
int S7API Cli_IsoExchangeBuffer(S7Object Client, void *pUsrData, int *Size);
// Misc
int S7API Cli_GetExecTime(S7Object Client, int *Time);
int S7API Cli_GetLastError(S7Object Client, int *LastError);
int S7API Cli_GetPduLength(S7Object Client, int *Requested, int *Negotiated);
int S7API Cli_ErrorText(int Error, char *Text, int TextLen);
// 1.1.0
int S7API Cli_GetConnected(S7Object Client, int *Connected);
//------------------------------------------------------------------------------
//  Async functions
//------------------------------------------------------------------------------
int S7API Cli_AsReadArea(S7Object Client, int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
int S7API Cli_AsWriteArea(S7Object Client, int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
int S7API Cli_AsDBRead(S7Object Client, int DBNumber, int Start, int Size, void *pUsrData);
int S7API Cli_AsDBWrite(S7Object Client, int DBNumber, int Start, int Size, void *pUsrData);
int S7API Cli_AsMBRead(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_AsMBWrite(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_AsEBRead(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_AsEBWrite(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_AsABRead(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_AsABWrite(S7Object Client, int Start, int Size, void *pUsrData);
int S7API Cli_AsTMRead(S7Object Client, int Start, int Amount, void *pUsrData);
int S7API Cli_AsTMWrite(S7Object Client, int Start, int Amount, void *pUsrData);
int S7API Cli_AsCTRead(S7Object Client, int Start, int Amount, void *pUsrData);
int S7API Cli_AsCTWrite(S7Object Client, int Start, int Amount, void *pUsrData);
int S7API Cli_AsListBlocksOfType(S7Object Client, int BlockType, TS7BlocksOfType *pUsrData, int *ItemsCount);
int S7API Cli_AsReadSZL(S7Object Client, int ID, int Index, TS7SZL *pUsrData, int *Size);
int S7API Cli_AsReadSZLList(S7Object Client, TS7SZLList *pUsrData, int *ItemsCount);
int S7API Cli_AsUpload(S7Object Client, int BlockType, int BlockNum, void *pUsrData, int *Size);
int S7API Cli_AsFullUpload(S7Object Client, int BlockType, int BlockNum, void *pUsrData, int *Size);
int S7API Cli_AsDownload(S7Object Client, int BlockNum, void *pUsrData, int Size);
int S7API Cli_AsCopyRamToRom(S7Object Client, int Timeout);
int S7API Cli_AsCompress(S7Object Client, int Timeout);
int S7API Cli_AsDBGet(S7Object Client, int DBNumber, void *pUsrData, int *Size);
int S7API Cli_AsDBFill(S7Object Client, int DBNumber, int FillChar);
int S7API Cli_CheckAsCompletion(S7Object Client, int *opResult);
int S7API Cli_WaitAsCompletion(S7Object Client, int Timeout);

//******************************************************************************
//                                   SERVER
//******************************************************************************

extern const int mkEvent;
extern const int mkLog;

// Server Area ID  (use with Register/unregister - Lock/unlock Area)
extern const int srvAreaPE;
extern const int srvAreaPA;
extern const int srvAreaMK;
extern const int srvAreaCT;
extern const int srvAreaTM;
extern const int srvAreaDB;

// Errors
extern const longword errSrvCannotStart; // Server cannot start
extern const longword errSrvDBNullPointer; // Passed null as PData
extern const longword errSrvAreaAlreadyExists; // Area Re-registration
extern const longword errSrvUnknownArea; // Unknown area
extern const longword errSrvInvalidParams; // Invalid param(s) supplied
extern const longword errSrvTooManyDB; // Cannot register DB
extern const longword errSrvInvalidParamNumber; // Invalid param (srv_get/set_param)
extern const longword errSrvCannotChangeParam; // Cannot change because running

// TCP Server Event codes
extern const longword evcServerStarted;
extern const longword evcServerStopped;
extern const longword evcListenerCannotStart;
extern const longword evcClientAdded;
extern const longword evcClientRejected;
extern const longword evcClientNoRoom;
extern const longword evcClientException;
extern const longword evcClientDisconnected;
extern const longword evcClientTerminated;
extern const longword evcClientsDropped;
extern const longword evcReserved_00000400; // actually unused
extern const longword evcReserved_00000800; // actually unused
extern const longword evcReserved_00001000; // actually unused
extern const longword evcReserved_00002000; // actually unused
extern const longword evcReserved_00004000; // actually unused
extern const longword evcReserved_00008000; // actually unused
// S7 Server Event Code
extern const longword evcPDUincoming  	;
extern const longword evcDataRead;
extern const longword evcDataWrite    	;
extern const longword evcNegotiatePDU;
extern const longword evcReadSZL;
extern const longword evcClock;
extern const longword evcUpload;
extern const longword evcDownload;
extern const longword evcDirectory;
extern const longword evcSecurity;
extern const longword evcControl;
extern const longword evcReserved_08000000; // actually unused
extern const longword evcReserved_10000000; // actually unused
extern const longword evcReserved_20000000; // actually unused
extern const longword evcReserved_40000000; // actually unused
extern const longword evcReserved_80000000; // actually unused
// Masks to enable/disable all events
extern const longword evcAll;
extern const longword evcNone;
// Event SubCodes
extern const word evsUnknown;
extern const word evsStartUpload;
extern const word evsStartDownload;
extern const word evsGetBlockList;
extern const word evsStartListBoT;
extern const word evsListBoT;
extern const word evsGetBlockInfo;
extern const word evsGetClock;
extern const word evsSetClock;
extern const word evsSetPassword;
extern const word evsClrPassword;
// Event Params : functions group
extern const word grProgrammer;
extern const word grCyclicData;
extern const word grBlocksInfo;
extern const word grSZL;
extern const word grPassword;
extern const word grBSend;
extern const word grClock;
extern const word grSecurity;
// Event Params : control codes
extern const word CodeControlUnknown;
extern const word CodeControlColdStart;
extern const word CodeControlWarmStart;
extern const word CodeControlStop;
extern const word CodeControlCompress;
extern const word CodeControlCpyRamRom;
extern const word CodeControlInsDel;
// Event Result
extern const word evrNoError;
extern const word evrFragmentRejected;
extern const word evrMalformedPDU;
extern const word evrSparseBytes;
extern const word evrCannotHandlePDU;
extern const word evrNotImplemented;
extern const word evrErrException;
extern const word evrErrAreaNotFound;
extern const word evrErrOutOfRange;
extern const word evrErrOverPDU;
extern const word evrErrTransportSize;
extern const word evrInvalidGroupUData;
extern const word evrInvalidSZL;
extern const word evrDataSizeMismatch;
extern const word evrCannotUpload;
extern const word evrCannotDownload;
extern const word evrUploadInvalidID;
extern const word evrResNotFound;

typedef struct{
	time_t EvtTime;    // Timestamp
	int EvtSender;     // Sender
	longword EvtCode;  // Event code
	word EvtRetCode;   // Event result
	word EvtParam1;    // Param 1 (if available)
	word EvtParam2;    // Param 2 (if available)
	word EvtParam3;    // Param 3 (if available)
	word EvtParam4;    // Param 4 (if available)
}TSrvEvent, *PSrvEvent;

// Server Evants callback
typedef void (S7API *pfn_SrvCallBack)(void * usrPtr, PSrvEvent PEvent, int Size);
S7Object S7API Srv_Create();
void S7API Srv_Destroy(S7Object *Server);
int S7API Srv_GetParam(S7Object Server, int ParamNumber, void *pValue);
int S7API Srv_SetParam(S7Object Server, int ParamNumber, void *pValue);
int S7API Srv_StartTo(S7Object Server, const char *Address);
int S7API Srv_Start(S7Object Server);
int S7API Srv_Stop(S7Object Server);
int S7API Srv_RegisterArea(S7Object Server, int AreaCode, word Index, void *pUsrData, int Size);
int S7API Srv_UnregisterArea(S7Object Server, int AreaCode, word Index);
int S7API Srv_LockArea(S7Object Server, int AreaCode, word Index);
int S7API Srv_UnlockArea(S7Object Server, int AreaCode, word Index);
int S7API Srv_GetStatus(S7Object Server, int *ServerStatus, int *CpuStatus, int *ClientsCount);
int S7API Srv_SetCpuStatus(S7Object Server, int CpuStatus);
int S7API Srv_ClearEvents(S7Object Server);
int S7API Srv_PickEvent(S7Object Server, TSrvEvent *pEvent, int *EvtReady);
int S7API Srv_GetMask(S7Object Server, int MaskKind, longword *Mask);
int S7API Srv_SetMask(S7Object Server, int MaskKind, longword Mask);
int S7API Srv_SetEventsCallback(S7Object Server, pfn_SrvCallBack pCallback, void *usrPtr);
int S7API Srv_SetReadEventsCallback(S7Object Server, pfn_SrvCallBack pCallback, void *usrPtr);
int S7API Srv_EventText(TSrvEvent *Event, char *Text, int TextLen);
int S7API Srv_ErrorText(int Error, char *Text, int TextLen);

//******************************************************************************
//                                   PARTNER
//******************************************************************************

// Status
extern const int par_stopped;   // stopped
extern const int par_connecting;   // running and active connecting
extern const int par_waiting;   // running and waiting for a connection
extern const int par_linked;   // running and connected : linked
extern const int par_sending;   // sending data
extern const int par_receiving;   // receiving data
extern const int par_binderror;   // error starting passive server

// Errors
extern const longword errParAddressInUse;
extern const longword errParNoRoom;
extern const longword errServerNoRoom;
extern const longword errParInvalidParams;
extern const longword errParNotLinked;
extern const longword errParBusy;
extern const longword errParFrameTimeout;
extern const longword errParInvalidPDU;
extern const longword errParSendTimeout;
extern const longword errParRecvTimeout;
extern const longword errParSendRefused;
extern const longword errParNegotiatingPDU;
extern const longword errParSendingBlock;
extern const longword errParRecvingBlock;
extern const longword errParBindError;
extern const longword errParDestroying;
extern const longword errParInvalidParamNumber; // Invalid param (par_get/set_param)
extern const longword errParCannotChangeParam; // Cannot change because running
extern const longword errParBufferTooSmall; // Raised by LabVIEW wrapper

// Brecv Data incoming Callback
typedef void (S7API *pfn_ParRecvCallBack)(void * usrPtr, int opResult, longword R_ID, void *pData, int Size);
// BSend Completion Callback
typedef void (S7API *pfn_ParSendCompletion)(void * usrPtr, int opResult);

S7Object S7API Par_Create(int Active);
void S7API Par_Destroy(S7Object *Partner);
int S7API Par_GetParam(S7Object Partner, int ParamNumber, void *pValue);
int S7API Par_SetParam(S7Object Partner, int ParamNumber, void *pValue);
int S7API Par_StartTo(S7Object Partner, const char *LocalAddress, const char *RemoteAddress,
    word LocTsap, word RemTsap);
int S7API Par_Start(S7Object Partner);
int S7API Par_Stop(S7Object Partner);
// BSend
int S7API Par_BSend(S7Object Partner, longword R_ID, void *pUsrData, int Size);
int S7API Par_AsBSend(S7Object Partner, longword R_ID, void *pUsrData, int Size);
int S7API Par_CheckAsBSendCompletion(S7Object Partner, int *opResult);
int S7API Par_WaitAsBSendCompletion(S7Object Partner, longword Timeout);
int S7API Par_SetSendCallback(S7Object Partner, pfn_ParSendCompletion pCompletion, void *usrPtr);
// BRecv
int S7API Par_BRecv(S7Object Partner, longword *R_ID, void *pData, int *Size, longword Timeout);
int S7API Par_CheckAsBRecvCompletion(S7Object Partner, int *opResult, longword *R_ID,
	void *pData, int *Size);
int S7API Par_SetRecvCallback(S7Object Partner, pfn_ParRecvCallBack pCompletion, void *usrPtr);
// Stat
int S7API Par_GetTimes(S7Object Partner, longword *SendTime, longword *RecvTime);
int S7API Par_GetStats(S7Object Partner, longword *BytesSent, longword *BytesRecv,
	longword *SendErrors, longword *RecvErrors);
int S7API Par_GetLastError(S7Object Partner, int *LastError);
int S7API Par_GetStatus(S7Object Partner, int *Status);
int S7API Par_ErrorText(int Error, char *Text, int TextLen);


#pragma pack()
#ifdef __cplusplus
 }
#endif // __cplusplus

#ifdef __cplusplus

//******************************************************************************
//                           CLIENT CLASS DEFINITION
//******************************************************************************
class TS7Client
{
private:
    S7Object Client;
public:
	TS7Client();
	~TS7Client();
    // Control functions
    int Connect();
    int ConnectTo(const char *RemAddress, int Rack, int Slot);
    int SetConnectionParams(const char *RemAddress, word LocalTSAP, word RemoteTSAP);
    int SetConnectionType(word ConnectionType);
    int Disconnect();
    int GetParam(int ParamNumber, void *pValue);
    int SetParam(int ParamNumber, void *pValue);
    // Data I/O Main functions
    int ReadArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
    int WriteArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
    int ReadMultiVars(PS7DataItem Item, int ItemsCount);
    int WriteMultiVars(PS7DataItem Item, int ItemsCount);
    // Data I/O Lean functions
    int DBRead(int DBNumber, int Start, int Size, void *pUsrData);
    int DBWrite(int DBNumber, int Start, int Size, void *pUsrData);
    int MBRead(int Start, int Size, void *pUsrData);
    int MBWrite(int Start, int Size, void *pUsrData);
    int EBRead(int Start, int Size, void *pUsrData);
    int EBWrite(int Start, int Size, void *pUsrData);
    int ABRead(int Start, int Size, void *pUsrData);
    int ABWrite(int Start, int Size, void *pUsrData);
    int TMRead(int Start, int Amount, void *pUsrData);
    int TMWrite(int Start, int Amount, void *pUsrData);
    int CTRead(int Start, int Amount, void *pUsrData);
    int CTWrite(int Start, int Amount, void *pUsrData);
    // Directory functions
    int ListBlocks(PS7BlocksList pUsrData);
    int GetAgBlockInfo(int BlockType, int BlockNum, PS7BlockInfo pUsrData);
    int GetPgBlockInfo(void *pBlock, PS7BlockInfo pUsrData, int Size);
    int ListBlocksOfType(int BlockType, TS7BlocksOfType *pUsrData, int *ItemsCount);
    // Blocks functions
    int Upload(int BlockType, int BlockNum, void *pUsrData, int *Size);
    int FullUpload(int BlockType, int BlockNum, void *pUsrData, int *Size);
    int Download(int BlockNum, void *pUsrData, int Size);
    int Delete(int BlockType, int BlockNum);
    int DBGet(int DBNumber, void *pUsrData, int *Size);
    int DBFill(int DBNumber, int FillChar);
    // Date/Time functions
    int GetPlcDateTime(tm *DateTime);
    int SetPlcDateTime(tm *DateTime);
    int SetPlcSystemDateTime();
    // System Info functions
    int GetOrderCode(PS7OrderCode pUsrData);
    int GetCpuInfo(PS7CpuInfo pUsrData);
    int GetCpInfo(PS7CpInfo pUsrData);
	int ReadSZL(int ID, int Index, PS7SZL pUsrData, int *Size);
	int ReadSZLList(PS7SZLList pUsrData, int *ItemsCount);
	// Control functions
	int PlcHotStart();
	int PlcColdStart();
	int PlcStop();
	int CopyRamToRom(int Timeout);
	int Compress(int Timeout);
	// Security functions
	int GetProtection(PS7Protection pUsrData);
	int SetSessionPassword(char *Password);
	int ClearSessionPassword();
	// Properties
	int ExecTime();
	int LastError();
	int PDURequested();
	int PDULength();
	int PlcStatus();
	bool Connected();
	// Async functions
	int SetAsCallback(pfn_CliCompletion pCompletion, void *usrPtr);
	bool CheckAsCompletion(int *opResult);
	int WaitAsCompletion(longword Timeout);
	int AsReadArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
	int AsWriteArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
	int AsListBlocksOfType(int BlockType, PS7BlocksOfType pUsrData, int *ItemsCount);
	int AsReadSZL(int ID, int Index, PS7SZL pUsrData, int *Size);
	int AsReadSZLList(PS7SZLList pUsrData, int *ItemsCount);
	int AsUpload(int BlockType, int BlockNum, void *pUsrData, int *Size);
	int AsFullUpload(int BlockType, int BlockNum, void *pUsrData, int *Size);
	int AsDownload(int BlockNum, void *pUsrData,  int Size);
	int AsCopyRamToRom(int Timeout);
	int AsCompress(int Timeout);
	int AsDBRead(int DBNumber, int Start, int Size, void *pUsrData);
	int AsDBWrite(int DBNumber, int Start, int Size, void *pUsrData);
	int AsMBRead(int Start, int Size, void *pUsrData);
	int AsMBWrite(int Start, int Size, void *pUsrData);
	int AsEBRead(int Start, int Size, void *pUsrData);
	int AsEBWrite(int Start, int Size, void *pUsrData);
	int AsABRead(int Start, int Size, void *pUsrData);
	int AsABWrite(int Start, int Size, void *pUsrData);
    int AsTMRead(int Start, int Amount, void *pUsrData);
    int AsTMWrite(int Start, int Amount, void *pUsrData);
    int AsCTRead(int Start, int Amount, void *pUsrData);
	int AsCTWrite(int Start, int Amount, void *pUsrData);
    int AsDBGet(int DBNumber, void *pUsrData, int *Size);
	int AsDBFill(int DBNumber, int FillChar);
};
typedef TS7Client *PS7Client;
//******************************************************************************
//                           SERVER CLASS DEFINITION
//******************************************************************************
class TS7Server
{
private:
    S7Object Server;
public:
    TS7Server();
    ~TS7Server();
    // Control
    int Start();
    int StartTo(const char *Address);
    int Stop();
    int GetParam(int ParamNumber, void *pValue);
    int SetParam(int ParamNumber, void *pValue);
    // Events
    int SetEventsCallback(pfn_SrvCallBack PCallBack, void *UsrPtr);
    int SetReadEventsCallback(pfn_SrvCallBack PCallBack, void *UsrPtr);
    bool PickEvent(TSrvEvent *pEvent);
    void ClearEvents();
    longword GetEventsMask();
    longword GetLogMask();
    void SetEventsMask(longword Mask);
    void SetLogMask(longword Mask);
    // Resources
    int RegisterArea(int AreaCode, word Index, void *pUsrData, word Size);
    int UnregisterArea(int AreaCode, word Index);
    int LockArea(int AreaCode, word Index);
    int UnlockArea(int AreaCode, word Index);
    // Properties
    int ServerStatus();
    int GetCpuStatus();
    int SetCpuStatus(int Status);
	int ClientsCount();
};
typedef TS7Server *PS7Server;

//******************************************************************************
//                          PARTNER CLASS DEFINITION
//******************************************************************************
class TS7Partner
{
private:
	S7Object Partner; // Partner Handle
public:
	TS7Partner(bool Active);
	~TS7Partner();
	// Control
	int GetParam(int ParamNumber, void *pValue);
	int SetParam(int ParamNumber, void *pValue);
	int Start();
	int StartTo(const char *LocalAddress,
				const char *RemoteAddress,
				int LocalTSAP,
				int RemoteTSAP);
	int Stop();
	// Data I/O functions : BSend
	int BSend(longword R_ID, void *pUsrData, int Size);
	int AsBSend(longword R_ID, void *pUsrData, int Size);
	bool CheckAsBSendCompletion(int *opResult);
	int WaitAsBSendCompletion(longword Timeout);
	int SetSendCallback(pfn_ParSendCompletion pCompletion, void *usrPtr);
	// Data I/O functions : BRecv
	int BRecv(longword *R_ID, void *pUsrData, int *Size, longword Timeout);
	bool CheckAsBRecvCompletion(int *opResult, longword *R_ID, void *pUsrData, int *Size);
	int SetRecvCallback(pfn_ParRecvCallBack pCallback, void *usrPtr);
	// Properties
	int Status();
	int LastError();
	int GetTimes(longword *SendTime, longword *RecvTime);
	int GetStats(longword *BytesSent,
				 longword *BytesRecv,
				 longword *ErrSend,
				 longword *ErrRecv);
	bool Linked();
};
typedef TS7Partner *PS7Partner;
//******************************************************************************
//                               TEXT ROUTINES
// Only for C++, for pure C use xxx_ErrorText() which uses *char
//******************************************************************************
#define TextLen 1024

// String type
// Here we define generic TextString (by default mapped onto std::string).
// So you can change it if needed (Unicodestring, Ansistring etc...)

typedef std::string TextString;

TextString CliErrorText(int Error);
TextString SrvErrorText(int Error);
TextString ParErrorText(int Error);
TextString SrvEventText(TSrvEvent *Event);


#endif // __cplusplus
#endif // _snap7_h
