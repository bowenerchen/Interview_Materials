/*Given two binary strings, return their sum (also a binary string).
For example,
a = "11"
b = "1"
Return "100".
*/

#define ctn(x) ((x=='1')?1:0)
#define ntc(x) ((x==1)?'1':'0')
#define SWAP(a,b,type) {type c;*c=*a;*a=*b;*b=*c;}
char* addBinary(char* a, char* b) {
    if(!a) {return b;} else if(!b) {return a;}
    int lena=0;int lenb=0;
    while(*a) {a++;lena++;} a--;
    while(*b) {b++;lenb++;} b--;
    int sum=0;int up=0;
    char* ret=(char*)malloc(sizeof(char)*(((lena>lenb)?lena:lenb)+1));
    char* head=ret;
    char* rtu=ret;
    while(lena || lenb){
        if(lena && lenb){
            sum=ctn(*a) + ctn(*b) + up;
        }else{
            if(lena)
	    	{sum=ctn(*a) + up;}
            if(lenb)
	    	{sum=ctn(*b) + up;}
        }
        if(sum>=2) 
		{sum=sum%2;up=1;}
        else 
		{up=0;}
        *ret=ntc(sum);ret++;
        if(lena)
		{lena--;a--;}
        if(lenb)
		{lenb--;b--;}
    }
    if(up) {
        *ret='1';
        /*加了下面这句才通过，否则不能通过，
        不明白为什么要显式的指定这个值*/
        *(ret+1)='\0';
    }
    else{
        *ret='\0';
        ret--;
        while(*ret=='0'){
            if(ret==head)
	    	{break;}
            *ret='\0';
            ret--;
        }
    }
    
    while(head<ret){
        SWAP(head,ret,char*);
        head++;ret--;
    }
return rtu;
}
