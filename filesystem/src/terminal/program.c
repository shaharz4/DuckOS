#include "../../lib/libduck.h"
void main(int argc, char ** argv);
char **mystrsplit(char *string, char delimiter);
int strptrlen(char ** strptr);

void main(int argc, char ** argv) {
    char * input = malloc(80);
    char ** app_argv;
    int input_len = 0;
    while(1) {
		puts("\n$ ");
		gets(input);
        input_len = strlen(input);
        if(input[input_len-1] != ' ') {
            input[input_len-1] = ' ';
            input[input_len] = '\0';
        }
        app_argv = mystrsplit(input, ' ');
		execve(app_argv[0], strptrlen(app_argv), app_argv, 1);
	}
}

char **mystrsplit(char *string, char delimiter) {
    int length = 0, count = 0, i = 0, j = 0;
    while(*(string++)) {
        if (*string == delimiter) count++;
        length++;
    }
    string -= (length + 1);
    char **array = (char **)malloc(sizeof(char *) * (length + 1));
    char ** base = array;
    for(i = 0; i < count ; i++) {
        j = 0;
        while(string[j] != delimiter) j++;
        j++;
        *array = (char *)malloc(sizeof(char) * j);
        memcpy(*array, string, (j-1));
        (*array)[j-1] = '\0';
        string += j;
        array++;
    }
    *array = '\0';
    return base;  
}

int strptrlen(char ** strptr) {
    int len = 0;
    while(strptr[len++]);
    return len - 1;
}