/*  
 *  db_tagsPack.h
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

#ifndef _db_tagsPack_h_
#define _db_tagsPack_h_

#include "dbAccess.h"
#include "errors.h"

typedef struct {
    unsigned int db;
    unsigned int startByte;
    unsigned int dataLength;
    unsigned char* data;
} PLCData;

extern PLCData* addressPacked;

/**************************************************************************************************************************
 * getPack ( unsigned long* packLength )
 * 
 * Pack the variable addresses into a PLCData structure. Into PLCData will be
 * stored the data read from DB's PLC
 * 
 * ex:
 * int retVal = getPack ( packLength );
 * 
 * By given pointer "unsigned long* packLength", getPack return the bumber of
 * package of packed address created into global PLCData
 * 
 * function kill program with an arror code if realloc/malloc is uanble to re-allocate/allocate space
 * 
 * 0 returned if no issue are found
 * 
 *************************************************************************************************************************/ 
int getPack ( unsigned long* packLength );

#endif  // _db_tagsPack_h_
