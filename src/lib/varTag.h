/*
 *	varTag.h
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
 
#ifndef _varTag_h
#define _varTag_h

#include "dbAccess.h"
#include "errors.h"

#define MYSQL_DB_VARTAG_QRY "SELECT id, tagType, tagDB, tagBYTE, tagBIT FROM varList"

typedef struct{
	unsigned int id;
	unsigned char type;
	unsigned int db;
	unsigned long address;
	unsigned char addressBit;
} TAG_VAR;

extern TAG_VAR* VarTags;

int loadTags( unsigned long* rowCount );
int writeTag( unsigned int* tagId, float* tagValue, unsigned int* tagsCount );

#endif // _varTag_h
