#include <iostream>
#include <time.h>
#include <sys/time.h>
using namespace std;

int main(){

    timeval start1,end1;
    gettimeofday(&start1,0);
    time_t  now1 = time(0);
    long    now2;
    time(&now2);

    cout <<"now1 = " <<now1 <<endl;
    cout <<"now2 = " <<now2 <<endl;

    time_t now;
    tm tmnow;
    time(&now);
    localtime_r(&now, &tmnow);

    string stime = to_string(tmnow.tm_year + 1900) + "-" +
                   to_string(tmnow.tm_mon + 1) + "-" +
                   to_string(tmnow.tm_mday) + " " +
                   to_string(tmnow.tm_hour) + ":" +
                   to_string(tmnow.tm_min) + ":" +
                   to_string(tmnow.tm_sec);
    cout << "Current time: " << stime << endl;

    // Add one year to tmnow
    tmnow.tm_year += 1;
    time_t nextyear_timet = mktime(&tmnow);
    tm nextyear_tm;
    localtime_r(&nextyear_timet,&nextyear_tm);
    string stime2 = to_string(nextyear_tm.tm_year+1900) + "-"
                +  to_string(nextyear_tm.tm_mon+1) + "-"
                +  to_string(nextyear_tm.tm_mday) + " "
                +  to_string(nextyear_tm.tm_hour) + ":"
                +  to_string(nextyear_tm.tm_min) + ":"
                +  to_string(nextyear_tm.tm_sec);
    cout<<"nextyear_timet:"<<stime2<<endl;


    gettimeofday(&end1,0);

    timeval timev;
    timev.tv_sec = end1.tv_sec - start1.tv_sec;
    timev.tv_usec = end1.tv_usec - start1.tv_usec;

    cout<<"elapsed:"<<timev.tv_sec<<":"<<timev.tv_usec<<endl;

    return 0;
}