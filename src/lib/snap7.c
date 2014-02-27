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

#include "snap7.h"

// ISO Errors
const longword errIsoConnect            = 0x00010000; // Connection error
const longword errIsoDisconnect         = 0x00020000; // Disconnect error
const longword errIsoInvalidPDU         = 0x00030000; // Bad format
const longword errIsoInvalidDataSize    = 0x00040000; // Bad Datasize passed to send/recv buffer is invalid
const longword errIsoNullPointer    	= 0x00050000; // Null passed as pointer
const longword errIsoShortPacket    	= 0x00060000; // A short packet received
const longword errIsoTooManyFragments   = 0x00070000; // Too many packets without EoT flag
const longword errIsoPduOverflow    	= 0x00080000; // The sum of fragments data exceded maximum packet size
const longword errIsoSendPacket         = 0x00090000; // An error occurred during send
const longword errIsoRecvPacket         = 0x000A0000; // An error occurred during recv
const longword errIsoInvalidParams    	= 0x000B0000; // Invalid TSAP params
const longword errIsoResvd_1            = 0x000C0000; // Unassigned
const longword errIsoResvd_2            = 0x000D0000; // Unassigned
const longword errIsoResvd_3            = 0x000E0000; // Unassigned
const longword errIsoResvd_4            = 0x000F0000; // Unassigned

//------------------------------------------------------------------------------
//                                  PARAMS LIST            
//------------------------------------------------------------------------------
const int p_u16_LocalPort  	    = 1;
const int p_u16_RemotePort 	    = 2;
const int p_i32_PingTimeout	    = 3;
const int p_i32_SendTimeout     = 4;
const int p_i32_RecvTimeout     = 5;
const int p_i32_WorkInterval    = 6;
const int p_u16_SrcRef          = 7;
const int p_u16_DstRef          = 8;
const int p_u16_SrcTSap         = 9;
const int p_i32_PDURequest      = 10;
const int p_i32_MaxClients      = 11;
const int p_i32_BSendTimeout    = 12;
const int p_i32_BRecvTimeout    = 13;
const int p_u32_RecoveryTime    = 14;
const int p_u32_KeepAliveTime   = 15;

// Client/Partner Job status 
const int JobComplete           = 0;
const int JobPending            = 1;

//******************************************************************************
//                                   CLIENT
//******************************************************************************

// Error codes
const longword errNegotiatingPDU            = 0x00100000;
const longword errCliInvalidParams          = 0x00200000;
const longword errCliJobPending             = 0x00300000;
const longword errCliTooManyItems           = 0x00400000;
const longword errCliInvalidWordLen         = 0x00500000;
const longword errCliPartialDataWritten     = 0x00600000;
const longword errCliSizeOverPDU            = 0x00700000;
const longword errCliInvalidPlcAnswer       = 0x00800000;
const longword errCliAddressOutOfRange      = 0x00900000;
const longword errCliInvalidTransportSize   = 0x00A00000;
const longword errCliWriteDataSizeMismatch  = 0x00B00000;
const longword errCliItemNotAvailable       = 0x00C00000;
const longword errCliInvalidValue           = 0x00D00000;
const longword errCliCannotStartPLC         = 0x00E00000;
const longword errCliAlreadyRun             = 0x00F00000;
const longword errCliCannotStopPLC          = 0x01000000;
const longword errCliCannotCopyRamToRom     = 0x01100000;
const longword errCliCannotCompress         = 0x01200000;
const longword errCliAlreadyStop            = 0x01300000;
const longword errCliFunNotAvailable        = 0x01400000;
const longword errCliUploadSequenceFailed   = 0x01500000;
const longword errCliInvalidDataSizeRecvd   = 0x01600000;
const longword errCliInvalidBlockType       = 0x01700000;
const longword errCliInvalidBlockNumber     = 0x01800000;
const longword errCliInvalidBlockSize       = 0x01900000;
const longword errCliDownloadSequenceFailed = 0x01A00000;
const longword errCliInsertRefused          = 0x01B00000;
const longword errCliDeleteRefused          = 0x01C00000;
const longword errCliNeedPassword           = 0x01D00000;
const longword errCliInvalidPassword        = 0x01E00000;
const longword errCliNoPasswordToSetOrClear = 0x01F00000;
const longword errCliJobTimeout             = 0x02000000;
const longword errCliPartialDataRead        = 0x02100000;
const longword errCliBufferTooSmall         = 0x02200000;
const longword errCliFunctionRefused        = 0x02300000;
const longword errCliDestroying             = 0x02400000;
const longword errCliInvalidParamNumber     = 0x02500000;
const longword errCliCannotChangeParam      = 0x02600000;

