#include "libPLC.h"

int PLCConnect( S7Object* plcClient, const char* plcIp, int* plcRack, int* plcSlot ){
    
    *plcClient = Cli_Create();
    return ( int )Cli_ConnectTo( *plcClient, plcIp, *plcRack,  *plcSlot );
}

int PLCDisconnect( S7Object* plcClient ){
    return Cli_Disconnect( *plcClient );
}

