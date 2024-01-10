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


class connectTCP{
    public:
        bool recvDataTCP(string &buffer,const size_t maxlen){
            buffer.clear();
            buffer.resize(maxlen);
            if((recv(m_clientfd,&buffer[0],buffer.size(),0))<=0){//recieve
                cout<<"recv false="<<endl;
                return false;
            }
            cout<<"receive:"<<buffer<<endl;
            return true;
        }

        bool sendDataTCP(const string &buffer){
            if (m_clientfd == -1){
                return false;
            }
            if((send(m_clientfd,buffer.data(),buffer.size(),0))<=0){//send
                perror("send!");//
                return false;
            }
            cout<<"send msg:"<<buffer<<endl;
            return true;
        }
        connectTCP(){
            m_clientfd = -1;
        }
        ~connectTCP(){
            close(m_clientfd);
        }
        bool tcp_connect_process(string in_ip,const unsigned short in_port){
            m_port = in_port;
            m_ip = in_ip;
            //1 create the socket of client
            m_clientfd = socket(AF_INET,SOCK_STREAM,0);
            if(m_clientfd == -1){
                perror("socket");
                return false;
            }

            //2 send request to kserver 
            struct hostent* h;
            if((h = gethostbyname(m_ip.c_str()))==0) //set server ip address from ip format to 2 based format
            {
                cout<<"gethostname  failed\n";
                close(m_clientfd);
                m_clientfd = -1;
                return false;
            }
            struct sockaddr_in servaddr;//set for store the ip and port of server

            memset(&servaddr,0,sizeof(servaddr));
            servaddr.sin_family = AF_INET;
            memcpy(&servaddr.sin_addr,h->h_addr,h->h_length);//set server ip
            servaddr.sin_port = htons(m_port); //set server port

            //2.5   sent request to server
            if(connect(m_clientfd,(struct sockaddr*)&servaddr,sizeof(servaddr))!=0){
                perror("connect!");
                close(m_clientfd);
                m_clientfd = -1;
                return false;
            }
            return true;
        }
        int m_clientfd;
        string m_ip;
        unsigned short m_port;
};

int main(int argc,char *argv[]){
    string buffer = "this is a demo7 client";
    connectTCP tcpSocket;
    if(tcpSocket.tcp_connect_process(argv[1],atoi(argv[2])) == false){
        perror("tcp_connect_process()");
        return -1;
    }
    for (int ii =0;ii <3; ii++){
        if(tcpSocket.sendDataTCP(buffer) == false){
            perror("send failed!");
            return -1;
        }

        if(tcpSocket.recvDataTCP(buffer,1024) == false){
            perror("recv failed!");
            return -1;
        }


        sleep(1);
    }
    
}








