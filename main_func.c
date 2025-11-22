#include<stdio.h>
#include<string.h>
#include"mp3header.h"
#include<stdlib.h>

int main(int argc, char*argv[], char*envp[])
{
    if(argc<2)
    {
        error();
    }
    else
    {
        if(strcmp(argv[1], "--help")==0)
        {
            help();
            return 0;
        }

        else if((strcmp(argv[1], "-v")==0) && argc>2)
            {
                if(strstr(argv[2],".mp3")!=NULL)
                {
                    char *filename = (char*)malloc(100 * sizeof(char));
                    strcpy(filename, argv[2]);
                    if(check(filename))
                    {
                        view(filename);
                    }
                    free(filename);
                }
                else
                {
                    printf("Mp3 file is not passed\n");
                    error();
                    return 0;
                }
            }
        else if((strcmp(argv[1], "-e")==0) && argc>=2)
        {
            int flag = 0,i;
            for(i=2 ; i < argc ;i++)
            {
                if(strstr(argv[i],".mp3")!=NULL)
                {
                    flag = 1;
                    char *filename = (char*)malloc(100 * sizeof(char));
                    strcpy(filename, argv[i]);
                    if(check(filename))
                    {
                        edit(argv,filename,argc);
                    }
                    else{
                        return 0;
                    }
                    free(filename);
                    break;
                }
            }
            if(flag == 0) 
            {
                printf("Mp3 file not found\n");
                error();
                return 0;
            }
        }
        else{
            error();
            return 0;
        }
    }
        return 0;
}
