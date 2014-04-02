/*
 *	commInfo.h
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

#include "commInfo.h"

int linCCPLCgetInfo( PLC_CONN_INFO* connInfo ) {

    MYSQL* sqlHndl;  

//  Create my SQL connection and get row count of vatList table
    linCCConnect( &sqlHndl );
    
    unsigned long rowCount;
    DATA_ROWS* connList;
    
    linCCgetRows( sqlHndl, &connList, &rowCount, 4, "SELECT id, PLCRack, PLCSlot, PLCIp FROM PLCConnections" );
    if ( !connList )
        return 1;
        
//  Convert id char* field into unsigned int value
    connInfo->id   = ( unsigned int )strtol(( const char *)connList[0][0], NULL, 10 );
//  Convert PLCRack char* field into unsigned int value
    connInfo->rack = ( unsigned int )strtol(( const char *)connList[0][1], NULL, 10 );
//  Convert PLCSlot char* field into unsigned int value    
    connInfo->slot = ( unsigned int )strtol(( const char *)connList[0][2], NULL, 10 );
//  Copy PLCIp char* field into char*
    strcpy( connInfo->ip, ( const char *)connList[0][3] );

    linCCRowsFree( connList, &rowCount, 4 );
    linCCDisconnect( sqlHndl );
    
    return 0;
}
