/*
 *	dbAccess.c
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

DATA_ROWS* linCCgetRows( MYSQL* mySqlHndl, const char* sqlQry ){

//  SQL query
    if ( mysql_query( mySqlHndl, sqlQry ) ){
        printf ( "%s", "SQL query error in linCCgetRow\n" );
        exit( MYSQL_QURY_ERROR );
    }	
    
    MYSQL_RES* mySqlRes;
    mySqlRes = mysql_store_result( mySqlHndl );  
	
//  Getting row
    MYSQL_ROW mySqlRow;	
    DATA_ROWS* sqlRows;
    sqlRows = NULL;
    
    unsigned long LByte;
    int i = 0;
    
    for( i = 0; ( mySqlRow = mysql_fetch_row( mySqlRes )) != NULL; i++){
        //LByte = LByte + sizeof( **mySqlRow );
        LByte = LByte + strlen( ( const char *)mySqlRow ) + 1;
        sqlRows = realloc( sqlRows, LByte );
        if( !sqlRows ) {
			printf( "Unable to allocate space. realloc() error in linCCgetRow()\n" );
			exit( ALLOC_ERROR );
		}
        sqlRows[i] = (void *)mySqlRow;
	}
		
    if ( !mySqlRow )
        mysql_free_result( mySqlRes );
    
    if ( i == 0 )
		return NULL;
		
    return sqlRows;	
}

int linCCWriteRow( MYSQL* mySqlHndl, const char* sqlQry ){
//  SQL query
    return mysql_query( mySqlHndl, sqlQry );	
}
