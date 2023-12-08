// run "ascii -d" for a list of characters you need to check
// (CR, LF, SPACE, ...)

#include <stdio.h>

int main(int argc, char **argv){
    int args = argc;
    char input = *argv[1];

    printf("%d", input);

    return 0;
}