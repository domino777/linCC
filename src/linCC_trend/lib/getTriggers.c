/*  
 *  getTriggers.c
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

#include "getTriggers.h"

#define MYSQL_QRY_GET_TRG     "SELECT id, sampleTime, sampleFactor FROM trendSmplTime"

int getTriggers( TRIGGER_TIME** trgTime, unsigned long* trgTimeCount ) {
    
    int retVal = 0;
    unsigned int columnQry = 3;
    
    MYSQL* sqlHndl;
    DATA_ROWS* trgRows;
    
    if( retVal = linCCConnect( &sqlHndl ) )
        return retVal;
        
    if( retVal = linCCgetRows( sqlHndl, &trgRows, trgTimeCount, columnQry, MYSQL_QRY_GET_TRG ) )
        return retVal;

    *trgTime = malloc( sizeof( TRIGGER_TIME ) * *trgTimeCount );
    if( !( *trgTime )) {
        logMsg( LOG_INFO, "Unable to allocate space for *trendList in getTriggers\n" );
        exit( 1 );
    }
    
    for( unsigned long i = 0; i < *trgTimeCount; i++ ) {
//  Convert id char* field into unsigned int value
        ( *trgTime )[i].id        = ( unsigned int )strtol(( const char *)trgRows[i][0], NULL, 10 );
        
//  Convert  char* field into unsigned int value
        unsigned int time       =   ( unsigned int )strtol(( const char *)trgRows[i][1], NULL, 10 );
        unsigned long factor    =  ( unsigned long )strtol(( const char *)trgRows[i][2], NULL, 10 );

        if( factor == 2 )
            factor = 60;
        else if( factor == 3 )
            factor = 60 * 60;
        else if( factor == 4 )
            factor = 60 * 60 * 24;
        
        ( *trgTime )[i].timeBase  = ( unsigned long )time * factor;
    }

    linCCRowsFree( trgRows, trgTimeCount, columnQry ); 
    linCCDisconnect( sqlHndl );
    
    return 0;
}
