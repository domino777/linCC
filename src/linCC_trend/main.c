#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "linCC.h"
#include "libLog.h"
#include "getTrend.h"
#include "getTriggers.h"

void exitMsg( int signNo ){
    printf( "\n\n-----------------------------\n" );
    printf( "\n\nlinCC now exit. Goodbye ;)\n" );
    exit(0);
}

int main(void) {
    
    TREND* trendList;
    unsigned long trendCount;
    getTrends( &trendList, &trendCount );
    
    TRIGGER_TIME* trgTime;
    unsigned long trgTimeCount;
    getTriggers( &trgTime, &trgTimeCount );
    for( int i = 0; i < trgTimeCount; i++)
    printf( "trigger id: %d --- trigger time: %d\n", trgTime[i].id, trgTime[i].timeBase );
    
    printf("Getting max time value...\n" );
    unsigned long maxTime;
    for( unsigned long trgIdx = 0; trgIdx < trgTimeCount - 1; trgIdx++ ) {
        if( trgTime[ trgIdx ].timeBase > trgTime[ trgIdx + 1 ].timeBase )
            maxTime = trgTime[ trgIdx ].timeBase;
        else
            maxTime = trgTime[ trgIdx + 1].timeBase;
    }
    
    printf("Max time: %d\n", maxTime );
    
    unsigned long secondCount = 0;
    while( 1 ) {
        sleep( 1 );
        
        secondCount++;
        
        for( unsigned long trgIdx = 0; trgIdx < trgTimeCount; trgIdx++ ) {
            if( secondCount % trgTime[ trgIdx ].timeBase == 0 ) {
                printf( "Time value second counter at: %d\n", secondCount );
                for( unsigned long trndIdx = 0; trndIdx < trendCount; trndIdx++ )
                    if( trgTime[ trgIdx ].id == trendList[ trndIdx ].timeId ) {
                        printf("Trend no: %d\n", trendList[ trndIdx ].trendNo );
                        printf("ERROR CODE: %d\n", storeTrend( &( trendList[ trndIdx ].trendNo ) ));
                    }
                }
        }
        
        if( secondCount >= maxTime )
            secondCount = 0;
    }
    //~ for( int i = 0; i < trendCount; i ++ ){
        //~ printf( "TREND :  %d\n", trendList[i].trendNo );
        //~ storeTrend( ( unsigned int *)&trendList[i].trendNo );
    //~ }
}

 
