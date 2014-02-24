#include "lib/db_varTag.h"
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

//byte MyDB32[256]; // byte is a portable type of snap7.h
//S7Object Client;
//lCConnData plcConnData;
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

    loadTags();


    
   
    //~ MYSQL_RES* sqlRes;
    //~ sqlRes = mysql_use_result( sqlHdl );

}

 
