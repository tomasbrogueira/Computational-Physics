#include<random>
#include<iostream>
#include<ctime>
#include<algorithm>
#include<array>
#include"TH1F.h"

// ROOT
# include "TH1F.h"
# include "TApplication.h"
# include "TCanvas.h"
# include "TSystem.h"

using namespace std;

int main(){
    //random generator
    ranlux24 R1(time(0)+1),R2(time(0));

    printf("%u",time(0));
    cout<<endl;

    printf("R1:");
    for (int i=0; i<10 ; i++){
        printf("%u ",R1());
    }
    cout <<endl;

    printf("R2:");
    for (int i=0; i<10 ; i++){
        printf("%u ",R2());
    }
    cout <<endl;

    // distribution

    uniform_real_distribution<double> D1(0.,10);
    printf("D1: ");
    for (int i=0; i<10 ; i++){
        printf("%.2f ",D1(R1));
    }
    cout <<endl;    
    
    //STL: generate 2000 random numbers
    
    array<double,4000> aR1;
    generate(aR1.begin(),aR1.begin()+2000, [&D1,&R1](){ return D1(R1); });

    
    //vector<double> v(2000);
    //generate(v.begin(),v.end(),[&](){return D1(R1());});
    //cout << "v.size()=" << v.size() << endl;

    TH1F H("h", "", 20, 0, 10);
    for (auto x : arr1) H.Fill(x);

    TApplication A("A", 0, 0);  
    TCanvas C("canvas", "canvas teste", 1000, 800);

    H.draw();
    C.Update();
    gSystem->ProcessEvents();
    C.waitPrimitive();

}