# include <random> // random number generators
# include <iostream> // cout
# include <ctime> // time
# include <array> // array
# include <algorithm> // generate

// ROOT
# include "TH1F.h"
# include "TApplication.h"
# include "TCanvas.h"
# include "TSystem.h"


using namespace std;

int main() {
    int t = time(0);
    ranlux24 r1(t), r2(t+1);

    // Distributions
    uniform_real_distribution<double> u(0, 10);

    // Generate 2000 random numbers with STL
    array<double, 2000> arr1;
    generate(arr1.begin(), arr1.end(), [&u, &r1]() { return u(r1); });

    TH1F H("h", "", 20, 0, 10);
    for (auto x : arr1) H.Fill(x);

    TApplication A("A", 0, 0);  
    TCanvas C("canvas", "canvas teste", 1000, 800);

    H.Draw();
    C.Update();
    gSystem->ProcessEvents();
    C.WaitPrimitive();
}