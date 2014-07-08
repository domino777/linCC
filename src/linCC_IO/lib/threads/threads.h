/*  
 *  threads.h
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

#ifndef _threads_h_
#define _threads_h_

#include <pthread.h>
#include <signal.h>
#include "libPLC.h"
#include "linCC.h"

unsigned char pausePLCReadThread;
unsigned char PLCThreadStandBy;

extern PLCData* addressPacked;

int threadPLCRead( pthread_t* thread, PLCThread* threadData );

int threadCheck( pthread_t* thread );

#endif  // _threads_h_
