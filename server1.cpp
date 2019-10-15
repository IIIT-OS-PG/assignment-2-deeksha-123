#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
 #include <arpa/inet.h>
#include<sys/types.h>
#include<string.h>
#include<iostream>
#include<sys/socket.h>

#include <unistd.h> 
#include<pthread.h>
//#include<sstream>
#include<bits/stdc++.h>

using namespace std; 




//////////////////////////////////
int newSocket;
void* data_transfer(void*arg)
{
    char buffer[1024];
	int *p=(int *)arg;
    int l=*p;
	FILE *fp=fopen("try.txt","rb");
    fseek(fp,0,l*1024);
    int size=1024;
    send(newSocket,&size,sizeof(size),0);
    int n;
    while ( ( n = fread( buffer , sizeof(char) , 1024, fp ) ) > 0  && size > 0 )
{
	send (newSocket, buffer, n, 0 );
   	memset ( buffer , '\0', 1024);
	size = size - n ;
}
fclose(fp);
pthread_exit(0);
}




//////////////////////////////////




void* server_fun(void* arg)
{
    int *p=(int *)arg;
    int l=*p;
    int sockfd, ret;
	struct sockaddr_in serverAddr;
    struct sockaddr_in newAddr;
     socklen_t addr_size;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Server Socket is created.\n");
    memset(&serverAddr,'\0',sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(l);
	serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    ret = bind(sockfd,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret<0)
	{
	printf("Error in binding.\n");
	exit(1);
	}
	printf("Bind to port \n");
    if(listen(sockfd,10)==0)
	{
	printf("Listening....\n");
	}
	else
	{
	printf("Error in binding.\n");
	}
	newSocket=accept(sockfd,(struct sockaddr*)&newAddr,&addr_size);
	if(newSocket<0)
        {
		exit(1);
		}
		printf("Connection accepted \n");
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
	int m1=0;
	int m2=1;
    pthread_create(&tid[0],&attr,data_transfer,&m1);
    pthread_create(&tid[1],&attr,data_transfer,&m2);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
	close(newSocket);
    close(sockfd);
    pthread_exit(0);
}



///////// client funtion


void* client1_fun(void* arg)
{
    int *p=(int *)arg;
    int l=*p;
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd==-1)
    printf("error");
    struct sockaddr_in serv_addr;
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(l);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    int connection_status=connect(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(connection_status==-1)
    printf("error1");
    FILE *fp=fopen("bsh.txt","wb");
    char buffer[1024];
    int file_size;
    cout<<"before loop";
    recv(socket_fd,&file_size,sizeof(file_size),0);
     int n;
while ( ( n = recv( socket_fd , buffer , 1024, 0) ) > 0  &&  file_size > 0)
{
fwrite (buffer , sizeof (char), n, fp);
memset ( buffer , '\0', 1024);
file_size = file_size - n;
} 
fclose(fp);
printf("file received successfully");
close(socket_fd);
pthread_exit(0);
}



/////////////////////////////////////////////////////

void download_file()
{
int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd==-1)
         printf("error");
struct sockaddr_in serv_addr;
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(4444);
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
int connection_status=connect(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
if(connection_status==-1)
printf("connection error1.\n");
int buffer[1024];

//buffer1="bash";
int n;
send(socket_fd,"download" ,1024, 0);
recv(socket_fd, buffer,1024, 0);
cout<<buffer[0];
send(socket_fd,"kk" ,1024, 0);
pthread_t tid[2];
pthread_attr_t attr;
pthread_attr_init (&attr);
for(int i=0;i<3;i++)
{
	int p=buffer[i];
	pthread_create(&tid[i],&attr,client1_fun,&p);
}
for(int i=0;i<3;i++)
     pthread_join(tid[i],NULL);
     close(socket_fd);
     pthread_exit(0);
}



/////////////////////////////////////////////////



void run_client()
{
	int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd==-1)
         printf("error");
struct sockaddr_in serv_addr;
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(4444);
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
int connection_status=connect(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
if(connection_status==-1)
printf("connection error1.\n");
int buffer[1024]={0};
int n;
send(socket_fd,"run client" ,1024, 0);
recv(socket_fd, buffer,1024, 0);
for(int i=0;i<3;i++)
{
	int p=buffer[i];
	cout<<p<<endl;
	
}
send(socket_fd,"done" ,1024, 0);
     close(socket_fd);
}

////////////////////////////////

void create_user_account()
{
int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd==-1)
         printf("error");
struct sockaddr_in serv_addr;
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(4444);
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
int connection_status=connect(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
if(connection_status==-1)
printf("connection error1.\n");
char buffer[1024],s1[1024],s2[1024];
int size=1024;
send(socket_fd,"create account" ,1024, 0);
recv(socket_fd, buffer,1024, 0);
 cout<<buffer<<endl;
 memset ( buffer , '\0', 1024);
 cin>>s1;
send(socket_fd,s1,1024,0);
recv(socket_fd, buffer,1024, 0);
cout<<buffer<<endl;
int l;
cin>>l;
cout<<endl;
send(socket_fd,"11",1024,0);
//memset ( buffer , '\0', 1024);
recv(socket_fd, buffer,1024, 0);
cout<<buffer;
//memset ( buffer , '\0', 1024);
recv(socket_fd, buffer,1024, 0);
cout<<buffer;
if(strcmp(buffer,"user name exist")==0)
{
	cin>>s1;
	memset ( buffer , '\0', 1024);
recv(socket_fd, buffer,1024, 0);
cout<<buffer;
memset ( buffer , '\0', 1024);
}
else 
{
	recv(socket_fd, buffer,1024, 0);
cout<<buffer<<endl;
}
cin>>s2;
send(socket_fd,s2,1024,0);



     close(socket_fd);
}

////////////////////////////

void login()
{
int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd==-1)
         printf("error");
struct sockaddr_in serv_addr;
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(4444);
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
int connection_status=connect(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
if(connection_status==-1)
printf("connection error1.\n");
char buffer[1024],s1[1024],s2[1024];
int size=1024;
send(socket_fd,"login" ,1024, 0);
recv(socket_fd, buffer,1024, 0);
 cout<<buffer<<endl;
 memset ( buffer , '\0', 1024);
 cin>>s1>>s2;
send(socket_fd,s1,1024,0);
recv(socket_fd, buffer,1024, 0);
cout<<buffer<<endl;
memset ( buffer , '\0', 1024);
recv(socket_fd, buffer,1024, 0);
cout<<buffer;
send(socket_fd,s2,1024,0);
 close(socket_fd);
}

////////////////////////////////


void create_group()
{

}
//////////////////////////////////

void join_group()
{

}

//////////////////////////////////

void leave_group()
{

}
///////////////////////////

void list_pending()
{

}

///////////////////////

void accept_group()
{

}
///////////////////

void show_all_group()
{

}
////////////////////


void list_all_sharable_files()
{

}
////////////////////////

void upload_file(char  s[])
{
	
	cout<<s;
int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd==-1)
         printf("error");
struct sockaddr_in serv_addr;
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(4444);
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
int connection_status=connect(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
if(connection_status==-1)
printf("connection error1.\n");
//string buffer1[1024];
//buffer1[0]=s;
int buffer[3];
int n;
send(socket_fd, s,1024, 0);
cout<<"file uploaded";

     close(socket_fd);
}

/////////////////////

void logout()
{
int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd==-1)
         printf("error");
struct sockaddr_in serv_addr;
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(4444);
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
int connection_status=connect(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
if(connection_status==-1)
printf("connection error1.\n");
char buffer[1024];
 send(socket_fd,"logout" ,1024, 0);
 recv(socket_fd, buffer, 1024, 0);
 cout<<buffer<<endl;
 string s;
 cin>>s;
 if(s=="yes")
exit(0);
else
cout<<"ok";
 close(socket_fd);
}

///////////////////////////

void* client_fun(void* arg)
{
	int n,m;
	cin>>n;
	if(n==1)
    {
		cout<<"run client....press 1"<<endl;
	    cout<<"create user account....press 2"<<endl;
	    cout<<"log in....press 3"<<endl;
	    cout<<"create group....press 4"<<endl;
	    cout<<"join group....press 5"<<endl;
	    cout<<"leave group....press 6"<<endl;
	    cout<<"list pending join requests...press 7"<<endl;
	    cout<<"accept group joining req....press 8"<<endl;
	    cout<<"list all group in network....press 9"<<endl;
	    cout<<"list all sharable files in group....press 10"<<endl;
	    cout<<"upload file....press 11"<<endl;
	    cout<<"download file....press 12"<<endl;
	    cout<<"log out....press 13"<<endl;
		cin>>m;
		switch(m)
		{
			case 1:run_client();
			 break;
			 case 2:create_user_account();
			 break;
			 case 3:login();
			 break;
			 case 4:create_group();
			 break;
			 case 5:join_group();
			 break;
			 case 6:leave_group();
			 break;
			 case 7:list_pending();
			 break;
			 case 8:accept_group();
			 break;
			 case 9:show_all_group();
			 break;
			 case 10:list_all_sharable_files();
			 break;
			 case 11:
			 {
				 cout<<"enter the file name";
			 char s[100];
			 cin>>s;
			 upload_file(s);
			 break;
			 }
			 case 12:
			 {
				// cout<<"enter file name";
			 //char  s[100];
			// cin>>s;
			
			 download_file();
			 break;
			 }
			 case 13:logout();
			 break;
        }

	}

}

//////////////////////////////////////////////////

int main(int argc,char **argv)
{
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int port=atoi(argv[1]);
    pthread_create(&tid[0],&attr,server_fun,&port);
    pthread_create(&tid[1],&attr,client_fun,NULL);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    return 0;
}
