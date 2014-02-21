#ifndef dbAccess_h
#define dbAccess_h

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DATABASE CONNECTION DATA

#define dbUrl    "domyno.servehttp.com"
#define dbUser   "linCC"
#define dbPwd    "linCC"
#define dbBase   "linCC"

// EXIT ERROR DEFINITION
#define MYSQL_INIT_ERROR       1
#define MYSQL_CONN_ERROR       2
#define MYSQL_QURY_ERROR       3

typedef MYSQL_ROW *DATA_ROWS;

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
MYSQL* linCCConnect( );

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
 * Return the row count from a given table
 * 
 * ex:
 * unsigned long linCCRowCount( database_handler, table_name );
 * 
 * row count is returned
 * 
 */
long linCCRowCount( MYSQL* mySqlHndl, char* tableName );

/*
 * linCCgetRows( MYSQL* mySqlHndl, char* tableName )
 * 
 * Return the rows from a "SELECT cols_name FROM table_name ..." SQL query
 * 
 * ex:
 * DATA_ROWS var = linCCRowCount( database_handler, select_query );
 * 
 * rows are returnd
 * 
 */
DATA_ROWS linCCgetRows( MYSQL* mySqlHndl, const char* sqlQry );

#endif //dbAccess_h