const int MaxVars     = 20; // Max vars that can be transferred with MultiRead/MultiWrite

// Client Connection Type
const word CONNTYPE_PG                      = 0x0001;  // Connect to the PLC as a PG
const word CONNTYPE_OP                      = 0x0002;  // Connect to the PLC as an OP
const word CONNTYPE_BASIC                   = 0x0003;  // Basic connection

// Area ID
const byte S7AreaPE   =	0x81;
const byte S7AreaPA   =	0x82;
const byte S7AreaMK   =	0x83;
const byte S7AreaDB   =	0x84;
const byte S7AreaCT   =	0x1C;
const byte S7AreaTM   =	0x1D;

// Word Length
const int S7WLBit     = 0x01;
const int S7WLByte    = 0x02;
const int S7WLWord    = 0x04;
const int S7WLDWord   = 0x06;
const int S7WLReal    = 0x08;
const int S7WLCounter = 0x1C;
const int S7WLTimer   = 0x1D;

// Block type
const byte Block_OB   = 0x38;
const byte Block_DB   = 0x41;
const byte Block_SDB  = 0x42;
const byte Block_FC   = 0x43;
const byte Block_SFC  = 0x44;
const byte Block_FB   = 0x45;
const byte Block_SFB  = 0x46;

// Sub Block Type
const byte SubBlk_OB  = 0x08;
const byte SubBlk_DB  = 0x0A;
const byte SubBlk_SDB = 0x0B;
const byte SubBlk_FC  = 0x0C;
const byte SubBlk_SFC = 0x0D;
const byte SubBlk_FB  = 0x0E;
const byte SubBlk_SFB = 0x0F;

// Block languages
const byte BlockLangAWL       = 0x01;
const byte BlockLangKOP       = 0x02;
const byte BlockLangFUP       = 0x03;
const byte BlockLangSCL       = 0x04;
const byte BlockLangDB        = 0x05;
const byte BlockLangGRAPH     = 0x06;

//******************************************************************************
//                                   SERVER
//******************************************************************************

const int mkEvent = 0;
const int mkLog   = 1;

// Server Area ID  (use with Register/unregister - Lock/unlock Area)
const int srvAreaPE = 0;
const int srvAreaPA = 1;
const int srvAreaMK = 2;
const int srvAreaCT = 3;
const int srvAreaTM = 4;
const int srvAreaDB = 5;

// Errors
const longword errSrvCannotStart        = 0x00100000; // Server cannot start
const longword errSrvDBNullPointer      = 0x00200000; // Passed null as PData
const longword errSrvAreaAlreadyExists  = 0x00300000; // Area Re-registration
const longword errSrvUnknownArea        = 0x00400000; // Unknown area
const longword errSrvInvalidParams      = 0x00500000; // Invalid param(s) supplied
const longword errSrvTooManyDB          = 0x00600000; // Cannot register DB
const longword errSrvInvalidParamNumber = 0x00700000; // Invalid param (srv_get/set_param)
const longword errSrvCannotChangeParam  = 0x00800000; // Cannot change because running

