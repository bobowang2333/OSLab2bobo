#include <stdio.h>
int main(void)
{
    FILE *fp;
    fp = fopen("test.txt","r");
    char* s;
    char res[1024];
    int len = fread(res,sizeof(char),25,fp);    
    s = res;
    printf("result %s \n",s);
    return 0;
}
