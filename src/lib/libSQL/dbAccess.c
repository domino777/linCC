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

 int linCCConnect( MYSQL** mySqlHndl ) {

//  mySQL handler creation
	*mySqlHndl = mysql_init( NULL );

//  Pointer error, service MUST TO BE CLOSE!!!!!!!
	if ( *mySqlHndl == NULL ) {
		printf( "%s", "\nUnable to create mySQL handler\n" );
		exit( MYSQL_INIT_ERROR );
	}
	
//  Try to connec to mariaDB database
    if ( !mysql_real_connect( *mySqlHndl, dbUrl, dbUser, dbPwd, dbBase,  0, NULL, 0 ))
		return MYSQL_CONN_ERROR ;
		
	return 0;
}

void linCCDisconnect( MYSQL* mySqlHndl ){
    mysql_close( mySqlHndl );
}


unsigned long linCCRowCount( MYSQL* mySqlHndl, char* tableName ){

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
	unsigned long retVal = strtol( rowField, NULL, 10 );
	mysql_free_result( mySqlRes );
	
	return retVal;
}

int linCCgetRows( MYSQL* mySqlHndl, DATA_ROWS** sqlRows, unsigned long* rowCount, unsigned int collOnQry, const char* sqlQry ){

//  SQL query
    if ( mysql_query( mySqlHndl, sqlQry ) )
        return MYSQL_QURY_ERROR;
    
    MYSQL_RES* mySqlRes;
    
    mySqlRes = mysql_store_result( mySqlHndl );  
    if( !mySqlRes )
        return MYSQL_STORE_ERROR;
	
//  Getting row
    MYSQL_ROW mySqlRow;	
    
//  Declare a local temp data rows
    DATA_ROWS* tempRows;
    tempRows = NULL;
    
    unsigned long LByte;
    int i = 0;
    
    for( i = 0; ( mySqlRow = mysql_fetch_row( mySqlRes )) != NULL; i++){

//      Reallocation of matrix array [][]
		tempRows = realloc( tempRows, 8 * ( i + 1 ));
        tempRows[i] = malloc( 8 * ( collOnQry ));
        
//      Getting string length for re-allocate space
        for( int pi = 0; pi < collOnQry; pi++ ) {
//          Temp allocation of string data + 1 ( null char )
            //printf( "strlen: %d\n", strlen( mySqlRow[pi] ) + 1 ); 
            //char* tempStr = malloc( strlen( mySqlRow[pi] ) + 1 );
            tempRows[i][pi] = malloc( strlen( mySqlRow[pi] ) + 1 );
            strcpy( ( char *)tempRows[i][pi], mySqlRow[pi] );
        }
        //printf( "SOME DATA1: %s -- DATA2: %s -- DATA3: %s\n", tempRows[i][0], tempRows[i][1], tempRows[i][2] );
        //LByte = LByte + strlen( ( const char *)mySqlRow ) + 1;
        //tempRows = realloc( tempRows, LByte );
        
//      Pointer error, service MUST TO BE CLOSE!!!!!!!
        //if( !tempRows ) {
		//	printf( "Unable to allocate space. realloc() error in linCCgetRow()\n" );
		//	exit( ALLOC_ERROR );
		//}
        //tempRows[i] = (void *)mySqlRow;
	}
	
    *sqlRows = tempRows;
	*rowCount = i;	
    mysql_free_result( mySqlRes );
    
    if ( i == 0 )
		return MYSQL_NO_ROW;
		
    return 0;
}

int linCCRowsFree( DATA_ROWS* sqlRows, unsigned long* rowCount, unsigned int* collCount ){
	
//  Memory freeeing
    for( int i = 0; i < *rowCount; i++ ) {
        for( int coll = 0; coll < *collCount; coll++ )
            free( sqlRows[i][coll] );
        free( sqlRows[i] );
    }   
    free( sqlRows );
}

int linCCWriteRow( MYSQL* mySqlHndl, const char* sqlQry ){
//  SQL query
    return mysql_query( mySqlHndl, sqlQry );	
}
