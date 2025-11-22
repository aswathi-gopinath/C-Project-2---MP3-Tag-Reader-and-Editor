void endianess(int* size)
{
     char *ptr;   
     ptr = (char *)size;
     int i;
     char temp;
     for(i=0; i<2; i++)
     {
        temp = *(ptr + i);
        *(ptr + i) = *(ptr + (3 - i));
        *(ptr + (3 - i)) = temp;
     }
}