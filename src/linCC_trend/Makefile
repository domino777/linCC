CC=gcc

all:
	$(CC) main.c lib/libSQL/dbAccess.c lib/libLog/libLog.c -o linCC_trend `mysql_config --include --libs` -lsnap7 -I./lib/libSQL/ -I./lib/ -I./error/ -I./lib/libLog/ -std=gnu99 -pthread
# $(CC) main.c lib/dbAccess.c lib/db_varTag.c lib/libPLC.c lib/snap7.c -o linCC `mysql_config --include --libs` -lsnap7 -I./lib/ -std=gnu99
clean:
	rm linCC
