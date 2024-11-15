// this program recieves a .pgm file and applies a filter to it
// and saves the result in a new .pgm file
// it takes the first 3 lines from the original file and reads the image configuration (width, height, max value)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <iomanip>

using namespace std;

// function to read the image configuration
void readImageConfig(ifstream &file, int &width, int &height, int &maxValue)
{
    string line;
    getline(file, line);
    getline(file, line);
    getline(file, line);
    istringstream iss(line);
    vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());
    width = stoi(results[0]);
    height = stoi(results[1]);
    maxValue = stoi(results[2]);
}

// function to read the image data
void readImageData(ifstream &file, vector<vector<int>> &imageData, int width, int height)
{
    string line;
    int i = 0;
    while (getline(file, line))
    {
        istringstream iss(line);
        vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());
        for (int j = 0; j < width; j++)
        {
            imageData[i][j] = stoi(results[j]);
        }
        i++;
    }
}

// function to apply the filter
void applyFilter(vector<vector<int>> &imageData, vector<vector<int>> &filter, int width, int height, int filterWidth, int filterHeight)
{
    int filterCenterX = filterWidth / 2;
    int filterCenterY = filterHeight / 2;
    int sum = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width - filterWidth; j++)
        {
            for (int k = 0; k < filterHeight; k++)
            {
                for (int l = 0; l < filterWidth; l++)
                {
                    sum += filter[k][l] * imageData[i + k][j + l];
                }
            }
            imageData[i + filterCenterY][j + filterCenterX] = sum;
            sum = 0;
        }
    }
}

// function to write the image data
void writeImageData(ofstream &file, vector<vector<int>> &imageData, int width, int height, int maxValue)
{
    file << "P2" << endl;
    file << width << " " << height << endl;
    file << maxValue << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width - 1; j++)
        {
            file << imageData[i][j] << " ";
        }
        file << imageData[i][width - 1] << endl;
    }
}

int main(int argc, char *argv[])
{
    // check if the number of arguments is correct
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " <input_file> <filter_file> <output_file>" << endl;
        return 1;
    }

    // open the input file
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        cout << "Could not open input file" << endl;
        return 1;
    }

    // open the filter file
    ifstream filterFile(argv[2]);
    if (!filterFile.is_open())
    {
        cout << "Could not open filter file" << endl;
        return 1;
    }

    // open the output file
    ofstream outputFile(argv[3]);
    if (!outputFile.is_open())
    {
        cout << "Could not open output file" << endl;
        return 1;
    }

    // read the image configuration
    int width, height, maxValue;
    readImageConfig(inputFile, width, height, maxValue);

    // read the filter configuration
    int filterWidth, filterHeight;
    filterFile >> filterWidth >> filterHeight;

    // read the image data
    vector<vector<int>> imageData(height, vector<int>(width));
    readImageData(inputFile, imageData, width, height);

    // read the filter data
    vector<vector<int>> filter(filterHeight, vector<int>(filterWidth));
    for (int i = 0; i < filterHeight; i++)
    {
        for (int j = 0; j < filterWidth; j++)
        {
            filterFile >> filter[i][j];
        }
    }

    // apply the filter
    applyFilter(imageData, filter, width, height, filterWidth, filterHeight);

    // write the image data
    writeImageData(outputFile, imageData, width, height, maxValue);

    // close the files
    inputFile.close();
    filterFile.close();
    outputFile.close();

    return 0;
}

// g++ -std=c++11 rImagem.cpp -o rImagem
// ./rImagem <input_file> <filter_file> <output_file>
// ./rImagem lena.pgm filter.txt lena_filtered.pgm
