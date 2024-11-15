#include<iostream>
#include<cmath>
#include<vector>
#include<sstream>
#include<string>

using namespace std;
string prota;
string dim;
int val_max;
int nrows, ncols;
vector<vector<int>> W_matrix;
for(i = 0 ; i < 3 ; i++){
    for(j = 0 ; j < 3 ; j++){
        if(i = 1 && j = 1) W_matrix[i][j] = 0;
        else W_matrix[i][j] = 1/8;
    }
}


vector<vector<int>> ReadImage(string filename);
vector<int> ColourFreq(vector<vector<int>> image);

int main(int argc, char const *argv[])
{
    
    return 0;
}

ReadImage(string filename){  
    ifstream FI(filename);

    getline(FI,prota); getline(FI,dim); getline(FI,val_max);
    int val_max_int = stoi(val_max);

    istringstream iss(dim);
    iss >> ncols >> nrows;

    vector<vector<int>> M(nrows, vector<int>(ncols));

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++){
            FI >> M[i][j];
        }
    }
}

vector<int> ColourFreq(vector<vector<int>> image){
    vector<int> histo(256,0)   
 
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++){
            histo[image[i][j]]++;
        } 
    }
    return histo;
}

int Average_colour(vector<vector<int>> image){
    int average = 0;
    vector<int> histo = ColourFreq(image);

    for (i = 0 , i < 256, i++){
        average += histo[i]*i;
    }
    
    return average/(ncols*nrows);
}

double Varience(vector<vector<int>> image){
    double var = 0;
    int average = Average_colour(image);

    for(i = 0; i < nrows; i++){
        for(j = 0; j < ncols; j++){
            var += pow(image[i][j]-average,2);
        }
    }

    return var/(ncols*nrows-1)

}

void Inverted_image(vector<vector<int>> image){

    ofstream FO("glassware_noisy_inverted.ascii.pgm");

    FO << "P2" << endl;
    FO << ncols << nrows << endl;
    FO << val_max << endl;

    for(i = 0; i < nrows; i++){
        for(j = 0; j < ncols; j++){
            FO << (val_max-image[i][j]);
        }
        FO << endl;
    }
    FO.close();
}

void Filtered_image(vector<vector<int>> image){
    ofstream FO("glassware_reduced_noise.ascii.pgm");

    FO << "P2" << endl;
    FO << ncols << nrows << endl;
    FO << val_max << endl;

    for(i = 0; i < nrows; i++){
        for(j = 0; j < ncols; j++){
            int sum = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (i + dy < 0 || i + dy >= nrows ) continue;
                    if (j + dx < 0 || j + dx >= ncols ) continue;
                    if (dy == 0 && dx == 0) continue;
                    sum += image[i+dy][j+dx];
                }
            }
            FO << sum/8 << " ";
        }
        FO << endl;
    }    

}


void Box_filtering(vector<vector<int>> image){
    ofstream FO("glassware_box_blur.ascii.pgm");

    FO << "P2" << endl;
    FO << ncols << nrows << endl;
    FO << val_max << endl;

    for(i = 0; i < nrows; i++){
        for(j = 0; j < ncols; j++){
            int sum = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (i + dy < 0 || i + dy >= nrows ) continue;
                    if (j + dx < 0 || j + dx >= ncols ) continue;
                    if (dy == 0 && dx == 0) continue;
                    sum += image[i+dy][j+dx]*W_matrix[dy+1][dx+1];
                }
            }
            FO << sum << " ";
        }
        FO << endl;
    }
}