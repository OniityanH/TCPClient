#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;

int main(){
    char path1[256];
    getcwd(path1,256);
    cout<<"path1="<<path1<<endl;

    char* path2 = get_current_dir_name();
    cout<<"path2="<<path2<<endl;
    free(path2);

    int res = mkdir("/home/zhu/gdbtest/NewFolder",0755);

    sleep(5);
    res = rmdir("/home/zhu/gdbtest/NewFolder");


    return 0;
}