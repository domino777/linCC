/*
 *	libPLC.c
 *
 *  "Copyright 2014 Mauro Ghedin"
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  or any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *
 *       @author         : Mauro Ghedin
 *       @contact        : domyno88 at gmail dot com
 *       @version        : 0.1
 *
 */
 
#include "libPLC.h"

int PLCConnect( S7Object* plcClient, const char* plcIp, int plcRack, int plcSlot ){
    
    *plcClient = Cli_Create();
    return Cli_ConnectTo( *plcClient, plcIp, plcRack,  plcSlot );
}

int PLCDisconnect( S7Object* plcClient ){
    return Cli_Disconnect( *plcClient );
}

float PLCReadTag( S7Object* plcClient, unsigned int* tagDB, unsigned int* tagByte, int* varType ){

//  Getting plc's INT or WORD value
    if( *varType == Word || *varType == Int ) {
		 char dataByte[ _BYTE_2_ ];
		 
//  Read error detection
         if( Cli_DBRead( *plcClient, *tagDB, *tagByte, _BYTE_2_ , &dataByte ))
             return PLC_DB_READ_ERROR;
             
         int tempVar = dataByte[0] << 8;
         return ( float )( tempVar = tempVar | dataByte[1] );
    }
    //else if( varType == DInt || varType == Real )
}

