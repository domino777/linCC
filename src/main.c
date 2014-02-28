#include "lib/db_varTag.h"
#include "lib/libPLC.h"
#include "lib/commInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


TAG_VAR* VarTags;

int main(void) {

    unsigned long rowCount;// = malloc( sizeof( unsigned long ));
    
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
	sleep( 5 );
    int counter = 0;
    while( ( ++counter ) < 50 ){
        sleep( 1 );
        for(int i = 0; i < 10; i++ ){
			float retVal;
			retVal = PLCReadTag( &client, &VarTags[i].db, &VarTags[i].address, &VarTags[i].type );
            printf("DATA no[%d] value: %f\n", counter, retVal);
            writeTag( &VarTags[i].id, &retVal );
         }
        printf("\n");
    }
    
    printf("PLCDisc status: %d\n", PLCDisconnect( &client ));
    


}

 
