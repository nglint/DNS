// simple Recursive Query DNS server by SADEEM 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <winsock.h>

 struct sockaddr_in;


 struct in_addr;

struct sockaddr;

void sethost(char *a,char *b)//add an ip and host name to the database
{//the file name is the host name and it contain the ip address in HEX format
    //EX\ sethost("www.myserver.com","192.168.0.1");
 FILE *A;
char g[100]="host\\";// database folder
 A=fopen(strcat(g,a),"a");
 unsigned char t=0;
 unsigned int s=0;
 for(int i=strlen(b)-1,i2=1,m=0;i>=0;i--)
 {
 if(b[i]!='.')
 {
 t+=(b[i]-48)*i2;
 i2*=10;
 }
 if(b[i]=='.'i==0)
 {
 s|=(t<<(8*m));
  printf("HEX:%x  \n",s);
  i2=1,t=0,m++;
 }
 }


 fprintf(A,"%x \n",s);
 fclose(A);
}

void strcut(char *a,int f,int l,char *b)
{
 for(int i=f,i2=0;i<=l;i++,i2++) b[i2]=a[i];
 b[l]='\0';
}

typedef struct dns
{
 unsigned short id,flag,nq,na,nat,nat2;
 unsigned char x;
 unsigned char host[50];

} sdns;

typedef struct dns2
{

 unsigned short name,type,classs;
 unsigned int ttl:32;
 unsigned short len:16;
 int data;
char end;
} ;

void B(SOCKET *A)
{


 SOCKET B;
 unsigned char *d=(char *)malloc(44000),d3;
 struct sockaddr_in h;
   h.sin_port=  htons(53);////////////////////
   h.sin_addr.s_addr = inet_addr("8.8.8.8");//google //this is the addres of the dns server that we will use if we dont find the host name in the server database
   h.sin_family=AF_INET;/////////////////////
for(;;){int siz=0;
char d2[200]="host\\";   // this is the path to the database folder
struct sockaddr_in a;
int s=sizeof(a);
    do{siz=recvfrom(*A,d,100,0,(struct sockaddr*)&a,&s );
       }while(siz==-1);
      sdns *P; ////DNS packet format
P=(sdns*)d;

FILE *V;
strcat(d2,P->host);
for(int i=0;i<siz-13;i++)if(d2[i]<10)d2[i]='.';
printf("%s\n",d2);
V=fopen(d2,"r");
unsigned short name ,type,classs,len;
int ttl,ip;

if(V!=0) // the host name in the server database
{
name =0xc00c,type=1,classs=1,ttl=16,len=4;
fscanf(V,"%x",&ip);//get the ip add
P->na=0x0100;
P->flag=0x8081;
strcpy(d,(char*)P);
char *c=&ip;
d[siz+12]=c[3];d[siz+13]=c[2];d[siz+14]=c[1];d[siz+15]=c[0];
{
 c=&name;d[siz]=c[1];d[siz+1]=c[0];
  c=&type;d[siz+2]=c[1];d[siz+3]=c[0];
 c=&classs;d[siz+4]=c[1];d[siz+5]=c[0];
 c=&ttl;d[siz+6]=c[3];d[siz+7]=c[2];d[siz+8]=c[1],d[siz+9]=c[0];
 c=&len;d[siz+10]=c[1];d[siz+11]=c[0];
}
}else// the is host not in the database, and we will ask for help from other dns server then send the response to the user
{
    
   int siz2,m=0;

   do {m++;
sendto(*A,(char*)P,siz,0,(struct sockaddr*)&h,sizeof(h));
   siz2=recv(*A,d,200,0);
   }while(siz2==-1&&m<1000);
   siz=siz2;
}
fclose(V);
sendto(*A,d,siz+17,0,(struct sockaddr*)&a,s);

}
}
int main()
{//sethost("www.a.com","192.168.0.1");
WSADATA Winsock;
WSAStartup(MAKEWORD(2, 2), &Winsock);    // Start Winsock
    if(LOBYTE(Winsock.wVersion) != 2  HIBYTE(Winsock.wVersion) != 2)WSACleanup(),exit(1);
    SOCKET A;
 struct   sockaddr_in a;
 printf("DNS SERVERR\n");
    A=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
   a.sin_port=  htons(53);
   a.sin_addr.s_addr = htonl(INADDR_ANY);
   a.sin_family=AF_INET;
  if( bind(A,(struct sockaddr*)&a,sizeof(a))==-1)printf("bind ERORR"),exit(1);

B(&A);

}