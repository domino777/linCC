/*  
 *  linCC.h
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

#ifndef _linCC_h_
#define _linCC_h_

typedef struct {
    unsigned int    trendNo;
    unsigned int    timeId;
} TREND;

typedef struct {
    unsigned int    id;
    unsigned long   timeBase;   //  Time base is calculated by multiply time value with time base value got from linCC table
} TRIGGER_TIME;

typedef struct {
    unsigned int    trgTimeId;
    unsigned long   timeBase;
    TREND*          trendNo;
} TREND_TRIGGER_THREAD;

#endif  // _linCC_h_
