#include<iostream>
#include<ctime> // time
#include<random> // ranlux24
#include <array> // array
#include <algorithm> // generate
// ROOT
#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TGraph.h"
using namespace std;


void histograma(std::vector<std::vector<double>>imagem,int N, int nrows, int ncols){
    std::vector<double> freq_abs(N+1,0);
    std::vector<double> freq_rel(N+1,0);
    for(int i=0; i < nrows;i++){
        for(int j=0; j< ncols;j++){
            //std::cout << imagem[i][j] << "\n";
            freq_abs[imagem[i][j]]++;
        }
    }
    for(int i=0; i < N+1;i++){
        freq_rel[i] = (freq_abs[i])/(nrows*ncols);
        std::cout << freq_abs[i] << " ";
    }
    std::cout << "\n\n\n";
    for(int i=0; i < N+1;i++){
        std::cout << freq_rel[i] << " ";
    }
    std::cout << "\n\n\n";
}

vector<vector<int>> read_image(string filename) {
    ifstream FILE(filename);

    getline(FILE, protocol); // Read first line (protocol)

    getline(FILE, line); // Read width and height
    istringstream iss(line);
    iss >> width >> height; // Split width and height

    getline(FILE, line); // Read max value
    N = stoi(line); // Convert string to int (max value

    // Create image matrix
    vector<vector<int>> image(height, vector<int>(width));

    // Read image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            FILE >> image[i][j];
        }
    }

    FILE.close(); // Close file
    return image;
}

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

    TGraph g1(1000,arr1.data(),arr1.data()+1000);

    TApplication A("A", 0, 0);
    TCanvas C("canvas", "canvas teste", 1000, 800);
//g1.SetMarkerColor(42);
//g1.SetMarkerStyle(20);
//g1.Draw("AP");
    H.Draw();
    C.Update();
    gSystem->ProcessEvents();
    C.WaitPrimitive();
}

