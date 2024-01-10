//this is a client demo 


#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc,char *argv[]){

    cout<<argc<<endl;
    if (argc!=3){
        cout<<"using :./demo1 server port 192.168.0.1\n";
        return -1;
    }
    //1 create the socket of client
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        perror("socket");
        return -1;
    }

    //2 send request to kserver 
    struct hostent* h;
    if((h = gethostbyname(argv[1]))==0) //set server ip address from ip format to 2 based format
    {
        cout<<"gethostname  failed\n";
        close(sockfd);
    }
    struct sockaddr_in servaddr;//set for store the ip and port of server

    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    memcpy(&servaddr.sin_addr,h->ls,h->h_length);//set server ip
    servaddr.sin_port = htons(atoi(argv[2])); //set server port

    //2.5   sent request to server
    if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))!=0){
        perror("connect!");
        close(sockfd);
        return -1;
    }

    char buffer[1024];
    for (int ii =0;ii <3; ii++){
        int iret;
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"this is the rank %d message, code: %03d\n",ii+1,ii+1);//set be sent message

        if((iret = send(sockfd,buffer,strlen(buffer),0))<0){//send
            perror("send!");//
            break;
        }
        cout<<"send msg:"<<buffer<<endl;

        memset(buffer,0,sizeof(buffer));

        if((iret=recv(sockfd,buffer,sizeof(buffer),0))<=0){//recieve
            cout<<"iret="<<iret<<endl;
        }
        cout<<"receive:"<<buffer<<endl;

        sleep(1);
    }
    close(sockfd);
}








