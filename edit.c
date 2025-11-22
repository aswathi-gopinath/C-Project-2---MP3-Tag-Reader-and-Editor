#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"mp3header.h"

int edit(char*argv[], char *file, int argc)
{
   if(argc == 3)
   {
      printf("------------------SELECTED EDIT DETAILS-----------------\n");
      printf("\nPlease pass tag arguments which you want to edit\n");
      printf("eg :./a.out -e/-t/-a/-A/-y/-m/-c mp3 filename\n");
      return 0;
   }
   FILE *fp, *f2;
   fp = fopen(file, "r");
   f2 = fopen("copy.mp3","w");
   if(fp == NULL || f2 == NULL)
   {
    perror("ERROR \n");
    return 0;
   }

   char edit_tag[5];
   char str3[100];
   if(strcmp(argv[2],"-t") == 0) 
   {
      strcpy(edit_tag, "TIT2");
      strcpy(str3, "Title");
   }
   else if(strcmp(argv[2],"-a") == 0) 
   {
      strcpy(edit_tag, "TPE1");
      strcpy(str3, "Artist");
   }
   else if(strcmp(argv[2],"-A") == 0) 
   {
      strcpy(edit_tag, "TALB");
      strcpy(str3, "Album");
   }
   else if(strcmp(argv[2],"-y") == 0) 
   {
      strcpy(edit_tag, "TYER");
      strcpy(str3, "Year");
   }
   else if(strcmp(argv[2],"-m") == 0) 
   {
       strcpy(edit_tag, "TCON");
       strcpy(str3, "Content");
   }
   else if(strcmp(argv[2],"-c") == 0) 
   {
      strcpy(edit_tag, "COMM");
      strcpy(str3, "Comment");
   }
   else
   {
      error();
      return 0;
   }

   printf("----------------SELECT EDIT OPTION---------------\n");
   printf("-------------Select %s change option--------------------\n", str3);
   printf("               %s     :    %s\n", str3,argv[3]);
  
   int new_size = strlen(argv[3]);
   char *text = malloc(new_size + 1);
   strcpy(text,argv[3]);
   
   char header[11];
   int size,size1;
   char data[5];
   char flag[2];
   char ch;
   fread(header ,10, 1, fp);
   fwrite(header, 10, 1, f2);
   int j = 0;
    while((fread(data, 1, 4, fp) > 0) && j!=6)
    {
         data[4] = '\0';
         fwrite(data, 1, 4, f2);
         j++;
         fread(&size, 4, 1, fp);
         endianess(&size);
         size1 = size;
         fread(flag, 2, 1, fp);
         fread(&ch, 1, 1, fp);
         if( strcmp(data, edit_tag) == 0 )
         {
            int new_size1= new_size;
            int total_size = new_size+1;
            endianess(&total_size);
            fwrite(&total_size, 4, 1, f2);
            fwrite(flag, 2, 1, f2);
            fwrite(&ch, 1, 1, f2);
            fwrite(text,new_size1, 1 , f2);
            fseek(fp, size-1, SEEK_CUR);
          }
          else
          {
            endianess(&size);
            fwrite(&size, 4, 1, f2);
            fwrite(flag, 2, 1, f2);
            fwrite(&ch, 1, 1, f2);
            if(size1 > 0)
            {
              char *data1 = (char *)malloc(size1 - 1);
              fread(data1,size1-1,1,fp);
              fwrite(data1,size1-1,1,f2);
              free(data1);
            }
        }
   }
   char data1[1024];
   int n;
   while ((n = fread(data1, 1, sizeof(data1), fp)) > 0)
   {
       fwrite(data1, 1, n, f2);
   }

   fclose(f2);
   fclose(fp);
   free(text);
   remove(file);
   rename("copy.mp3",file);
   printf("--------------%s changed successfully--------------\n", str3);
   return 0;
}
   
