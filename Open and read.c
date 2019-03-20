#include<stdio.h> 
#include<fcntl.h> 
  
int main() 
{ 
    char c[10]; 
    int fd1 = open("foobar.txt", O_RDONLY, 0); 
    int fd2 = open("foobar.txt", O_RDONLY, 0); 
    read(fd1, &c, 6); 
    read(fd2, &c, 6); 
    printf("c = %s \n", c); 
    return 0;
} 
