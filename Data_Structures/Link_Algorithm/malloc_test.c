#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* test(){
	char* p=(char*)malloc(sizeof(char)*20);
	printf("after malloc,mem addr:%p\n",p);
	strcpy(p,"hello,world!");
	printf("after strcpy, mem addr:%p\n",p);
return p;
}

void test2(char** p){
	*p=(char*)malloc(sizeof(char)*20);
	printf("after malloc,mem addr:%p\n",*p);
	strcpy(*p,"hello,world!");
	printf("after strcpy, mem addr:%p\n",*p);
return ;
}

int main(){
	//char* a=test();
	//printf("in main mem addr:%p\n",a);
	//printf("length:%zd\n",strlen(a));
	//printf("%s\n",a);
	//free(a);
	//printf("after free() mem addr:%p\n",a);
	//printf("length:%zd\n",strlen(a));
	//printf("%s\n",a);
	
	char* b=NULL;
	test2(&b);
	printf("in main mem addr:%p\n",b);
	printf("length:%zd\n",strlen(b));
	printf("%s\n",b);
	free(b);
	printf("after free() mem addr:%p\n",b);
	printf("length:%zd\n",strlen(b));
	printf("%s\n",b);
return 0;
}
