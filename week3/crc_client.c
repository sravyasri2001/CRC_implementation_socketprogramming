#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
#define MAX 80
#define SERV_TCP_PORT 8080
#define SA struct sockaddr
int main()
{
int sockfd,connfd;
struct sockaddr_in serv_addr;
//struct hostent *server;
char s[100],a[100],q[100];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if (sockfd == -1) 
{
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");

bzero(&serv_addr, sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
serv_addr.sin_port=htons(SERV_TCP_PORT);

if (connect(sockfd, (SA*)&serv_addr, sizeof(serv_addr)) != 0)
{
printf("connection with the server failed...\n");
exit(0);
}
else
printf("connected to the server..\n");


printf("Enter the data to be transferred:\n");
scanf("%s",s);
printf("Enter CRC key:\n");
scanf("%s",q);
int i=0;
int n=strlen(s);
int m=strlen(q);
int k=n;
while(k<n+m-1)
{
s[k]='0';
k++;
}

int l=0;
while(l<m)
{
a[l]=s[l];
l++;
}
a[l]='\0';

while(i<n)
{
if(a[0]=='1')
{
for(int j=0;j<m-1;j++)
{
if(a[j+1]==q[j+1])
{
a[j]='0';
}
else
a[j]='1';
}
}
else
{
for(int j=0;j<m-1;j++)
{
if(a[j+1]=='1')
{
a[j]='1';
}
else
a[j]='0';
}
}
if(i!=n-1)
a[m-1]=s[i+m];
else
break;
i++;
}
a[m-1]='\0';
int b=0;
k=n;
while(k<n+m-1)
{
s[k]=a[b];
b++;
k++;
}
s[k]='\0';
char t[100];
int flag=0;

write(sockfd,q,sizeof(q));
write(sockfd,s,sizeof(s));
printf("\n\nMessage from Server:\n");
read(sockfd,t,sizeof(t));
for(int i=0;i<strlen(t);i++)
{
if(t[i]=='1')
{
flag=1;
break;
}
}
if(flag==0)
printf("Data succesfully received\n");
else
printf("Data got corrupted during transmission\n");
close(sockfd);
return 0;
}

