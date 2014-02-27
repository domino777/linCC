#include "lib/db_varTag.h"
#include "lib/libPLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


TAG_VAR* VarTags;

int main(void) {
	
S7Object* client = malloc( sizeof( S7Object ));
unsigned long* rowCount = malloc( sizeof( unsigned long ));

int rack = 0;
int slot = 2;
    
    
    
    printf( "Lettura tag da DB in corso\n" );
    if( loadTags( rowCount ) ) {
        printf( "Impossibile leggere lista tag da DB" );
        exit(1);
    }
    
    	printf("a tag: %d\n", VarTags[0].db);
   	
    printf("PLCConn status: %d\n", PLCConnect( client, "192.168.1.83", &rack , &slot ));

    int counter = 0;
    while( ( ++counter ) < 50 ){
        sleep( 1 );
        for(int i = 0; i < 3; i++ ){
			float retVal;
			retVal = PLCReadTag( client, &VarTags[i].db, &VarTags[i].address, &VarTags[i].type );
            printf("DATA no[%d] value: %f\n", counter, retVal);
            writeTag( &VarTags[i].id, &retVal );
         }
        printf("\n");
    }
    
    printf("PLCDisc status: %d\n", PLCDisconnect( client ));

    free( client );
    free( rowCount );
  
}

 
