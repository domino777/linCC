/*
 *	db_varTag.c
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
 
#include "db_varTag.h"

int loadTags( unsigned long* rowCount ){
	
	MYSQL* sqlHndl;  
	
//  Create my SQL connection and get row count of vatList table
    sqlHndl = linCCConnect( );
    *rowCount = linCCRowCount( sqlHndl, "varList" );
    if( *rowCount == 0)
        return LINCC_NO_TAGS_FOUND;
    
//  ------> tags <------- is extern TAG_VAR*    
    VarTags = malloc( sizeof( TAG_VAR ) * *rowCount );
    if( !VarTags ) {
		printf( "Unable to allocate space for 'tags' by malloc in loadTags()\n" );
		exit( DBVARTAG_MALLOC_ERROR );
	}
    
//  Retrive tag list from databese
    DATA_ROWS* tagsList;
    tagsList = linCCgetRows( sqlHndl, MYSQL_DB_VARTAG_QRY );
    if ( !tagsList )
        return LINCC_NO_TAGS_FOUND;
    
    const char* rowField;
    printf ( "%d\n", *rowCount);
    for( unsigned long i = 0; i < *rowCount; i++ ){
//	Convert id char* field into unsigned int value
        VarTags[i].id = ( unsigned int )strtol(( const char *)tagsList[i][0], NULL, 10 );
        
//	Convert type char* field into unsigned int value
       VarTags[i].type = ( unsigned char )strtol(( const char *)tagsList[i][1], NULL, 10 );
        
//	Convert db char* field into unsigned int value
        VarTags[i].db = ( unsigned int )strtol(( const char *)tagsList[i][2], NULL, 10 );

//	Convert byte address char* field into unsigned long value        
        VarTags[i].address = ( unsigned long )strtol(( const char *)tagsList[i][3], NULL, 10 );
		
//	Convert bit of byte address char* field into unsigned int value
        VarTags[i].addressBit = ( unsigned char )strtol(( const char *)tagsList[i][4], NULL, 10 );
    }	
	
	free( tagsList ); 
    linCCDisconnect( sqlHndl );
    
    return LINCC_RETURN_OK;
}
