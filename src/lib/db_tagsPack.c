/*  
 *  db_tagsPack.c
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

#include "db_tagsPack.h"

int getPack ( unsigned long* packLength ) {
	
    MYSQL* sqlHndl;  

//  Create my SQL connection and get row count of vatList table
    linCCConnect( &sqlHndl );
    *packLength = linCCRowCount( sqlHndl, "varList" );
    if( *packLength == 0)
        return LINCC_NO_TAGS_FOUND;
    
//  Retrive tag list from databese
    DATA_ROWS* tagsList;
    
   
    int retVal;
    if ( retVal = linCCgetRows( sqlHndl, &tagsList, packLength, "SELECT DISTINCT tagType, tagDB, tagBYTE from varList ORDER BY tagDB, tagBYTE ASC" ))
        return retVal;
    
    const char* rowField;
    //  ------> addressPacked <------- is extern PLCData*    
    addressPacked = NULL;
    
    unsigned int tempType;
    unsigned int tempDB, tempPrevDB;
    unsigned int tempBYTE, tempStartByte, tempPrevByte;
    tempPrevByte = 0;
    unsigned int tempLength = 0;
    
    unsigned int counter = 0;
    
    for( unsigned long i = 0; i <= *packLength; i++ ){
		if( i < *packLength ) {
            tempType = ( unsigned int )strtol(( const char *)tagsList[i][0], NULL, 10 );
            tempDB   = ( unsigned int )strtol(( const char *)tagsList[i][1], NULL, 10 );
            tempBYTE = ( unsigned int )strtol(( const char *)tagsList[i][2], NULL, 10 );
        }
        
        if( i == 0 ) {
            tempPrevDB = tempDB;
            tempStartByte = tempBYTE;
        }
        
		switch( tempType ) {
            case 1: case 2:
                tempLength += 1;
            break;

            case 3: case 4:
                tempLength += 2;
            break;

            case 5: case 6:
                tempLength += 4;
            break;
            }

        if( tempDB != tempPrevDB || i == *packLength ) {
// Allocate/reallocate space for packed addresses
            addressPacked = realloc( addressPacked, sizeof( PLCData ) * ( counter + 1 ));
// Allocate space for store date by PLC reading library
            
            addressPacked[counter].data = malloc( tempLength );
            addressPacked[counter].db = tempPrevDB;
            addressPacked[counter].startByte = tempStartByte;
            addressPacked[counter].dataLength =  tempLength;
// Syncronize previous value with current value
            tempPrevDB = tempDB;
            tempStartByte = tempBYTE;
// Clearing length and inc counter
            tempLength = 0;
            counter++;
        }
        
        tempPrevDB = tempDB;
    }
    
    *packLength = counter;
    free( tagsList ); 
    linCCDisconnect( sqlHndl );	
    
}
