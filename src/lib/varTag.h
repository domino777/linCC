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
#include "linCC.h"

#define MYSQL_DB_VARTAG_QRY "SELECT id, tagType, tagAccess, tagDB, tagBYTE, tagBIT FROM varList ORDER BY tagType, tagDB, tagBYTE ASC"

extern TAG_VAR* VarTags;

/**************************************************************************************************************************
 * int loadTags( unsigned long* rowCount );
 * 
 * Connect to linCC sql database and retrive all variables present into the database of varList
 * and store tag's specification into VarTags that is a global pointer
 * loadTags also allocate space with malloc and realloc for VarTags
 * 
 * ex:
 * int retVal = loadTags( row_count )
 * 
 * By given pointer "row_count", the number of variable storend into VarTags is passed
 * 
 * if function is unable to create handler. EXIT code is generated
 * if there are no issues 0 is returned.
 * 
 *************************************************************************************************************************/ 
int loadTags( unsigned long* rowCount );

/**************************************************************************************************************************
 * int writeTag( U_TAG_VAR* tagVar, unsigned long* tagsCount )
 * 
 * Write tags value passed by U_TAG_VAR into linCC varList database
 * 
 * ex:
 * int retVal = writeTag( tag_Var, tag_count_of_tag_var )
 * 
 * if there are no issues 0 is returned.
 * 
 *************************************************************************************************************************/ 
int writeTag( U_TAG_VAR* tagVar, unsigned long* tagsCount );

#endif // _varTag_h
