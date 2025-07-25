#include <stdio.h>
#include <ctype.h>      // character types
#include <string.h>     // string manipulation
#include <unistd.h>     // cmd arguments
#include <stdlib.h>     // malloc n stuff
#include <errno.h>      // errors
#include <bits/getopt_core.h>   // just to use optarg in line 34

#ifndef FALSE
    #define FALSE 0
#endif

#ifndef TRUE
    #define TRUE 1
#endif

int main(int argc, char **argv){
    if(argc < 6){
        printf("Usage: parCer [DELIMITER] [OPTION]... [FILE] [FILE]\n");
        return 1;
    }

    char delimiter = 0;

    /* DEFINE FLAGS USED */
    int LOG = FALSE;
    int NEW_LINE = FALSE;
    int TRIM = FALSE;

    int c = 0;
    while((c = getopt(argc, argv, "d:lnt")) != -1){
        switch(c){
            case 'd':
                int i = strlen(optarg);
                if(i > 1){
                    printf("Please use a single character\n");
                    return 1;
                }
                delimiter = *optarg;
                break;
            case 'l':
                LOG = TRUE;
                break;
            case 'n':
                NEW_LINE = TRUE;
                break;
            case 't':
                TRIM = TRUE;
                break;
            default:
                printf("Wrong usage.\n");
                return 1;
        }
    }

    FILE *input = NULL;
    FILE *output = NULL;

    if((input = fopen(argv[argc-2], "r")) == NULL){
        printf("TEST\n");
        printf("wrong input file: %s\n", *argv[argc-2]);
        return 1;
    }
    if((output = fopen(argv[argc-1], "w")) == NULL){
        printf("Can not create file: %s\n", *argv[argc-1]);
        return 1;
    }

    int token_len_max = 32;             // arbitrary size
    float load_factor_threshold = 0.8;  // arbitrary size
    float load_factor = 0;              // initialize

    char *token = NULL;
    token = (char *)malloc(token_len_max * sizeof(char));

    int del_found = FALSE;
    int token_idx = 0;              // token index
    int token_len = 0;              // token length
    char character = getc(input);   // current character

    while(character != EOF){
        if((character != delimiter) && (character != '\n') && (character != '\r')){
            del_found = FALSE;

            token[token_idx++] = character;
            token_len = token_idx;

            load_factor = (float)token_idx / token_len_max;
            if(load_factor > load_factor_threshold){
                token_len_max += token_len_max;

                // FIXME: seg fault (gdb)
                token = (char *)realloc(token, token_len_max * sizeof(char));
            }
        } else if(del_found && ((character == delimiter) || (character == '\n') || (character == '\r'))){
            character = getc(input);
            token_idx = 0;
            continue;
        } else {
            del_found = TRUE;
            
            // TODO: trim multiple non-alphanumeric characters from token
            if(TRIM){
                // TODO: turn this into a function

                // example of a 5 character long token being fully trimmed
                //--------------------------------------------------------
                //  idx    len    idx    len    idx    len    idx    len
                // 012345        012345        012345        012345
                // (asd)_ : 5 -> _asd)_ : 4 -> asd)__ : 4 -> asd___ : 3

                if(!isalnum(token[0])){
                    token[0] = '\0';

                    // TODO: turn this into a function
                    // allign string with the start of the array
                    for(int i = 0; i < token_len; i++){
                        token[i] = token[i+1];
                    }

                    token_len--;
                }
                if(!isalnum(token[token_len - 1])){
                    token[token_len - 1] = '\0';
                    token_len--;
                }
            }
            if(NEW_LINE){
                token[token_len] = '\n';
            } else {
                token[token_len] = ' ';
            }

            char *_token = NULL;
            _token = (char *)malloc(token_len * sizeof(char) + 2); // +1 for space/newline, +1 for \0

            for(int i = 0; i < (token_len + 1); i++){
                _token[i] = token[i];
            }

            _token[token_len + 1] = '\0'; // terminate string

            fputs(_token, output);

            free(_token);

            token_idx = 0;
        }
        character = getc(input);
    }

    if(token_idx > 0){
        if(TRIM){
            // TODO: turn this into a function

            // example of a 5 character long token being fully trimmed
            //--------------------------------------------------------
            //  idx    len    idx    len    idx    len    idx    len
            // 012345        012345        012345        012345
            // (asd)_ : 5 -> _asd)_ : 4 -> asd)__ : 4 -> asd___ : 3

            if(!isalnum(token[0])){
                token[0] = '\0';

                // TODO: turn this into a function
                // allign string with the start of the array
                for(int i = 0; i < token_len; i++){
                    token[i] = token[i+1];
                }

                token_len--;
            }
            if(!isalnum(token[token_len - 1])){
                token[token_len - 1] = '\0';
                token_len--;
                }
        }
        if(NEW_LINE){
            token[token_len] = '\n';
        } else {
            token[token_len] = ' ';
        }

        char *_token = NULL;
        _token = (char *)malloc(token_len * sizeof(char) + 1);

        for(int i = 0; i < (token_len + 1); i++){
            _token[i] = token[i];
        }

        fputs(_token, output);

        free(_token);
    }

    free(token);
    if(fclose(input) != 0){
        printf("Error closing file: %s\n", strerror(errno));
    }
    if(fclose(output) != 0){
        printf("Error closing file: %s\n", strerror(errno));
    }
    return 0;
}
