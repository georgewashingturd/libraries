////////////////////////////////////////////////////////////////////////////////
// Copyright(C) GreyGrolics 2004
//
// Filename: String.h
// Description: header file for String.c (String related functions)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Defs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

int StrLen(const char * source);
void StrCopy(const char * source, char * dest);
char * StrCat(const char * source, const char * dest);
void StrnCopy(const char * source, char * dest, int count);
char * StrnCat(const char * source, const char * dest, int count);
unsigned char isDelimiter(const char alpha, const char * delimiters);
char * StrTrim(const char *string, const char * delimiters, int lr);
char * ChangeCase(const char * string, int ul);
int StrFindSubString(const char * string, const char * substring, int Dir);
int StrCountToken(const char * string, const char * delimiters);
int StrTok(const char * string, const char * delimiters, char *** tokens);
