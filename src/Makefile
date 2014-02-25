CC=gcc

all:
	$(CC) main.c lib/dbAccess.c lib/db_varTag.c lib/libPLC.c -o linCC `mysql_config --include --libs` -lsnap7 -I./lib/ -L./lib/ -std=gnu99

clean:
	rm linCC
