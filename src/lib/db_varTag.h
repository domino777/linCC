/*
 *	db_varTag.h
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
 
#ifndef _db_varTag_h
#define _db_varTag_h

#include "dbAccess.h"

#define DBVARTAG_MALLOC_ERROR       20
#define MYSQL_DB_VARTAG_QRY "SELECT id, tagType, tagDB, tagBYTE, tagBIT FROM varList"


// RETURN CODE DEFINITION
#define LINCC_RETURN_OK             0
#define LINCC_NO_TAGS_FOUND         1

typedef struct{
	unsigned int id;
	unsigned char type;
	unsigned int db;
	unsigned long address;
	unsigned char addressBit;
} TAG_VAR;

extern volatile TAG_VAR* VarTags;

int loadTags();

#endif // db_varTag_h
