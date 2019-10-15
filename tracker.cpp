#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<sys/types.h>
#include<string.h>
#include<iostream>
#include<sys/socket.h>
#include<map>
#include<vector>
#include <unistd.h> 
#include<pthread.h>
#include<bits/stdc++.h>

using namespace std; 

//////////////////////////
class Detail
{
	public:
	int port;
	int ip;

	
	string file_name;
};
map<string,string>m;

int main()
{
	vector<Detail>v(100);

	
	int i=0,flag=0;
    int sockfd,ret,newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_in newAddr;
	socklen_t addr_size;
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
	{
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Server Socket is created.\n");
    memset(&serverAddr,'\0',sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(4444);
	serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    ret=bind(sockfd,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret<0)
	{
		printf("Error in binding.\n");
		exit(1);
	}
	printf("Bind to port %d\n",4444);
    if(listen(sockfd,10)==0)
	{
	    printf("Listening....\n");
	}
	else
	{
		printf("Error in binding.\n");
	}
    char buffer[1024];
	char s1[1024];
	char s2[1024];
	//string buffer1;
	while(1)
	{
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
	if(newSocket < 0)
        {
			exit(1);
		}
	printf("Connection accepted  \n");
	recv(newSocket, (buffer), 1024, 0);
     cout<<buffer<<endl;
     int size=1024;
	 if(strcmp(buffer,"create account")==0)
	 {
		 send(newSocket,"write your user name and pwd" ,1024, 0);
		 recv(newSocket, s1, 1024, 0);
		 send(newSocket,"validating......" ,1024, 0);
		 recv(newSocket, buffer, 1024, 0);
		 send(newSocket,"processing......" ,1024, 0);
		 if(m.find(s1)!=m.end())
		 {
			 send(newSocket,"user name exist" ,1024, 0);
			 cout<<"user name exist";
		 send(newSocket,"done" ,1024, 0);
		 }
		 else
		 {
			 send(newSocket,"done" ,1024, 0);
			 cout<<"done"<<endl;
             //recv(newSocket, (s2), 1024, 0);
			//m[s1]=s2;
		 }
		 recv(newSocket, (s2), 1024, 0);
			m[s1]=s2;
	 }
	 else if(strcmp(buffer,"login")==0)
	 {
		 send(newSocket,"write your user name and pwd" ,1024, 0);
		 recv(newSocket, s1, 1024, 0);
		 send(newSocket,"ok..done" ,1024, 0);
			 send(newSocket,"done" ,1024, 0);
			 cout<<"done"<<endl;
             recv(newSocket, (s2), 1024, 0);
			m[s1]=s2;
	 }
	 else if(strcmp(buffer,"logout")==0)
	 {
     send(newSocket,"do you really want to log out" ,1024, 0);
	 }
	 else if(strcmp(buffer,"download")==0)
	 {
		 int arr[3]={5555,6666,7777};
    send(newSocket,arr ,3*sizeof(int), 0);
	recv(newSocket, (buffer), 1024, 0);
 cout<<buffer;
     v[i++].file_name=buffer;
	//send(newSocket,"start" ,1024, 0);
    bzero(buffer,256);
	 }
else 
	{
		if(flag==0)
	{
		cout<<"no data"<<endl;
		flag=1;
	}
	else
   {
	   int arr[3]={5555,6666,7777};
    send(newSocket,arr ,3*sizeof(int), 0);
	recv(newSocket, (buffer), 1024, 0);
     v[i++].file_name=buffer;
	
    bzero(buffer,256);
   }
	}
    close(newSocket);

	}
	
    close(sockfd);
	 return 0;
}


///////////////////////////////////////////////////


