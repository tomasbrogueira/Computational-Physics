#include <iostream>
using namespace std;

int main(){
    int x = 12;
    float y = 6.9;

    auto f = [&](){
        x+=1;
        return x+y;
    };

    
    cout << f() << endl;
    cout << x << endl;

    return 0;
}