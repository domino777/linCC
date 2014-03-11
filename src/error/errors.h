/*
 *	errors.h
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
 
#ifndef _errors_h
#define _errors_h


// *********************************************************************
//    dbAccess return errors
// *********************************************************************

// linCCConnect RETURN
#define MYSQL_CONN_ERROR            50

// linCCgetRows RETURN
#define MYSQL_NO_ROW                51
#define MYSQL_QURY_ERROR            52
#define MYSQL_STORE_ERROR           53

// *********************************************************************
//    db_varTag return errors
// *********************************************************************

// loadTags RETURN
#define LINCC_NO_TAGS_FOUND         60


// *********************************************************************
//
//                        EXIT ERROR
//
// *********************************************************************

// linCCConnect EXIT ERROR
#define MYSQL_INIT_ERROR            1

// linCCgetRows EXIT ERROR
#define ALLOC_ERROR                 2

// loadTags EXIT ERROR
#define DBVARTAG_MALLOC_ERROR       3


#define GETPACK_REALLOC_EXIT        4

#endif // _errors_h
