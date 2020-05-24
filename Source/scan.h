#ifndef _SCAN_H_
#define _SCAN_H_

# include "type.h"

FILE * read;
FILE * output;

/* getToken get token and return TokenType */
TokenType getToken();

#endif