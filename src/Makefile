CC=gcc

all:
	$(CC) main.c lib/libPLC.c lib/dbAccess.c lib/db_varTag.c -o linCC `mysql_config --include --libs` -lsnap7 -I./lib/ -std=gnu99

clean:
	rm linCC
