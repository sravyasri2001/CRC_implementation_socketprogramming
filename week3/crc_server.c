#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include <unistd.h>
#include<stdlib.h>
#define MAX 80
#define SERV_TCP_PORT 8080
#define SA struct sockaddr
int main()
{
int sockfd,newsockfd,clength;
struct sockaddr_in serv_addr,cli_addr;
char s[100],a[100],q[100];
sockfd=socket(AF_INET,SOCK_STREAM,0);

if (sockfd == -1) {
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");

serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=INADDR_ANY;
serv_addr.sin_port=htons(SERV_TCP_PORT);

if ((bind(sockfd, (SA*)&serv_addr, sizeof(serv_addr))) != 0) {
printf("socket bind failed...\n");
exit(0);
}
else
printf("Socket successfully binded..\n");

if ((listen(sockfd, 5)) != 0) {
printf("Listen failed...\n");
exit(0);
}
else
printf("Server listening..\n");

clength=sizeof(cli_addr);
newsockfd=accept(sockfd, (SA*)&cli_addr, &clength);

if (newsockfd< 0) {
printf("server acccept failed...\n");
exit(0);
}
else
printf("server acccept the client...\n");

read(newsockfd,q,sizeof(q));
read(newsockfd,s,sizeof(s));
s[4]='1';

printf("Data recieved:%s\n",s);
printf("CRC key provided by sender:%s\n",q);

int i=0;
int n=strlen(s);
int m=strlen(q);
int k=n;
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
write(newsockfd,a,sizeof(a));
close(sockfd);
return 0;
}
