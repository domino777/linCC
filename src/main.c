#include "lib/db_varTag.h"
#include "lib/libPLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


TAG_VAR* VarTags;

int main(void) {
	
	//~ FILE* confFile;
	//~ char ch;
	//~ 
	//~ confFile = fopen( "./config/plcConn.conf", "r" );
	//~ 
	//~ while( ( ch = fgetc( confFile ) ) != EOF )
    //~ printf("%c",ch);
	//~ 
	//~ fclose( confFile );
	
//----------------------------------------------------------------------

    //~ Client = Cli_Create();
    //~ printf ( "%d\n", Cli_ConnectTo( Client, "10.1.1.200", 0, 2 ));
    //~ 
    //~ TS7BlocksList BList;
    //~ Cli_ListBlocks(Client, &BList);
    //~ printf ( "%d\n", BList.FBCount );

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

    //for( int i = 0; i < *rowCount; i++ )
    int counter = 0;
    while( ( ++counter ) < 50 ){
        sleep( 1 );
        for(int i = 0; i < 5; i++ )
            printf("DATA no[%d] value: %f\n", counter, PLCReadTag( client, &VarTags[i].db, &VarTags[i].address, &VarTags[i].type ));
        printf("\n");
    }
    
    printf("PLCDisc status: %d\n", PLCDisconnect( client ));

  //  client = Cli_Create();
  //  printf("%d\n", Cli_ConnectTo( client, "192.168.1.83", 0, 3 ));
   
    //~ MYSQL_RES* sqlRes;
    //~ sqlRes = mysql_use_result( sqlHdl );
    free( client );
    free( rowCount );

}

 
