#include "lib/db_varTag.h"
#include "lib/libPLC.h"
#include <stdio.h>
#include <stdlib.h>


volatile TAG_VAR* VarTags;

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
S7Object* client;

int rack = 0;
int slot = 2;

  printf("-->%d\n", PLCConnect( client, "192.168.1.83", 0 , 2 ));
  int type = Int;
  int bytes = 0;
  int databl = 100;
  printf("DATA value: %f\n", PLCReadTag( client, &databl, &bytes, &type ));
  
  printf("%d", PLCDisconnect( client ));

  //  client = Cli_Create();
  //  printf("%d\n", Cli_ConnectTo( client, "192.168.1.83", 0, 3 ));
   
    //~ MYSQL_RES* sqlRes;
    //~ sqlRes = mysql_use_result( sqlHdl );

}

 
