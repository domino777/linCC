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

int PLCConnect( S7Object* plcClient, const char* plcIp, int* plcRack, int* plcSlot ){
	
    *plcClient = Cli_Create();
    return Cli_ConnectTo( *plcClient, plcIp, *plcRack, *plcSlot );
}

int PLCDisconnect( S7Object* plcClient ){
    return Cli_Disconnect( *plcClient );
}

float PLCReadTag( S7Object* plcClient, unsigned int* tagDB, unsigned long* tagByte, unsigned char* tagBit, unsigned char* varType ){

//  Getting plc's INT or WORD value
    if( *varType == Word || *varType == Int ) {
        char dataByte[ _BYTE_2_ ];

//  Read error detection
         if( Cli_DBRead( *plcClient, *tagDB, *tagByte, _BYTE_2_ , &dataByte ))
             return PLC_DB_READ_ERROR;
             
         int tempVar = dataByte[0] << 8;
         return ( float )( tempVar = tempVar | dataByte[1] );
    }
    
    else if( *varType == Real ) {
         char dataByte[ _BYTE_4_ ];

//  Read error detection
         if( Cli_DBRead( *plcClient, *tagDB, *tagByte, _BYTE_4_ , &dataByte ))
             return PLC_DB_READ_ERROR;
             
         float tempFloat;
         *((unsigned char*)(&tempFloat) + 3) = dataByte[0];
         *((unsigned char*)(&tempFloat) + 2) = dataByte[1];
         *((unsigned char*)(&tempFloat) + 1) = dataByte[2];
         *((unsigned char*)(&tempFloat) + 0) = dataByte[3];

         return tempFloat;
    }
    
    else if( *varType == Bool ) {
        char dataByte;

        //  Read error detection
         if( Cli_DBRead( *plcClient, *tagDB, *tagByte, _BYTE_1_ , &dataByte ))
             return PLC_DB_READ_ERROR;

         if ( dataByte & ( 0x0001 << *tagBit ) )
             return 1.0;

         return 0.0;
     }
     
     return 0xFFFFFFFF;
}

int PLCReadTags( S7Object* plcClient, unsigned int* tagDB, unsigned long* startByte, unsigned long* dataLength, unsigned char** data) {

//  Read data into PLC and read error detection
    if( Cli_AsDBRead( *plcClient, *tagDB, *startByte, *dataLength, *data ))
        return PLC_DB_READ_ERROR;
    
    int retVal;    
    while( retVal = Cli_WaitAsCompletion( *plcClient, 1000) )
        if ( retVal != 0x02200000 )
            return retVal;
             
    return 0;
}

int PLCWriteTags( S7Object* plcClient, W_TAG_VAR* tagVar, unsigned long* tagVarCount ) {

//  Create data buffer to send to PLC
    PS7DataItem plcItems;
    plcItems = NULL;
    
    plcItems = malloc( sizeof( TS7DataItem ) * *tagVarCount );
    printf( " \n Tag count in plcwrite %d\n", *tagVarCount );
    if( !plcItems ) {
        printf( "Unable to allocate space. plcItems[] = malloc() error in PLCWriteTags()\n" );
        exit( GETPACK_REALLOC_EXIT );
    }

//  Prepare data buffer
    for( unsigned int i = 0; i < *tagVarCount; i++ ) {
//      On this version of linCC only DB can be read and write
        plcItems[i].Area    = 0x84;
        
        plcItems[i].DBNumber = tagVar[i].db;    
        plcItems[i].Start   = tagVar[i].address;
        plcItems[i].Amount = 1;
        
        unsigned char *data;
        data = NULL;
        
        if( tagVar[i].type == Bool ) {
            plcItems[i].WordLen = 0x01;
//  Override start address for bit type
            plcItems[i].Start = ( tagVar[i].address * 8 ) + tagVar[i].addressBit;
        }
//  Byte swap and assign for Byte type  
        else if( tagVar[i].type == Byte ) {
            plcItems[i].WordLen = 0x02;
            
            data = malloc( 1 );
            unsigned char val = ( unsigned char )( tagVar[i].tagValue );
            data[0] = ( unsigned char )val;
            plcItems[i].pdata = ( void *)data;
            
        }
//  Byte swap and assign for Word and Int type            
        else if( tagVar[i].type == Word || tagVar[i].type == Int ) {
            plcItems[i].WordLen = 0x04;
            
            data = malloc( 2 );
            short int val = ( short int )( tagVar[i].tagValue );
            data[0] = *((unsigned char*)(&( val ) ) + 1);
            data[1] = *((unsigned char*)(&( val ) ) + 0);

            plcItems[i].pdata = ( void *)data;
        }
//  Byte swap and assign for DWord and DInt type            
        else if( tagVar[i].type == DWord || tagVar[i].type == DInt ) {
            plcItems[i].WordLen = 0x06;

            data = malloc( 4 );
            int val = ( int )( tagVar[i].tagValue );
            data[0] = *((unsigned char*)(&( val ) ) + 3);
            data[1] = *((unsigned char*)(&( val ) ) + 2);
            data[2] = *((unsigned char*)(&( val ) ) + 1);
            data[3] = *((unsigned char*)(&( val ) ) + 0);
            plcItems[i].pdata = ( void *)data;
            
        }
//  Byte swap and assign for Real type            
        else if( tagVar[i].type == Real ) {
            plcItems[i].WordLen = 0x08;
            
            data = malloc( 4 );
            data[0] = *((unsigned char*)(&( tagVar[i].tagValue) ) + 3);
            data[1] = *((unsigned char*)(&( tagVar[i].tagValue) ) + 2);
            data[2] = *((unsigned char*)(&( tagVar[i].tagValue) ) + 1);
            data[3] = *((unsigned char*)(&( tagVar[i].tagValue) ) + 0);
            plcItems[i].pdata = ( void *)data;
            
        }
        
        printf(" TTTAAAAAAAG:::: %d", tagVar[i].id);
    }
//  Send data buffer
    int retVal = Cli_WriteMultiVars( *plcClient, plcItems, ( int )*tagVarCount );

//  Freeeeeeeeeeeing plcItems
    for( unsigned long i = 0; i < *tagVarCount; i++ )
        free( plcItems[i].pdata );
    free( plcItems );

    
    return retVal;

}
