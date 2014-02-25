#include "lib/db_varTag.h"
#include "lib/libPLC.h"
#include <stdio.h>
#include <stdlib.h>

volatile TAG_VAR* tags;

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
S7Object *client;
int* rack;
int* slot;
*rack = 0;
*slot = 2;
    printf("%d\n", PLCConnect( client, "192.168.201.1", rack , slot ));
printf("%d", PLCDisconnect( client ));

    
   
    //~ MYSQL_RES* sqlRes;
    //~ sqlRes = mysql_use_result( sqlHdl );

}

 
