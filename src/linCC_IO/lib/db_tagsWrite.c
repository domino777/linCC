/*  
 *  db_tagsWrite.c
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

#include "db_tagsWrite.h"


int getTagWrite( W_TAG_VAR** wTagVar, unsigned long* wTagVarCount ) {
    
    MYSQL* sqlHndl;  

//  Create my SQL connection and get row count of vatList table
    linCCConnect( &sqlHndl );
    
    *wTagVarCount = linCCRowCount( sqlHndl, "varList", "wFlag=1" );
    if ( !*wTagVarCount )
        return 1;
    
//  Retrive tag list from databese
    DATA_ROWS* tagsList;

    unsigned int collCount = 6;
    int retVal;
    if ( retVal = linCCgetRows( sqlHndl, &tagsList, wTagVarCount, collCount, "SELECT DISTINCT id, tagType, tagDB, tagBYTE, tagBIT, wValue FROM varList WHERE wFlag=1 ORDER BY tagDB, tagBYTE ASC;" ))
        return retVal;
     
    W_TAG_VAR* tempwTagVar;
    tempwTagVar = NULL;
    
    printf( "tag wFlag : %d\n", *wTagVarCount );
    
    if( *wTagVarCount > 0 ) {
        tempwTagVar = malloc( sizeof( W_TAG_VAR ) * *wTagVarCount );
        if( !tempwTagVar ) {
            printf( "Unable to allocate space for 'w_tags' by malloc in gatTagWrite()\n" );
            exit( DBVARTAG_MALLOC_ERROR );
        }
        
        for( unsigned long i = 0; i < *wTagVarCount; i++ ){
            tempwTagVar[i].id           = ( unsigned int )strtol(( const char *)tagsList[i][0], NULL, 10 );
            tempwTagVar[i].type         = ( unsigned char )strtol(( const char *)tagsList[i][1], NULL, 10 );
            tempwTagVar[i].db           = ( unsigned int )strtol(( const char *)tagsList[i][2], NULL, 10 );
            tempwTagVar[i].address      = ( unsigned long )strtol(( const char *)tagsList[i][3], NULL, 10 );
            tempwTagVar[i].addressBit   = ( unsigned char )strtol(( const char *)tagsList[i][4], NULL, 10 );
            tempwTagVar[i].tagValue     = ( float )strtof(( const char *)tagsList[i][5], NULL );
        }
        
        *wTagVar = tempwTagVar;
    }
    else
        return 1;
    
    linCCRowsFree( tagsList, wTagVarCount, collCount );
    //free( tagsList );  
    linCCDisconnect( sqlHndl );
    
    return 0;
}

int clrTagWrite( W_TAG_VAR* wTagVar, unsigned long* wTagVarCount ) {
    MYSQL* sqlHndl;  

//  Create my SQL connection and get row count of varList table
    linCCConnect( &sqlHndl );
    
    int retVal = 0;
    char sqlQry[256];
    sqlQry[0] = NULL;
    
    for( unsigned long i = 0; i < *wTagVarCount; i++ ) {
        sprintf( sqlQry, "UPDATE varList SET wFlag=0 WHERE id=%d", wTagVar[i].id );
        if( ( retVal = linCCWriteRow( sqlHndl, ( const char* )sqlQry ) ))
            return retVal;
    }
    
    linCCDisconnect( sqlHndl );
    
    return 0;   
}
