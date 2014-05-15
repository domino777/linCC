#include "varTag.h"
#include "libPLC.h"
#include "commInfo.h"
#include "db_tagsPack.h"
#include "PLCComm.h"
#include "linCC.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "threads.h"
#include <signal.h>
#include "libLog.h"
#include "db_tagsWrite.h"


TAG_VAR* VarTags;
PLCData* addressPacked;


void exitMsg( int signNo ){
    printf( "\n\n-----------------------------\n" );
    printf( "\n\nlinCC now exit. Goodbye ;)\n" );
    exit(0);
}

int main(void) {

    unsigned long rowCount;
    unsigned int packCount;

    signal( SIGINT, exitMsg );
    
    logMsg( LOG_INFO, "Packing address...\n" );
    getPack( &packCount );
    logMsg( LOG_INFO,  "Package count: %d\n", packCount );
    for( int i = 0; i < packCount; i++)
        logMsg( LOG_INFO, "DB: %d : StrtByte: %d : Length: %d\n", addressPacked[i].db, addressPacked[i].startByte, addressPacked[i].dataLength );
    
    
    logMsg( LOG_INFO, "Reading tags dabase... \n" );
    if( loadTags( &rowCount ) ) {
        logMsg( LOG_INFO, "Impossibile leggere lista tag da DB" );
        exit(1);
    }
    
    logMsg( LOG_INFO, "Number of tags: %d\n", rowCount );
   
    logMsg( LOG_INFO, "Reading database of PLC connections...\n" );
   	PLC_CONN_INFO plcInfo;
   	linCCPLCgetInfo( &plcInfo );
   	
   	logMsg( LOG_INFO, "PLC Connection info:\n" );
   	logMsg( LOG_INFO, "PLC IP ADDRESS   : %s\n", plcInfo.ip );
   	logMsg( LOG_INFO, "PLC RACK         : %d\n", plcInfo.rack );
   	logMsg( LOG_INFO, "PLC SLOT         : %d\n", plcInfo.slot );
   	logMsg( LOG_INFO, "Try to connect to PLC...\n" );
   	
   	/*S7Object client;
    while( PLCConnect( &client, plcInfo.ip , &plcInfo.rack, &plcInfo.slot )) {
        logMsg( LOG_INFO, "linCC is unable to connect to the PLC... retry\n" );
        sleep( 1 );
    }*/

    int qryCount = 0;
    logMsg( LOG_INFO, "Comunication started...\n" );
   /* 
    PLCThread plcData;
    plcData.packCount = &packCount;
    plcData.client = &client;
    */
// Start PLC reading thread
  /*  pthread_t thread;
    threadPLCRead( &thread, &plcData );
    */
    unsigned long tagUpdateCount;
    unsigned long wTagVarCount;
    
    while( 1 ) {
        sleep( 1 );
        
        W_TAG_VAR* wTagVar;
        if( !getTagWrite( &wTagVar, &wTagVarCount ) ) {
            for( int i = 0; i < wTagVarCount; i++ ) {
                printf("tag id: %d -- Value %f\n", wTagVar[i].id, wTagVar[i].tagValue );
            }
            free( wTagVar );
        }
        else
            printf("no tag\n");
/*
// Check if PLC reading thread is still running
        if( threadCheck( &thread ) ) {
            logMsg( LOG_INFO, "PLC reading process exited, try to reconnect to PLC\n" );
            PLCDisconnect( &client );
            while( PLCConnect( &client, plcInfo.ip , &plcInfo.rack, &plcInfo.slot )) {
                logMsg( LOG_INFO, "linCC is unable to connect to the PLC... retry\n" );
                sleep( 1 );
            }
            logMsg( LOG_INFO, "PLC connected, try to star reading thread process\n" );
            threadPLCRead( &thread, &plcData );
            continue;
        }
        
        U_TAG_VAR* tagUpdate;
        
        varTagGetValues( VarTags, &tagUpdate, addressPacked, &rowCount, &tagUpdateCount, &packCount );
        logMsg( LOG_INFO, "TAG update count: %d\n", tagUpdateCount);
        writeTag( tagUpdate, &tagUpdateCount );
        
        qryCount++;
        logMsg( LOG_INFO, "\rCounter : %d", qryCount );
        fflush( stdout );
        free(tagUpdate);
        */
    }
}

 
