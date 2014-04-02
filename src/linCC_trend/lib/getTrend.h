/*  
 *  getTrend.h
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

#ifndef _getTrend_h_
#define _getTrend_h_

#include "linCC.h"
#include "libLog.h"
#include "error.h"
#include "dbAccess.h"

/**************************************************************************************************************************
 *
 *     For ERROR codes about exit() function or value returned by the
 *     the functions, refer to linCC wiki or errors.h header in: 
 *     $linCCPATH/errors/
 * 
 *************************************************************************************************************************/ 
 
/**************************************************************************************************************************
 * int getTrends( TREND** trendList, unsigned long* trendCount )
 * 
 * Connect to sql server for getting trend list
 * 
 * ex:
 * int retVal = getTrends( &trend_List, trend_Count )
 * 
 * if function is unable to create handler. EXIT code is generated
 * if there are no issues 0 is returnd.
 * 
 *************************************************************************************************************************/ 
int getTrends( TREND** trendList, unsigned long* trendCount );

/**************************************************************************************************************************
 * int getTrends( TREND** trendList, unsigned long* trendCount )
 * 
 * Connect to sql server for getting trend list
 * 
 * ex:
 * int retVal = getTrends( &trend_List, trend_Count )
 * 
 * if function is unable to create handler. EXIT code is generated
 * if there are no issues 0 is returnd.
 * 
 *************************************************************************************************************************/ 
int storeTrend( unsigned int* trendNo );

#endif  // _getTrend_h_
