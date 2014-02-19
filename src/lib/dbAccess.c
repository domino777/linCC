#include "dbAccess.h"

int linCCConnection( MYSQL* mySqlHndl ) {

//  Connecting to mariaDB database

    if ( mysql_real_connect( mySqlHndl, dbUrl, dbUser, dbPwd, dbBase,  0, NULL, 0 ) == NULL )
		return 1;
		
	return 0;
}

void linCCDisconnect( MYSQL* mySqlHndl ){
    mysql_close( mySqlHndl );
}


void linCCRowCount( MYSQL* mySqlHndl, char* tableName, long unsigned int* strLen ){
	
	char qryStr[256] = "SELECT COUNT(*) FROM ";
	
	for ( long unsigned int i = 0; i < *strLen; i++ )
		qryStr[ 21 + i ] = *( tableName + i );
		
	*strLen += 21;
	qryStr[ (int)(*strLen) + 1] = 0;
		
	const char* qryStrConst = qryStr;
	
	mysql_query( mySqlHndl, qryStrConst );
	
	MYSQL_RES *mySqlRes;
	mySqlRes = mysql_use_result( mySqlHndl );
	
	MYSQL_ROW mySqlRow;
	mySqlRow = mysql_fetch_row( mySqlRes );
	
    //return (unsigned long) mysql_num_rows(MYSQL_RES * );
}
