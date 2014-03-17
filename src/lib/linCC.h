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

typedef struct{
    unsigned int id;
    float tagValue;
} U_TAG_VAR;

typedef struct{
	unsigned int id;
	unsigned char type;
	unsigned int db;
	unsigned long address;
	unsigned char addressBit;
	float tagValue;
} TAG_VAR;

typedef struct {
    unsigned int db;
    unsigned int startByte;
    unsigned int dataLength;
    unsigned char* data;
} PLCData;

typedef struct{
    unsigned int id;
    unsigned int rack;
    unsigned int slot;
    unsigned int port;
    char ip[16];	
} PLC_CONN_INFO;

enum variableType { noType, Bool, Byte, Word, Int, DInt, Real };

#endif  // _linCC_h_
