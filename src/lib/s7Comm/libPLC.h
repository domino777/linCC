/*
 *	libPLC.h
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

#ifndef _libPLC_h
#define _libPLC_h

#include "snap7.h"
#include <stdio.h>
#include "errors.h"
#include "linCC.h"

#define snap7PLCIp           192.168.102.1
#define snap7PLCRack         0
#define snap7PLCSlot         2

#define _BYTE_1_             1
#define _BYTE_2_             2
#define _BYTE_4_             4

#define PLC_DB_READ_ERROR    0xFFFFFFFF

/**************************************************************************************************************************
 *
 *     For ERROR codes about exit() function or value returned by the
 *     the functions, refer to linCC wiki or open errors.h header in: 
 *     $linCCPATH/errors/
 * 
 *************************************************************************************************************************/ 
 
/**************************************************************************************************************************
 * int PLCConnect( S7Object* plcClient, const char* plcIp, int* plcRack, int* plcSlot )
 * 
 * Connect to a Siemens S7 plc
 * 
 * ex:
 * int retVal = PLCConnect( plc_client_pointer, "192.168.55.155", plc_rack, plc_slot )
 * 
 * if there are no issues 0 is returned.
 * 
 *************************************************************************************************************************/ 
int PLCConnect( S7Object* plcClient, const char* plcIp, int* plcRack, int* plcSlot );

/**************************************************************************************************************************
 * int PLCDisconnect( S7Object* plcClient )
 * 
 * Disconnect from a Siemens S7 plc
 * 
 * ex:
 * int retVal = PLCDisconnect( plc_client_pointer )
 * 
 * if there are no issues 0 is returned.
 * 
 *************************************************************************************************************************/ 
int PLCDisconnect( S7Object* plcClient );

/**************************************************************************************************************************
 *
 * <<<<<    DEPRECATED   >>>>>> <<<<<    DEPRECATED   >>>>>> <<<<<    DEPRECATED   >>>>>> <<<<<    DEPRECATED   >>>>>> <<<<<    DEPRECATED   >>>>>>
 * 
 * float PLCReadTag( S7Object* plcClient, unsigned int* tagDB, unsigned long* tagByte, unsigned char* tagBit, unsigned char* varType )
 * 
 * Read a variable form PLC's DB by given parameter and return the value read
 * 
 * ex:
 * float retVal = PLCReadTag( plc_client_pointer, db_no, db_byte, db_bit, var_type )
 * 
 * if you want read: DB25.DBW80
 * db_no = 25 -- db_byte = 80 -- db_bit = ( not important if you read not bool value )
 * var_type is defined in linCC.h by enum variableType
 * 
 * if there are no issues a valid value is returned, if an error occurs a 0xFFFFFFFF ( #NAN ) value is returned
 * 
 * <<<<<    DEPRECATED   >>>>>> <<<<<    DEPRECATED   >>>>>> <<<<<    DEPRECATED   >>>>>> <<<<<    DEPRECATED   >>>>>> <<<<<    DEPRECATED   >>>>>>
 * 
 *************************************************************************************************************************/ 
float PLCReadTag( S7Object* plcClient, unsigned int* tagDB, unsigned long* tagByte, unsigned char* tagBit, unsigned char* varType );

/**************************************************************************************************************************
 * int PLCReadTags( S7Object* plcClient, unsigned int* tagDB, unsigned long* startByte, unsigned long* dataLength, unsigned char* data)
 * 
 * Read a variable form PLC's DB by given parameter and return the value read
 * 
 * ex:
 * int retVal = PLCReadTags( plc_client_pointer, db_no, db_Startbyte, no_of_byte_to_read, data_pointer)
 * 
 * if you want read: DB25 from byte 50 to 250
 * db_no = 25 -- db_Startbyte = 50 -- no_of_byte_to_read = 200
 * 
 * if there are no issues 0 is returned.
 * 
 *************************************************************************************************************************/ 
int PLCReadTags( S7Object* plcClient, unsigned int* tagDB, unsigned long* startByte, unsigned long* dataLength, unsigned char* data);

#endif // _libPLC_h
