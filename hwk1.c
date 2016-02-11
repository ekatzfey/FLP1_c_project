//
//  main.c
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFSIZ 1024
#define USAGE printf("Usage: hwk1 [-i] <file-name> <pattern>\n"); return 0;

int main(int argc, const char * argv[]) {
    
    // General loop index
    int i = 0;
    
    // Flag to indicate case insensitive match
    int nocase = 0;
    
    // File pointer
    FILE *fp = NULL;
    
    // Buffer to store file name
    char filename[BUFSIZ];
    
    // Buffer to store a line of text
    char buf[BUFSIZ];
    
    // Buffer to store the pattern
    char pattern[BUFSIZ];
    
    // Buffer to store current word in current line
    char curword[BUFSIZ];
    
    // Length of pattern
    int patlen = 0;
    
    // Length of current input string
    int curlen = 0;
    
    // Current index into line buffer
    int idx = 0;
    
    // Parse command line
    if ((argc < 3) || (argc > 4)) {
        USAGE
    }
    
    // Check for properly formatted option.
    // Copy arguments into local buffers.
    if (argc == 4) {
        if (strcmp(argv[1], "-i") != 0) {
            USAGE
        }
        else {
            nocase = 1;
            strcpy(filename, argv[2]);
            strcpy(pattern, argv[3]);
        }
    }
    else {
        strcpy(filename, argv[1]);
        strcpy(pattern, argv[2]);
    }
    
    // Get length of the pattern
    patlen = (int) strlen(pattern);
    
    // If we are doing a case insensitive search
    // then convert pattern to uppercase
    if (nocase == 1) {
        for (i = 0; i < patlen; i++) {
            if (islower(pattern[i])) {
                pattern[i] = toupper(pattern[i]);
            }
        }
    }
    
    // Debug code
    //printf("Case insensitive: %d\n", nocase);
    //printf("File name: %s\n", filename);
    //printf("Pattern: %s\n", pattern);
    
    // Open the file
    fp = fopen(filename, "r");
    
    if (fp != NULL) {
        // Read in a line at a time
        while (fgets(buf, BUFSIZ, fp) != NULL) {
            
            // Figure out the length of the current line
            curlen = (int) strlen(buf);
            
            // Debug
            //printf("Current line length: %d\n", curlen);
            
            // If there are enough characters in the current line
            // then compare current word to the pattern
            while ((curlen - idx) >= patlen) {
                
                // Copy into the current word buffer
                strncpy(curword, &buf[idx], patlen);
                
                // If it is a case insensitive search then convert the
                // current word to upper case
                if (nocase == 1) {
                    for (i = 0; i < patlen; i++) {
                        if (islower(curword[i])) {
                            curword[i] = toupper(curword[i]);
                        }
                    }
                }
                
                // Check for a match
                if (strncmp(curword, pattern, patlen) == 0) {
                    
                    // We found a match so output proper number of '*'
                    for (i = 0; i < patlen; i++) {
                        printf("*");
                    }
                    idx += patlen;
                }
                else {
                    // No match so print current character and then
                    // move to the next one.
                    printf("%c", buf[idx++]);
                }
            }
            
            // Output whatever is left in the current line
            puts(&buf[idx]);
            
            // Reset the index
            idx = 0;
        }
        
        // Close the file
        fclose(fp);
    }
    else {
        printf("ERROR, could not open file: %s\n", filename);
    }
    
    return 0;
}
