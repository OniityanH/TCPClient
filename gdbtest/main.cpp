#include <iostream>
#include <unistd.h>

using namespace std;

void bb(const int bh,const string xm){
    for (int ii =0; ii< 10000000;ii++){
        sleep(1);
        cout<<ii<<endl;
    }
}

void aa(const int no,const string name){
    bb(3,"bingbing");
}

int main(){
    aa(9,"xiaoxi");
    return 0;
}