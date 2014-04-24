/*  
 *  getTrend.c
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

#include "getTrend.h"

#define MYSQL_QRY_GET_TREND "SELECT id, trendId, trendSmplTime FROM varTrend ORDER BY trendSmplTime ASC"

int getTrends( TREND** trendList, unsigned long* trendCount ) {
    
    int retVal = 0;
    unsigned int columnQry = 2;
    
    MYSQL* sqlHndl;
    DATA_ROWS* trendRows;
    
    if( retVal = linCCConnect( &sqlHndl ) )
        return retVal;
        
    if( retVal = linCCgetRows( sqlHndl, &trendRows, trendCount, columnQry, MYSQL_QRY_GET_TREND ) )
        return retVal;

    *trendList = malloc( sizeof( TREND ) * *trendCount );
    if( !( *trendList )) {
        logMsg( LOG_INFO, "Unable to allocate space for *trendList in getTrends\n" );
        exit( 1 );
    }

    for( unsigned long i = 0; i < *trendCount; i++ ) {
//  Convert id char* field into unsigned int value
        ( *trendList )[i].id        = ( unsigned int )strtol(( const char *)trendRows[i][0], NULL, 10 );
//  Convert type char* field into unsigned int value
        ( *trendList )[i].trendNo   = ( unsigned int )strtol(( const char *)trendRows[i][1], NULL, 10 );
//  Convert trendSmplTime filed into unsigned long value
        ( *trendList )[i].timeId    = ( unsigned int )strtol(( const char *)trendRows[i][2], NULL, 10 );
    }

    linCCRowsFree( trendRows, trendCount, columnQry ); 
    linCCDisconnect( sqlHndl );
    
    return 0;
}

int storeTrend( unsigned int* trendNo ) {
    
    int retVal = 0;
    char sqlQry[128];
    
    MYSQL* sqlHndl;
    
    sprintf( sqlQry, "CALL provaTrend( %d )", *trendNo );
    printf( "%s\n", sqlQry);
    if( retVal = linCCConnect( &sqlHndl ) )
        return retVal;
        
    retVal = linCCWriteRow( sqlHndl, sqlQry );
        
    linCCConnect( &sqlHndl );    
    
    if( retVal )
        return retVal;
        
    return 0;
}