// TCP Server Event codes
const longword evcServerStarted       = 0x00000001;
const longword evcServerStopped       = 0x00000002;
const longword evcListenerCannotStart = 0x00000004;
const longword evcClientAdded         = 0x00000008;
const longword evcClientRejected      = 0x00000010;
const longword evcClientNoRoom        = 0x00000020;
const longword evcClientException     = 0x00000040;
const longword evcClientDisconnected  = 0x00000080;
const longword evcClientTerminated    = 0x00000100;
const longword evcClientsDropped      = 0x00000200;
const longword evcReserved_00000400   = 0x00000400; // actually unused
const longword evcReserved_00000800   = 0x00000800; // actually unused
const longword evcReserved_00001000   = 0x00001000; // actually unused
const longword evcReserved_00002000   = 0x00002000; // actually unused
const longword evcReserved_00004000   = 0x00004000; // actually unused
const longword evcReserved_00008000   = 0x00008000; // actually unused
// S7 Server Event Code
const longword evcPDUincoming  	      = 0x00010000;
const longword evcDataRead            = 0x00020000;
const longword evcDataWrite    	      = 0x00040000;
const longword evcNegotiatePDU        = 0x00080000;
const longword evcReadSZL             = 0x00100000;
const longword evcClock               = 0x00200000;
const longword evcUpload              = 0x00400000;
const longword evcDownload            = 0x00800000;
const longword evcDirectory           = 0x01000000;
const longword evcSecurity            = 0x02000000;
const longword evcControl             = 0x04000000;
const longword evcReserved_08000000   = 0x08000000; // actually unused
const longword evcReserved_10000000   = 0x10000000; // actually unused
const longword evcReserved_20000000   = 0x20000000; // actually unused
const longword evcReserved_40000000   = 0x40000000; // actually unused
const longword evcReserved_80000000   = 0x80000000; // actually unused
// Masks to enable/disable all events
const longword evcAll                 = 0xFFFFFFFF;
const longword evcNone                = 0x00000000;
// Event SubCodes
const word evsUnknown                 = 0x0000;
const word evsStartUpload             = 0x0001;
const word evsStartDownload           = 0x0001;
const word evsGetBlockList            = 0x0001;
const word evsStartListBoT            = 0x0002;
const word evsListBoT                 = 0x0003;
const word evsGetBlockInfo            = 0x0004;
const word evsGetClock                = 0x0001;
const word evsSetClock                = 0x0002;
const word evsSetPassword             = 0x0001;
const word evsClrPassword             = 0x0002;
// Event Params : functions group
const word grProgrammer               = 0x0041;
const word grCyclicData               = 0x0042;
const word grBlocksInfo               = 0x0043;
const word grSZL                      = 0x0044;
const word grPassword                 = 0x0045;
const word grBSend                    = 0x0046;
const word grClock                    = 0x0047;
const word grSecurity                 = 0x0045;
// Event Params : control codes
const word CodeControlUnknown         = 0x0000;
const word CodeControlColdStart       = 0x0001;
const word CodeControlWarmStart       = 0x0002;
const word CodeControlStop            = 0x0003;
const word CodeControlCompress        = 0x0004;
const word CodeControlCpyRamRom       = 0x0005;
const word CodeControlInsDel          = 0x0006;
// Event Result
const word evrNoError                 = 0x0000;
const word evrFragmentRejected        = 0x0001;
const word evrMalformedPDU            = 0x0002;
const word evrSparseBytes             = 0x0003;
const word evrCannotHandlePDU         = 0x0004;
const word evrNotImplemented          = 0x0005;
const word evrErrException            = 0x0006;
const word evrErrAreaNotFound         = 0x0007;
const word evrErrOutOfRange           = 0x0008;
const word evrErrOverPDU              = 0x0009;
const word evrErrTransportSize        = 0x000A;
const word evrInvalidGroupUData       = 0x000B;
const word evrInvalidSZL              = 0x000C;
const word evrDataSizeMismatch        = 0x000D;
const word evrCannotUpload            = 0x000E;
const word evrCannotDownload          = 0x000F;
const word evrUploadInvalidID         = 0x0010;
const word evrResNotFound             = 0x0011;

//******************************************************************************
//                                   PARTNER
//******************************************************************************

// Status
const int par_stopped         = 0;   // stopped
const int par_connecting      = 1;   // running and active connecting
const int par_waiting         = 2;   // running and waiting for a connection
const int par_linked          = 3;   // running and connected : linked
const int par_sending         = 4;   // sending data
const int par_receiving       = 5;   // receiving data
const int par_binderror       = 6;   // error starting passive server

// Errors
const longword errParAddressInUse       = 0x00200000;
const longword errParNoRoom             = 0x00300000;
const longword errServerNoRoom          = 0x00400000;
const longword errParInvalidParams      = 0x00500000;
const longword errParNotLinked          = 0x00600000;
const longword errParBusy               = 0x00700000;
const longword errParFrameTimeout       = 0x00800000;
const longword errParInvalidPDU         = 0x00900000;
const longword errParSendTimeout        = 0x00A00000;
const longword errParRecvTimeout        = 0x00B00000;
const longword errParSendRefused        = 0x00C00000;
const longword errParNegotiatingPDU     = 0x00D00000;
const longword errParSendingBlock       = 0x00E00000;
const longword errParRecvingBlock       = 0x00F00000;
const longword errParBindError          = 0x01000000;
const longword errParDestroying         = 0x01100000;
const longword errParInvalidParamNumber = 0x01200000; // Invalid param (par_get/set_param)
const longword errParCannotChangeParam  = 0x01300000; // Cannot change because running
const longword errParBufferTooSmall     = 0x01400000; // Raised by LabVIEW wrapper
