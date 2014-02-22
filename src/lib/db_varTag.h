#ifndef db_varTag_h
#define db_varTag_h

#include "dbAccess.h"

#define MYSQL_DB_VARTAG_QRY "SELECT id, tagType, tagDB, tagBYTE, tagBIT FROM varList"

typedef struct{
	unsigned int id;
	unsigned char type;
	unsigned int db;
	unsigned long address;
	unsigned char addressBit;
} TAG_VAR;

extern volatile TAG_VAR* tags;

int loadTags(  );

#endif // db_varTag_h
