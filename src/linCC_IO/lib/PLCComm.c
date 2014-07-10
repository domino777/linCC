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

unsigned char firstRun = 0;

int varTagGetValues ( TAG_VAR* tagList, U_TAG_VAR** tagListUp, PLCData* dataPackage, unsigned long* tagCount, unsigned long* updateTagCount, unsigned int *packageCount ) {
    
    float retTempFloat = 0.0;
    
    U_TAG_VAR* tempVar;
    tempVar = NULL;
    
    unsigned long tagCountUp = 0;
    
    for( unsigned long i = 0; i < *tagCount; i++ ) {

        int pkgIndex = 0;
        while( tagList[i].db != dataPackage[pkgIndex].db )
            pkgIndex++;

//  Getting plc's INT or WORD value
        if( tagList[i].type == Word || tagList[i].type == Int ) {
        
            int tempVar = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte ) ] << 8;
            tempVar     = tempVar = tempVar | dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 1 ) ];
            if( tagList[i].type == Word )
                retTempFloat = ( float )( unsigned int )tempVar;
            else
                retTempFloat = ( float )( short int )tempVar;
        }
        
        else if( tagList[i].type  == DWord || tagList[i].type  == DInt ) {
        
            int tempLong;
            *((unsigned char*)(&tempLong) + 3) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 0 ) ];
            *((unsigned char*)(&tempLong) + 2) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 1 ) ];
            *((unsigned char*)(&tempLong) + 1) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 2 ) ];
            *((unsigned char*)(&tempLong) + 0) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 3 ) ];
            
            if( tagList[i].type == DWord )
                retTempFloat = ( float )( unsigned int )tempLong;
            else
                retTempFloat = ( float )( int )tempLong;
                
        }
    
        else if( tagList[i].type  == Real ) {

           float tempFloat;
           *((unsigned char*)(&tempFloat) + 3) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 0 ) ];
           *((unsigned char*)(&tempFloat) + 2) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 1 ) ];
           *((unsigned char*)(&tempFloat) + 1) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 2 ) ];
           *((unsigned char*)(&tempFloat) + 0) = dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte + 3 ) ];

           retTempFloat = tempFloat;
        }
    
        else if( tagList[i].type  == Bool ) {
            if ( dataPackage[pkgIndex].data[ ( tagList[i].address - dataPackage[pkgIndex].startByte ) ] & ( 0x0001 << tagList[i].addressBit ) )
                retTempFloat = 1.0;
        }
        
        if( tagList[i].tagValue != retTempFloat || !firstRun ) {
            tagCountUp++;
            tempVar = realloc( tempVar, sizeof( U_TAG_VAR ) * tagCountUp );
            tempVar[ tagCountUp - 1 ].id = tagList[i].id;
            tempVar[ tagCountUp - 1 ].tagValue = retTempFloat;
        }

        tagList[i].tagValue = retTempFloat;
    }
    
    *updateTagCount = tagCountUp;
    *tagListUp = tempVar;
    firstRun = 1;
    
    return 0;
}
