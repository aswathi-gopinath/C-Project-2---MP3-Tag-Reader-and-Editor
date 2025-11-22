#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"mp3header.h"

int view(char *file)
{
   printf("----------------------SELECTED VIEW DETAILS----------------------\n");
   printf("\n-----------------------------------------------------------------\n");
   printf("               MP3 TAG READER AND EDITOR FOR ID3v2                 \n");
   printf("-------------------------------------------------------------------\n");
   FILE *fp;
   fp = fopen(file, "r");
   if(fp == NULL)
   {
    perror("ERROR \n");
    return 0;
   }
   fseek(fp,10,SEEK_SET);
   //printf("%ld\n", ftell(fp)-1);
   int j=0;
   char view_tag[5];
   char tag[10];
   while(j!=6 && (fread(view_tag,4,1,fp) > 0))
   {
      view_tag[4] = '\0';
      //printf("%s : ", str1);
      int size;
      fread(&size,4,1,fp);
      //printf("%ld\n", ftell(fp)-1);
      char *ptr;
      ptr = (char *)&size;
      endianess(&size);
      fseek(fp,2,SEEK_CUR);
      //printf("%ld\n", ftell(fp)-1);
      char str2[size+1];
      fread(str2,size,1,fp);
      str2[size]='\0';
      if( strcmp(view_tag, "TIT2")== 0) 
      {
        strcpy(tag, "Title");
        j++;
      }
      if( strcmp(view_tag, "TPE1")== 0) 
      {
         strcpy(tag, "Artist");
         j++;
      }
      if( strcmp(view_tag, "TALB")== 0) 
      {
        strcpy(tag, "Album");
        j++;
      }
      if( strcmp(view_tag, "TYER")== 0) 
      {
        strcpy(tag, "Year");
        j++;
      }
      if( strcmp(view_tag, "TCON")== 0) 
      {
        strcpy(tag, "Content");
        j++;
      }
      if( strcmp(view_tag, "COMM")== 0) 
      {
        strcpy(tag, "Comment");
        j++;
      }
      int k;
      printf("%-10s : ", tag);
      for(k = 1; k < size; k++)
      {
         printf("%c", str2[k]);
      }
      printf("\n");
   }
      fclose(fp);
      return 0;
}


