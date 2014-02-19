CC=gcc

all:
	$(CC) main.c lib/dbAccess.c -o linCC `mysql_config --include --libs`

clean:
	rm linCC
