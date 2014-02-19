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
