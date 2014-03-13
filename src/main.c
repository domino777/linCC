#include "varTag.h"
#include "libPLC.h"
#include "commInfo.h"
#include "db_tagsPack.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


TAG_VAR* VarTags;
PLCData* addressPacked;

int main(void) {

    unsigned long rowCount;// = malloc( sizeof( unsigned long ));
    unsigned long packCount;
    getPack( &packCount );
    printf( "Data count: %d\n", packCount );
    for( int i = 0; i < packCount; i++)
        printf( "DB: %d : StrtByte: %d : Length: %d\n", addressPacked[i].db, addressPacked[i].startByte, addressPacked[i].dataLength );
    
    
    printf( "Reading database of tags... " );
    if( loadTags( &rowCount ) ) {
        printf( "Impossibile leggere lista tag da DB" );
        exit(1);
    }
    
    printf( "DONE!!\nNumber of tags: %d\n", rowCount );
   
    printf( "Reading database of PLC connections... " );
   	PLC_CONN_INFO* plcInfo;
   	plcInfo = linCCPLCgetInfo();	
   	
   	printf( "DONE!!\nPLC Connection info:\n" );
   	printf( "PLC IP ADDRESS   : %s\n", plcInfo->ip );
   	printf( "PLC RACK         : %d\n", plcInfo->rack );
   	printf( "PLC SLOT         : %d\n", plcInfo->slot );
   	printf( "Try to connect to PLC... " );
   	
   	S7Object client;
	if( PLCConnect( &client, plcInfo->ip , &plcInfo->rack, &plcInfo->slot )) {
		free( plcInfo );
		exit(50);
	}
	free( plcInfo );
	
	printf( "DONE!!\nComunication started...\n" );
	//unsigned int* tagDB, unsigned int* startByte, unsigned int* dataLength, unsigned char* data)
	while( 1 ) {
		//sleep( 1 );
		for( int l = 0; l < packCount; l++ )
			if( !PLCReadTags( &client, &addressPacked[l].db, &addressPacked[l].startByte, &addressPacked[l].dataLength, addressPacked[l].data ) );
				//for( int i = 0; i < addressPacked[l].dataLength; i++ )
					//printf( "DB: %d -- DATA BYTE %d -- VALUE: %d \n", addressPacked[l].db, i, addressPacked[l].data[i] );
	}
	/*
	sleep( 2 );
    int counter = 0;
    while( ( ++counter ) < 5000 ){
        sleep( 1 );
        float retVal[10];
        int ids[10];
        for(int i = 0; i < 10; i++ ){
			printf(" TAG ID: %d -- TYPE: %d -- ", VarTags[i].id, VarTags[i].type );
			ids[i] = VarTags[i].id; 
			retVal[i] = PLCReadTag( &client, &VarTags[i].db, &VarTags[i].address, &VarTags[i].addressBit, &VarTags[i].type );
            printf("DATA no[%d] value: %f\n", counter, retVal[i]);
         }
         int count = 10;
         writeTag( ids, retVal, &count );
         
        printf("\n");
    }
    
    printf("PLCDisc status: %d\n", PLCDisconnect( &client ));
*/


}

 
