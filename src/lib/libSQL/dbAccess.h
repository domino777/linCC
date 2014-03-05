/*
 *	dbAccess.h
 *
 *  "Copyright 2014 Mauro Ghedin"
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  or any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *
 *       @author         : Mauro Ghedin
 *       @contact        : domyno88 at gmail dot com
 *       @version        : 0.1
 *
 */

#ifndef _dbAccess_h
#define _dbAccess_h

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"

// DATABASE CONNECTION DATA

#define dbUrl    "domyno.servehttp.com"
//#define dbUrl    "localhost"
//#define dbUrl    "192.168.1.110"
#define dbUser   "linCC"
#define dbPwd    "linCC"
#define dbBase   "linCC"

typedef MYSQL_ROW *DATA_ROWS;

/**************************************************************************************************************************
 *
 *     For ERROR codes about exit() function or value returned by the
 *     the functions, refer to linCC wiki or open errors.h header in: 
 *     $linCCPATH/errors/
 * 
 *************************************************************************************************************************/ 
 
/***********************************************************************
 * int linCCConnection( MYSQL** mySqlHndl )
 * 
 * Connect to a SQL server and return a status if the connection is 
 * completed successfully or not
 * 
 * ex:
 * int retVal = linCCConnection( database_handler );
 * 
 * if function is unable to create handler. EXIT code is generated
 * if there are no issues 0.
 * 
 *************************************************************************************************************************/ 
int linCCConnect( MYSQL** mySqlHndl );

/**************************************************************************************************************************
 * void linCCDisconnect( MYSQL* mySqlHndl )
 * 
 * Disconnect from a SQL server
 * 
 * ex:
 * linCCDisconnect( database_handler );
 * 
 * no value returned
 * 
 *************************************************************************************************************************/ 
void linCCDisconnect( MYSQL* mySqlHndl );

/**************************************************************************************************************************
 * linCCRowCount( MYSQL* mySqlHndl, char* tableName )
 * 
 * Return the row count from a given table - the value returned is the 
 * total amount of row in a table
 * 
 * ex:
 * unsigned long linCCRowCount( database_handler, table_name );
 * 
 * row count is returned
 * 
 *************************************************************************************************************************/ 
unsigned long linCCRowCount( MYSQL* mySqlHndl, char* tableName );

/**************************************************************************************************************************
 * linCCgetRows( MYSQL* mySqlHndl, DATA_ROWS** sqlRows, unsigned long* rowCount, const char* sqlQry )
 * 
 * Return the rows from a "SELECT cols_name FROM table_name ..." SQL query
 * 
 * ex:
 * int retVal = linCCRowCount( database_handler, sqlRows_pointer, row_count, select_query );
 * 
 * By given pointer "DATA_ROWS** sqlRows", linCCgetRows return an allocated
 * pointer by malloc which contain an 3d array divided in:
 * [ROW][COLUMN][NULL TERMINATED STRING]
 * In row_count pointer is returned the numer of rows given by returl of the SQL query
 * 
 * function kill program with an arror code if realloc is uanble to allocate space
 * 
 * 0 returned if no issue are found
 * 
 *************************************************************************************************************************/ 
int linCCgetRows( MYSQL* mySqlHndl, DATA_ROWS** sqlRows, unsigned long* rowCount, const char* sqlQry );

/**************************************************************************************************************************
 * linCCWriteRow( MYSQL* mySqlHndl, const char* sqlQry )
 * 
 * SQL query to database
 * 
 * ex:
 * int retVale = long linCCWriteRow( database_handler, sql_query );
 * 
 * 0 returned if no issue are found
 * FOR THIS FUNCTION, THE ERRORS CODE GENERATED MUST BE REFERRED TO MARIA DB CLIENT MANUAL
 * 
 *************************************************************************************************************************/ 
int linCCWriteRow( MYSQL* mySqlHndl, const char* sqlQry );

#endif //dbAccess_h
