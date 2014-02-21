#include "dbAccess.h"

MYSQL* linCCConnect() {

//  mySQL handler creation
	MYSQL*  mySqlHndl;
	mySqlHndl = mysql_init( NULL );

//  Check if handler was successfully created
	if ( mySqlHndl == NULL ) {
		printf( "%s", "\nUnable to create mySQL handler\n" );
		exit( MYSQL_INIT_ERROR );
	}
	
//  Try to connec to mariaDB database
    if ( mysql_real_connect( mySqlHndl, dbUrl, dbUser, dbPwd, dbBase,  0, NULL, 0 ) == NULL ) {
		printf( "%s", "\nUnable to establish connection to mySQL server\n" );
		exit( MYSQL_CONN_ERROR );
	}
		
	return mySqlHndl;
}

void linCCDisconnect( MYSQL* mySqlHndl ){
    mysql_close( mySqlHndl );
}


long linCCRowCount( MYSQL* mySqlHndl, char* tableName ){

//  SQL query for return table row count
	char qryStr[256] = "SELECT COUNT(*) FROM ";

//  Concatenating string
	strcat( qryStr, tableName );
		
	const char* qryStrConst = qryStr;

//  Send SQL query to Databases	
	mysql_query( mySqlHndl, qryStrConst );

//  Using resource
	MYSQL_RES *mySqlRes;
	mySqlRes = mysql_use_result( mySqlHndl );
	
//  Getting row
	MYSQL_ROW mySqlRow;
	mySqlRow = mysql_fetch_row( mySqlRes );

//	Convert row char* field into long value
	const char* rowField = mySqlRow[0];
	long retVal = strtol( rowField, NULL, 10 );
	mysql_free_result( mySqlRes );
	
	return retVal;
}

DATA_ROWS linCCgetRows( MYSQL* mySqlHndl, const char* sqlQry ){

//  SQL query
    if ( mysql_query( mySqlHndl, sqlQry ) ){
        printf ( "%s", "\nSQL query error in linCCgetRow\n" );
        exit( MYSQL_QURY_ERROR );
    }	
    
    MYSQL_RES* mySqlRes;
    mySqlRes = mysql_store_result( mySqlHndl );  
	
//  Getting row
    MYSQL_ROW mySqlRow;	
    DATA_ROWS sqlRow;
    for( int i = 0; ( mySqlRow = mysql_fetch_row( mySqlRes )) != NULL; i++)
		sqlRow[i] = mySqlRow;
			
    if ( !mySqlRow )
        mysql_free_result( mySqlRes );
		
	return sqlRow;
		
}
