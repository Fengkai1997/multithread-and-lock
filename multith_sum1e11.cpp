#include<iostream>
#include<thread>
#include<vector>
#include <chrono>

using namespace std;


const long N = 10000000000;





void calculate(long n,long spp, vector<long>&sum2){
    sum2[n]=0;
    for (long i=n*spp;i<(n+1)*spp;i++){
        sum2[n] = sum2[n] +i;
    }
}



int main(){

    auto start = std::chrono::steady_clock::now();//measure the start time 

    long long ssum=0;
    int hardware_threads = thread::hardware_concurrency()/2; //the number of thread
    //int hardware_threads = 16;

    vector<long>sum2(hardware_threads);
    vector<thread> threads(hardware_threads); //create threads

    int rem = N % hardware_threads;//take the reminder
    long spl = (N-rem)/hardware_threads;//get the split
    cout<<rem<<"//"<<spl<<"//"<<hardware_threads;

    for (int i=0;i<hardware_threads;i++){
        threads[i] = thread(calculate,i,spl,ref(sum2));//input the variable into new thread  
    }
    
    for (int i=0;i<hardware_threads;i++){
       threads[i].join();
    }

    for (int i=0;i<hardware_threads;i++){
        ssum = ssum + sum2[i];

    }
    ssum = ssum + ( (N-rem)+N)*rem/2;
    cout<<"sum of 1e10 is "<<ssum<<endl;

    auto finish = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    std::cout << "the calculating time is "<<duration.count() << "ms" << std::endl;


}
