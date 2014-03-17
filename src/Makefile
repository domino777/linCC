CC=gcc

all:
	$(CC) main.c lib/libSQL/dbAccess.c lib/varTag.c lib/s7Comm/libPLC.c lib/snap7.c lib/commInfo.c lib/db_tagsPack.c lib/PLCComm.c lib/threads/threads.c -o linCC `mysql_config --include --libs` -lsnap7 -I./lib/libSQL/ -I./lib/ -I./error/ -I./lib/threads -I./lib/s7Comm/ -std=gnu99 -pthread
# $(CC) main.c lib/dbAccess.c lib/db_varTag.c lib/libPLC.c lib/snap7.c -o linCC `mysql_config --include --libs` -lsnap7 -I./lib/ -std=gnu99
clean:
	rm linCC
