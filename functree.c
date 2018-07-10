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



void find_function_main(char *buffer, size_t size)
{
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //what are the conditions needed for us to read a pattern as a function?                                                                //
        //1. is a word followed by a '(' followed by either a ')' + '\n{' or '{\n' or by words and a ')' ...                                    //
        //2. difference between a definition, declaration, and call:                                                                            //
        //   - definition doesn't have {}, it's merely a primitive. - declaration is outside a function (followed by ;).                        //
        //   - call is from inside a function, (followed by ;).                                                                                 //
        //3. I will need a bool which signifies whether we are reading within a function or outside a function. This will signify the different //
        //   between declaration and call.                                                                                                      //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        int len;
        int position;
        char *found;
        char *search;

        search = "void";
        len = strlen(search);

        if(len > 0)
                found = strstr(buffer, search);
                if(found != NULL) {
                        position = (int)(found - buffer);
                        printf("%d\n", position);
                }
                else {
                        printf("Not found\n");
                }
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
        else
        {
                fseek(fp, OL, SEEK_END);
                size = ftell(fp);
                fseek(fp, OL, SEEK_SET);

                buffer = calloc(size, sizeof(char));
                fread(buffer, sizeof(char), size, fp);

                find_function_main(buffer, size);

                fclose(fp);
                free(buffer);
        }

        return 0;
}
