CC=gcc

all:
	$(CC) main.c lib/dbAccess.c lib/db_varTag.c -o linCC `mysql_config --include --libs` -std=gnu99

clean:
	rm linCC
