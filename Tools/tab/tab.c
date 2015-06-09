/*
//===========================================================================
// Copyright (c) : Pulserain Technology, LLC. 2015
//===========================================================================
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
*/


#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DEFAULT_ERROR 1
#define DEFAULT_TAB_SPAN 4

#define MAX_TAB_SPAN 256

#define EOL '\n'

#ifndef bool
typedef enum {
    false,
    true
} bool;
#endif

/*
//-----------------------------------------------------------------------------
// backUpFile()
//
// Parameters:
//        fileName: file to be backed.
//        backUpFileName: the name of the back up file
//
// Return Values:
//        true : success
//        false: back up fail
//
// Remarks:
//        This function makes a backup copy for a certain file
//-----------------------------------------------------------------------------
*/

bool backUpFile(char *fileName, char *backUpFileName)
{

    FILE *bf, *f;
    size_t count, countBackUp;
    char buf[2];

    f = fopen(fileName, "r");
    if (!f) {
        fprintf(stderr, "Can't open source file %s!\n", fileName);
        return false;
    }

    bf = fopen(backUpFileName, "w");
    if (!bf) {
        fprintf(stderr, "Can't open backup file %s!\n", backUpFileName);
        return false;
    }

    do {
        count = fread(buf, sizeof(char), 1, f);
        if (count) {
            countBackUp = fwrite(buf, sizeof(char), 1, bf);
            if (countBackUp == 0) { /* write back up file fail */
                fprintf(stderr, "write back up file error!\n");
                fclose(f);
                fclose(bf);
                return false;
            }
        }
    } while((count) && ((*buf) != EOF));

    fclose(f);
    fflush(bf);
    fclose(bf);

    printf(" The original file has been saved as %s\n", backUpFileName);

    return true;

} /* End of backUpFile() */

/*
//-----------------------------------------------------------------------------
// main()
//
// Parameters:
//        argv[1]: file name
//        argv[2]: tab span
//
// Return Values:
//        the count of tabs
//
// Remarks:
//        This is the main function.
//-----------------------------------------------------------------------------
*/
int main(int argc, char **argv)
{
    char *fileName;
    char *backUpFileName;
    char buf[MAX_TAB_SPAN + 2];
    bool foundTab;

    FILE *fp = NULL, *bf;
    int i, column, loopEnd;
    int tabSpan = DEFAULT_TAB_SPAN;
    int lineCount = 1;
    int totalTabCount = 0;
    size_t count, countBackUp;

    if (argc > 3) { /* too many parameters */
        fprintf(stderr, " too many parameters \n");
        return DEFAULT_ERROR;
    } else if (argc == 1) {
        printf("===== tab version 1.2 =====\n");
        printf("usage  : tab file [tabSpan]\n");
        return DEFAULT_ERROR;
    }

    fileName = argv[1];
    backUpFileName = malloc(strlen(fileName) + 3);
    if (!backUpFileName) {
        fprintf(stderr, " Can't get back up file name\n");
        return DEFAULT_ERROR;
    }

    /* back up file name */
    sprintf(backUpFileName, "%s~", fileName);
    backUpFileName[strlen(fileName) + 1] = '\0';

    if (backUpFile(fileName, backUpFileName) == false) {
        free(backUpFileName);
        return DEFAULT_ERROR;
    }

    fp = fopen(fileName, "w+");

    if (!fp) {
        fprintf(stderr, " Can't open file %s for write!\n", fileName);
        free(backUpFileName);
        return DEFAULT_ERROR;
    }

    bf = fopen(backUpFileName, "r");

    if (!bf) {
        fprintf(stderr, " Can't back up file %s for read!\n", backUpFileName);
        free(backUpFileName);
        return DEFAULT_ERROR;
    }

    if (argc == 3) { /* get tab span */
        tabSpan = atoi(argv[2]);
        if (MAX_TAB_SPAN <= tabSpan) {
            fprintf(stderr, " tab span %d too big!\n", tabSpan);
            free(backUpFileName);
            return DEFAULT_ERROR;
        }
    }

    foundTab = false;
    column = 0;
    do { /* character by charater */
        count = fread(buf, sizeof(char), 1, bf);
        if (count) {
            ++column;
            buf[1] = '\0';
            if ((*buf) == '\t') {
                ++totalTabCount;
                if (foundTab == false) {
                    foundTab = true;
                    printf("### found tab on line %d\n", lineCount);
                }
                --column;
                loopEnd = tabSpan - (column % tabSpan);
                for (i = 0; i < loopEnd; ++i) {
                    buf[i] = ' ';
                    ++column;
                } /* End of for loop */
                buf[loopEnd] = '\0';
            } else if ((*buf) == EOL) { /* increase line count */
                ++lineCount;
                foundTab = false;
                column = 0;
            }

            countBackUp = fwrite(buf, sizeof(char), strlen(buf), fp);
            if (countBackUp == 0) {
                fprintf(stderr, "Can not update file!\n");
            }
        }
    } while(count && (buf[0] != EOF));

    free(backUpFileName);

    fflush(fp);
    fclose(fp);
    fclose(bf);

    return totalTabCount;
} /* End of main() */
