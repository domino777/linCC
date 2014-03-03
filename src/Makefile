CC=gcc

all:
	$(CC) main.c lib/dbAccess.c lib/varTag.c lib/libPLC.c lib/snap7.c lib/commInfo.c lib/db_tagsPack.c -o linCC `mysql_config --include --libs` -lsnap7 -I./lib/ -I./error/ -std=gnu99
# $(CC) main.c lib/dbAccess.c lib/db_varTag.c lib/libPLC.c lib/snap7.c -o linCC `mysql_config --include --libs` -lsnap7 -I./lib/ -std=gnu99
clean:
	rm linCC
