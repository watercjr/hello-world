#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*************************************************
 Function:       memstr
 Description:    从内存里面找特定的字符串
 
 Input:          full_data:要查找的源字符串指针，substr：要查找的目标字符串
 Return:         没有发现返回NULL，成功发现返回指向目标的指针 
 Author:         chenjunren
*************************************************/
char* memstr(char* full_data, int full_data_len, char* substr)
{
    if (full_data == NULL || full_data_len <= 0 || substr == NULL) {
        return NULL;
    }
 
    if (*substr == '\0') {
        return NULL;
    }
 
    int sublen = strlen(substr);
 
    int i;
    char* cur = full_data;
    int last_possible = full_data_len - sublen + 1;		//可能包含substr的full_data指针偏移量
    for (i = 0; i < last_possible; i++) {
        
        //当字符串首字符一致时，进行后面字符串的比对
        if (*cur == *substr) {
            //assert(full_data_len - i >= sublen);
            if (memcmp(cur, substr, sublen) == 0) {
                //found
                return cur;
            }
        }
        cur++;
    }
 
    return NULL;
}

int main(int argc, char **argv)
{
	char *src = "helloworld,123456789";
	char *dest = "456";
	char *addr = NULL;

	if((addr = memstr(src, strlen(src), dest)) !=NULL)
		printf("find \"%s\" success, the memory address is %p\n", dest, addr);

	return 0;
}