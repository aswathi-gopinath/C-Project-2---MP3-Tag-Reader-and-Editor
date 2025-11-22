#include<stdio.h>
#include<string.h>
#include"mp3header.h"

int check(char *file)
{
    FILE *fp;
    fp = fopen(file,"r");
    if(fp == NULL)
    {
        printf("No mp3 file found\n");
        return -1;
    }
    char tag[4];
    if(fgets(tag,4,fp)!=NULL)
    {
        if(!(strcasecmp(tag,"ID3")))
        {
           //ID3 tag present
           fseek(fp, 3, SEEK_SET);
           char version[2];
           fread(version, 2, 1,fp);
           if(version[0]==0x03 && version[1]==0x00)  
           { 
                //Version is ID3V2.3
                return 1;
           }
            else{
                printf("Different verion\n");
            }
        }
       else
        {
             printf("ID3 tag absent. No metadata available\n");
        }
    }
    fclose(fp);
    return 0;

}
 