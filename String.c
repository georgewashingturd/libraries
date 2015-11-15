////////////////////////////////////////////////////////////////////////////////
// Copyright(C) GreyGrolics 2004
//
// Filename: String.c
// Description: String related functions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes and external references
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h> // this is for definition of NULL

////////////////////////////////////////////////////////////////////////////////
// Defs
////////////////////////////////////////////////////////////////////////////////

#define DELIMITER 1     // only used for tokenizer
#define STRING 0        // only used for tokenizer

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          StrLen
//
//   Type:          Function
//
//   Description:   To count the length of a NULL terminated string
//
//   Inputs:        source - the string
//
//   Outputs:       int - the length of the string
//
////////////////////////////////////////////////////////////////////////////////
int StrLen(const char * source)
{
    int i = 0;

    if (source == NULL)
        return 0;

    while(source[i] != '\0')
        i++;

    return i;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          StrCopy
//
//   Type:          Function
//
//   Description:   To copy a string to another
//
//   Inputs:        source - the source string
//                  dest - the destination string
//
//   Outputs:       dest - contains the resulting string
//
////////////////////////////////////////////////////////////////////////////////
void StrCopy(const char * source, char * dest)
{
    int i = 0;

    if (source == NULL || dest == NULL)
        return;

    while (source[i]!='\0')
    {
        dest[i] = source[i];
        i++;
    }

    dest[i] = '\0';
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          StrCat
//
//   Type:          Function
//
//   Description:   To concatenate two strings
//
//   Inputs:        source - the head
//                  dest - the tail
//
//   Outputs:       char * - the combined string
//
////////////////////////////////////////////////////////////////////////////////
char * StrCat(const char * source, const char * dest)
{
    char * result;
    int src;

    if (source == NULL || dest == NULL)
        return NULL;

    src = StrLen(source);
    result = (char *)malloc(sizeof(char) * (src + StrLen(dest) + 1));

    if (result != NULL)
        *result = '\0';
    else
        return result;

    StrCopy(source,result);
    StrCopy(dest,&(result[src]));

    return result;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          StrnCopy
//
//   Type:          Function
//
//   Description:   To copy a string to another
//
//   Inputs:        source - the source string
//                  dest - the destination string
//                  count - how many characters to copy
//
//   Outputs:       dest - contains the resulting string
//
////////////////////////////////////////////////////////////////////////////////
void StrnCopy(const char * source, char * dest, int count)
{
    int i;
    int length;

    if (source == NULL || dest == NULL)
    {
        return;
    }

    length = StrLen(source);

    if (count > length)
        count = length;

    for (i = 0; i < count ; i++)
    {
        dest[i] = source[i];
    }

    dest[i] = '\0';
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          StrnCat
//
//   Type:          Function
//
//   Description:   To concatenate two strings
//
//   Inputs:        source - the head
//                  dest - the tail
//                  count - the length of the resulting string
//
//   Outputs:       char * - the combined string
//
////////////////////////////////////////////////////////////////////////////////
char * StrnCat(const char * source, const char * dest, int count)
{
    char * result;
    int length;
    int d_length;

    if (source == NULL || dest == NULL)
        return NULL;    // fatal error

    length = StrLen(source);
    d_length = StrLen(dest);

    if (count <= length)
    {
        result = (char *)malloc(sizeof(char));
        if (result != NULL)
            *result = '\0';
        return result;
    }

    if (count > length + d_length)
        count = length + d_length;

    result = (char *)malloc(sizeof(char) * (count + 1));

    if (result != NULL)
        *result = '\0';
    else
        return result;      // fatal error

    StrCopy(source,result);
    StrnCopy(dest,&(result[length]),count-length);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          isDelimiter
//
//   Type:          Function
//
//   Description:   To check whether a character is a delimiter, delimiter can be
//                  anything, it doesn't need to be white space
//
//   Inputs:        alpha - the character to test
//                  delimiters - array of delimiters, must be '\0' terminated
//                               if delimiters is NULL it will default to space
//                               and tab, delimiters can be any characters
//
//   Outputs:       unsigned char - 1 character is delimiter
//                                  0 otherwise
//
////////////////////////////////////////////////////////////////////////////////
unsigned char isDelimiter(const char alpha, const char * delimiters)
{
    int i = 0;
    unsigned char found = 0;

    if (delimiters == NULL)
    {
        if (alpha == ' ' || alpha == '\t')
            found = 1;
    }
    else
    {
        while (delimiters[i] != '\0' && found == 0)
        {
            if (alpha == delimiters[i])
                found = 1;
            i++;
        }
    }

    return found;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          StrTrim
//
//   Type:          Function
//
//   Description:   To trim a string of the delimiters, delimiters can be any
//                  characters, if it's NULL it defaults to tabs and spaces
//
//   Inputs:        string - string to be trimmed
//                  delimiters - array of delimiters, must be '\0' terminated
//                               if delimiters is NULL it will default to space
//                               and tab
//                  lr - left(1), right(2), or both ends trim(3)
//
//   Outputs:       char * - the trimmed string
//
////////////////////////////////////////////////////////////////////////////////
char * StrTrim(const char *string, const char * delimiters, int lr)
{
    int length;
    int start = 0;
    int end;
    int i = 0;
    char * result;

    if (string == NULL)
        return NULL;

    length = StrLen(string);
    end = length;

    if (length <= 0)
    {
        result = (char *)malloc(sizeof(char));
        if (result != NULL)
            *result = '\0';
        return result;
    }

    // 1 left trim, 2 right trim, 3 both end trim
    if (lr == 1 || lr == 3)
    {
        while(isDelimiter(string[i],delimiters) && i < length)
        {
            i++;
        }

        start = i;
    }

    if (lr == 2 || lr == 3)
    {
        i = length - 1;

        while(isDelimiter(string[i],delimiters) && i >= 0)
        {
            i--;
        }

        end = i;
    }

    if (end < 0)
        end = start - 1;

    result = (char *)malloc(sizeof(char) * (end - start + 2));
    if (result == NULL)
        return result;

    StrnCopy(&(string[start]),result,end-start+1);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          ChangeCase
//
//   Type:          Function
//
//   Description:   To change the case of a string
//
//   Inputs:        string - string to be changed
//                  ul - to upper or lower case 1 - upper, 0 - otherwise
//
//   Outputs:       char * - the changed string
//
////////////////////////////////////////////////////////////////////////////////
char * ChangeCase(const char * string, int ul)
{
    int i = 0;
    char * result;

    if (string == NULL)
        return NULL;

    result = (char *)malloc(sizeof(char) * (StrLen(string) + 1));
    if (result == NULL)
        return NULL;

    while (string[i] != '\0')
    {
        if (ul == 1)     // to upper
        {
            if (string[i] >= 97 && string[i] <= 122)
                result[i] = string[i] - 32;
            else
                result[i] = string[i];
        }
        else            // to lower
        {
            if (string[i] >= 65 && string[i] <= 90)
                result[i] = string[i] + 32;
            else
                result[i] = string[i];
        }

        i++;
    }

    result[i] = '\0';

    return result;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          StrCmp
//
//   Type:          Function
//
//   Description:   To compare two strings
//
//   Inputs:        source - the first string to compare
//                  dest - the second string to compare
//
//   Outputs:       int - 1 - source > dest
//                        -1 - source < dest
//                        0 - source = dest
//                        -2 - error
//
////////////////////////////////////////////////////////////////////////////////
int StrCmp(const char * source, const char * dest)
{
    int length;
    int d_length;
    int i = 0;

    if (source == NULL || dest == NULL)
        return -2;

    length = StrLen(source);
    d_length = StrLen(dest);

    while (source[i] != '\0' && dest[i] != '\0')
    {
        if (source[i] > dest[i])
            return 1;
        else if (source[i] < dest[i])
            return -1;
        i++;
    }

    if (length > d_length)
        return 1;
    else if (length < d_length)
        return -1;
    else
        return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          StrFindSubString
//
//   Type:          Function
//
//   Description:   To find a substring within a string
//
//   Inputs:        string - the string containing the substring
//                  substring - the substring
//                  pos - starting position
//                  Dir - scan direction , > 0 forward, <= 0 backward
//
//   Outputs:       int - index of first occurance of substring in string
//                        -1 - substring not found
//                        -2 - error
//
////////////////////////////////////////////////////////////////////////////////
int StrFindSubString(const char * string, const char * substring, int pos, int Dir)
{
    int length;
    int sub_length;
    int i = pos;
    int j;

    if (string == NULL || substring == NULL)
        return -2;

    length = StrLen(string);
    sub_length = StrLen(substring);

    if (length < sub_length)
        return -2;

    if (length == 0)
        return 0;

    if (sub_length == 0)
        return length;

    if (Dir > 0) // scan forward
    {
        if (pos >= length)
            return -2;

        if (pos < 0)
            i = 0;

        while (i < (length - sub_length) + 1)
        {
            for (j = 0;j < sub_length && string[i + j] == substring[j];j++);

            if (j == sub_length)
                return i;

            i++;
        }
    }
    else if (Dir <= 0) // scan backward
    {
        if (pos < 0)
            return -2;

        if (pos + sub_length > length)
            i = length - sub_length;
        else
            i = pos;

        while (i >= 0)
        {
            for (j = 0;j < sub_length && string[i + j] == substring[j];j++);

            if (j == sub_length)
                return i;

            i--;
        }
    }
    return -1;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          StrCountToken
//
//   Type:          Function
//
//   Description:   To count how many tokens are in a string
//
//   Inputs:        string - the string to be tokenized
//                  delimiters - array of delimiters, must be '\0' terminated
//                               if delimiters is NULL it will default to space
//                               and tab, it can contain any characters
//
//   Outputs:       int - number of tokens
//
////////////////////////////////////////////////////////////////////////////////
int StrCountToken(const char * string, const char * delimiters)
{
    unsigned char state = DELIMITER;        // means delimiters found
    unsigned char isDlm;
    int i = 0;
    int tokenCount = 0;

    if (string == NULL)
        return 0;

    while (string[i] != '\0')
    {
        isDlm = isDelimiter(string[i],delimiters);
        if (state == DELIMITER)
        {
            if (!isDlm)
            {
                state = STRING;
                tokenCount++;
            }

        }
        else
        {
            if (isDlm)
            {
                state = DELIMITER;
            }
        }
        i++;
    }
    return tokenCount;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          StrTok
//
//   Type:          Function
//
//   Description:   To tokenize a string
//
//   Inputs:        string - the string to be tokenized
//                  delimiters - array of delimiters, must be '\0' terminated
//                               if delimiters is NULL it will default to space
//                               and tab, it can contain any characters
//                  tokens - array of strings to hold the result
//
//   Outputs:       int - number of tokens
//
////////////////////////////////////////////////////////////////////////////////
int StrTok(const char * string, const char * delimiters, char *** tokens)
{
    unsigned char state = DELIMITER;        // means delimiters found
    unsigned char isDlm;
    char *tempString;
    int i = 0;
    int stringCount = 0;
    int tokenCount;

    tokenCount = StrCountToken(delimiters,string);

    if (tokenCount <= 0)
        return tokenCount;

    (*tokens) = (char **)malloc(sizeof(char *) * tokenCount);
    if ((*tokens) == NULL)
        return -1;

    tokenCount = 0;
    while (string[i] != '\0')
    {
        isDlm = isDelimiter(string[i],delimiters);
        if (state == DELIMITER)
        {
            if (!isDlm)
            {
                state = STRING;
                tempString = (char *)&(string[i]);
                stringCount = 1;
            }

        }
        else
        {
            if (isDlm)
            {
                state = DELIMITER;
                *((*tokens) + tokenCount) = (char *)malloc(sizeof(char) * (stringCount + 1));
                if (*((*tokens) + tokenCount) == NULL)
                    return -1;
                StrnCopy(tempString,*((*tokens) + tokenCount),stringCount);
                stringCount = 0;
                tokenCount++;
            }
            else
                stringCount++;
        }
        i++;
    }

    // the last token is right before '\0'
    if (state == STRING)
    {
        *((*tokens) + tokenCount) = (char *)malloc(sizeof(char) * (stringCount + 1));
        if (*((*tokens) + tokenCount) == NULL)
            return -1;
        StrnCopy(tempString,*((*tokens) + tokenCount),stringCount);
        tokenCount++;
    }

    return tokenCount;
}
