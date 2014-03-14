/*  
 *  PLCComm.c
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

#include "PLCComm.h"

int varTagGetValues ( TAG_VAR* tagList, PLCData* dataPackage, unsigned long* tagCount, unsigned int *packageCount ) {
    
    for( unsigned long i = 0; i < *tagCount; i++ ) {
		
		int pkgIndex = 0;
		while( tagList[i].db != dataPackage[pkgIndex].db )
		    pkgIndex++;
		  
       // tagList[i].tagValue = ( float )dataPackage[pkgIndex].data[ ( dataPackage[pkgIndex].startByte - tagList[i].address ) ];
        
//  Getting plc's INT or WORD value
        if( tagList[i].type == Word || tagList[i].type == Int ) {		 
//  Read error detection

             int tempVar = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte ) ] << 8;
             tagList[i].tagValue = ( float )( tempVar = tempVar | dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 1 ) ] );
        }
    
       else if( tagList[i].type  == Real ) {

           float tempFloat;
           *((unsigned char*)(&tempFloat) + 3) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 0 ) ];
           *((unsigned char*)(&tempFloat) + 2) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 1 ) ];
           *((unsigned char*)(&tempFloat) + 1) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 2 ) ];
           *((unsigned char*)(&tempFloat) + 0) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 3 ) ];

            tagList[i].tagValue = tempFloat;
        }
    
        else if( tagList[i].type  == Bool ) {
            if ( dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte ) ] & ( 0x0001 << tagList[i].addressBit ) )
                tagList[i].tagValue = 1.0;
        }
    }
    
    return 0;
}
