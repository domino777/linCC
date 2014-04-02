#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "linCC.h"
#include "libLog.h"
#include "getTrend.h"

void exitMsg( int signNo ){
    printf( "\n\n-----------------------------\n" );
    printf( "\n\nlinCC now exit. Goodbye ;)\n" );
    exit(0);
}

int main(void) {
    
    TREND* trendList;
    unsigned long trendCount;
    getTrends( &trendList, &trendCount );
    
    for( int i = 0; i < trendCount; i ++ ){
        printf( "TREND :  %d\n", trendList[i].trendNo );
        storeTrend( ( unsigned int *)&trendList[i].trendNo );
    }
}

 
