#include<stdio.h>
#include"mp3header.h"
void error()
{
    printf("ERROR : ./a.out : INVALID ARGUMENTS\n");
    printf("USAGE :\n");
    printf("To view please pass like: ./a.out -v mp3filename\n");
    printf("To edit please pass like: ./a.out -e -t/-a/-A/-y/-c changing_text mp3filename\n");
    printf("To get help pass like: ./a.out --help\n");

}