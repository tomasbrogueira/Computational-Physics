#include<iostream>
#include<cmath>
using namespace std;

int main(){
    float x;
    cout << "Enter an number: " << flush;
    cin >> x;
    float y = pow(sin(x),2);
    float sum = x + y;
    cout << "Result = " << sum << endl;
    return 0;
}