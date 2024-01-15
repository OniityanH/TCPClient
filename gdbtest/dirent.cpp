#include <iostream>
#include <dirent.h>

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 2){
        cout<<"using ...."<<endl;
        return -1;
    }

    DIR* dir;
    if((dir = opendir(argv[1])) == nullptr){
        return -1;
    }

    struct dirent* stdinfo= nullptr;
    stdinfo->
    while(1){
        if((stdinfo =readdir(dir)) == nullptr){
            break;
        }

        cout<<"file name = "<<stdinfo->d_name<<",type = "<<(int)stdinfo->d_type<<endl;
    }
    closedir(dir);
}