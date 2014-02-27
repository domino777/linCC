#ifndef _libPLC_h
#define _libPLC_h

#include "snap7.h"

#define snap7PLCIp       192.168.102.1
#define snap7PLCRack     0
#define snap7PLCSlot     2


int PLCConnect( S7Object* plcClient, const char* plcIp, int plcRack, int plcSlot );
int PLCDisconnect( S7Object* plcClient );

#endif // _libPLC_h
