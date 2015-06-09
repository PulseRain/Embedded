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

#define DEFAULT_ERROR 1
#define DEFAULT_WIDTH 80

#define EOL '\n'

/*
//-----------------------------------------------------------------------------
// readLine()
//
// Parameters:
//      fp: file pointer, the file should be opened already
//
// Return Values:
//      -1 : end of file, no more data
//      otherwise, the count of characters read from current line
//
// Remarks:
//      This function will read one line from file and return the count of 
// characters of the line.
//-----------------------------------------------------------------------------
*/
int readLine(FILE * fp)
{
    size_t count, total = 0;
    char buffer[2];

    do {
        count = fread(buffer, sizeof(char), 1, fp);

        if ((*buffer) == EOL) { /* End of line */
                        if(count){   
                return ((int) total);
            } else {
                return -1;
            }
          
        } else if ((*buffer) == EOF) { /* End of file */
            return -1;
        }

        total += count;

    } while(count);

    return (-1); /* No more data */

} /* End of readLine() */



/*
//-----------------------------------------------------------------------------
// main()
//
// Parameters:
//      argv[1]: file name
//      argv[2]: line width (optional)
//
// Return Values:
//      0: success
//      otherwise, the count of total violations
//
// Remarks:
//      This is the main function.
//-----------------------------------------------------------------------------
*/

int main(int argc, char **argv)
{
    char *fileName;
    FILE *fp = NULL;
    int total;
    int lineWidth = DEFAULT_WIDTH;
    int lineCount = 0;
    int totalViolation = 0;

    if (argc > 3) {
        fprintf(stderr, " too many parameters \n");
        return DEFAULT_ERROR;
    } else if (argc == 1) {
        printf("===== lineWidth version 1.1 =====\n");
        printf("usage  : lineWidth file [width]\n");
        return DEFAULT_ERROR;
    }

    fileName = argv[1];


    fp = fopen(fileName, "r");

    if (fp == NULL) {
        fprintf(stderr, " Can't open file \n");
        return DEFAULT_ERROR;
    }

    if (argc == 3) { /* get line width */
        lineWidth = atoi(argv[2]);
    }

    do { /* line by line */
        total = readLine(fp);
        ++lineCount;
        if (total > lineWidth) {
                  ++totalViolation;
            printf(" ### line %d, width %d\n", lineCount, total);
        }
    } while(total >= 0);

    fclose(fp);

    return totalViolation;
} /* End of main() */
