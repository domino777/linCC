#include "db_varTag.h"

int loadTags(  ){
	
	MYSQL* sqlHndl;  
	unsigned long rowCount = 0;
	
//  Create my SQL connection and get row count of vatList table
    sqlHndl = linCCConnect( );
    rowCount = linCCRowCount( sqlHndl, "varList" );
    if( rowCount == 0)
        return LINCC_NO_TAGS_FOUND;
    
//  ------> tags <------- is extern TAG_VAR*    
    tags = malloc( sizeof( TAG_VAR ) * rowCount );
    if( !tags ) {
		printf( "Unable to allocate space for 'tags' by malloc in loadTags()\n" );
		exit( DBVARTAG_MALLOC_ERROR );
	}
    
//  Retrive tag list from databese
    DATA_ROWS* tagsList;
    tagsList = linCCgetRows( sqlHndl, MYSQL_DB_VARTAG_QRY );
    if ( !tagsList )
        return LINCC_NO_TAGS_FOUND;
    
    const char* rowField;
    printf ( "%d\n", rowCount);
    for( unsigned long i = 0; i < rowCount; i++ ){
//	Convert id char* field into unsigned int value
        tags[i].id = ( unsigned int )strtol(( const char *)tagsList[i][0], NULL, 10 );
        
//	Convert type char* field into unsigned int value
       tags[i].type = ( unsigned char )strtol(( const char *)tagsList[i][1], NULL, 10 );
        
//	Convert db char* field into unsigned int value
        tags[i].db = ( unsigned int )strtol(( const char *)tagsList[i][2], NULL, 10 );

//	Convert byte address char* field into unsigned long value        
        tags[i].address = ( unsigned long )strtol(( const char *)tagsList[i][3], NULL, 10 );
		
//	Convert bit of byte address char* field into unsigned int value
        tags[i].addressBit = ( unsigned char )strtol(( const char *)tagsList[i][4], NULL, 10 );
    }	
	
	free( tagsList ); 
    linCCDisconnect( sqlHndl );
    
    return LINCC_RETURN_OK;
}
