#ifndef dbAccess_h
#define dbAccess_h

#include <mysql.h>
#include <stdio.h>

// DATABASE CONNECTION DATA

#define dbUrl    "domyno.servehttp.com"
#define dbUser   "linCC"
#define dbPwd    "linCC"
#define dbBase   "linCC"


/*
 * int linCCConnection( MYSQL* mySqlHndl )
 * 
 * Connect to a SQL server and return a status if the connection is completed successfully or not
 * 
 * ex:
 * int retVal = linCCConnection( database_handler );
 * 
 * if successfully connected function return 0, else 1 value is returned
 * 
 */
int linCCConnection( MYSQL* mySqlHndl );

/*
 * void linCCDisconnect( MYSQL* mySqlHndl )
 * 
 * Disconnect from a SQL server
 * 
 * ex:
 * linCCDisconnect( database_handler );
 * 
 * no value returned
 * 
 */
void linCCDisconnect( MYSQL* mySqlHndl );

/*
 * linCCRowCount( MYSQL* mySqlHndl, char* tableName )
 * 
 * Disconnect from a SQL server
 * 
 * ex:
 * linCCDisconnect( database_handler );
 * 
 * no value returned
 * 
 */
int linCCRowCount( MYSQL* mySqlHndl, char* tableName );

#endif //dbAccess_h
