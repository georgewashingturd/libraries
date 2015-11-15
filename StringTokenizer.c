////////////////////////////////////////////////////////////////////////////////
// Copyright(C) GreyGrolics 2004
//
// Filename: StringTokenizer.c
// Description: String tokenizer functions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes and external references
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h> // this is for definition of NULL

////////////////////////////////////////////////////////////////////////////////
// Defs
////////////////////////////////////////////////////////////////////////////////

#define DELIMITER 1
#define STRING 0

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
unsigned char isDelimiter(char alpha, char * delimiters)
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
//   Name:          CopySubString
//
//   Type:          Function
//
//   Description:   To copy string to string, equivalent to StrnCopy
//
//   Inputs:        source - the source string
//                  dest - dest string
//                  length - how many characters to copy
//
//   Outputs:       dest - the copied string will be in dest
//
////////////////////////////////////////////////////////////////////////////////
void CopySubString(char * source, char * dest, int length)
{
    int i;

    if (source == NULL || dest == NULL)
    {
        return;
    }

    for (i = 0; i < length ; i++)
    {
        dest[i] = source[i];
    }

    dest[i] = '\0';
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          CountToken
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
int CountToken(char * string, char * delimiters)
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
int StrTok(char * string, char * delimiters, char *** tokens)
{
    unsigned char state = DELIMITER;        // means delimiters found
    unsigned char isDlm;
    char *tempString;
    int i = 0;
    int stringCount = 0;
    int tokenCount;

    tokenCount = CountToken(delimiters,string);

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
                tempString = &(string[i]);
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
                CopySubString(tempString,*((*tokens) + tokenCount),stringCount);
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
        CopySubString(tempString,*((*tokens) + tokenCount),stringCount);
        tokenCount++;
    }

    return tokenCount;
}
