#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OL 0

struct func_metadata
{
        int begin_pos;
        int end_pos;
        int func_id;
        char *call_ids[];
};

void find_function_main(char *buffer)
{
        int len;
        char print_string[40];
        char *found_begin_pos;
        char *found_end_pos;
        char *search_begin;
        char *search_end;
        struct func_metadata main;

        search_begin = "void";
        search_end = "{";
        len = strlen(search_begin);

        if(len > 0)
                found_begin_pos = strstr(buffer, search_begin);       /* maybe i should make this repeated code more modular */
                if(found_begin_pos != NULL) {
                        main.begin_pos = (int)(found_begin_pos - buffer);
                        printf("%d\n", main.begin_pos);

                        found_end_pos = strstr(buffer+main.begin_pos, search_end);
                        if(found_end_pos != NULL) {
                                main.end_pos = (int)(found_end_pos - buffer);
                                printf("%d\n", main.end_pos);

                                char subbuff[main.end_pos - main.begin_pos];
                                memcpy(subbuff, buffer+main.begin_pos, main.end_pos - main.begin_pos);
                                subbuff[main.end_pos - main.begin_pos] = '\0';

                                printf("%s", subbuff);
                        }
                        else
                                printf("Not found end\n");
                                return;
                }
                else
                        printf("Not found begin\n");
                        return;

        //should i use _recursion_ here to find all instances of function definitions?
        //find_function_main(buffer+main.end_pos, ); while buffer != EOF;
        return;
}


void format_file(char *buffer)
{
        //find_function_main(buffer);
        //printf("%s", buffer);
}

int main(int argc, char *argv[])
{
        FILE *fp;
        char *buffer;
        size_t size;

        fp = fopen(argv[1], "r");

        if(fp == NULL)
                printf("File not found\n");
        else {
                fseek(fp, OL, SEEK_END);
                size = ftell(fp);
                fseek(fp, OL, SEEK_SET);

                buffer = calloc(size, sizeof(char));
                fread(buffer, sizeof(char), size, fp);

                find_function_main(buffer);

                fclose(fp);
                free(buffer);
        }

        return 0;
}
