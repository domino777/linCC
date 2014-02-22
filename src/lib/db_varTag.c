#include "db_varTag.h"

int loadTags(  ){
	
	MYSQL* sqlHndl;  
	unsigned long rowCount = 0;
	
//  Create my SQL connection and get row count of vatList table
    sqlHndl = linCCConnect( );
    rowCount = linCCRowCount( sqlHndl, "varList" );

//  Retrive tag list from databese
    DATA_ROWS tagsList;
    tagsList = linCCgetRows( sqlHndl, MYSQL_DB_VARTAG_QRY );

//  ------> tags <------- is extern TAG_VAR*    
    tags = malloc( sizeof( TAG_VAR ) * rowCount );
    
    const char* rowField;
    
    for( unsigned long i = 0; i < rowCount; i++ ){
//	Convert id char* field into unsigned int value
        rowField = tagsList[i][0];
        tags[i].id = ( unsigned int )strtol( rowField, NULL, 10 );
        
//	Convert type char* field into unsigned int value
        rowField = tagsList[i][1];	
        tags[i].type = ( unsigned char )strtol( rowField, NULL, 10 );
        
//	Convert db char* field into unsigned int value
        rowField = tagsList[i][2];	
        tags[i].db = ( unsigned int )strtol( rowField, NULL, 10 );

//	Convert byte address char* field into unsigned long value        
        rowField = tagsList[i][3];	
        tags[i].address = ( unsigned long )strtol( rowField, NULL, 10 );
		
//	Convert bit of byte address char* field into unsigned int value
        rowField = tagsList[i][4];	
        tags[i].addressBit = ( unsigned char )strtol( rowField, NULL, 10 );
    }	
		
    linCCDisconnect( sqlHndl );
}
