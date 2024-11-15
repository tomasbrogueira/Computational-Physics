#include<cmath>
#include<iostream>
#include<vector>
using namespace std;

int main(){
    const double m_electron = 9.109e-31;
    const double electron_charge = 1.602e-19;
    const double epsilon_0 = 8.854e-12;
    const double planck = 6.626e-34;
    double n, E_h, E, n1, n2;
    int Z;
    
    vector<vector<double>> E_matrix;

    cout << "Enter the energy level: ";
    cin >> n;

    auto energy = [m_electron,electron_charge,epsilon_0,planck](double n){
        return -((pow(electron_charge,4)*m_electron)/(8*pow(M_PI,2)*pow(epsilon_0,2)*pow(planck,2)*pow(n,2)));
    };

    E_h = energy(n);
    cout << "The energy of the electron is: " << E_h << endl;
    
    
    cout << "Enter the atomic number: ";
    cin >> n;

    auto fEZ = [electron_charge,m_electron,epsilon_0,planck,n](Z){
        return -((pow(electron_charge,4)*m_electron*pow(Z,2))/(8*pow(M_PI,2)*pow(epsilon_0,2)*pow(planck,2)*pow(n,2)));
    };

    E = fEZ(n,1);
    cout << "The energy of the electron is: " << E << endl;

    cout << "Enter the atomic number: ";
    cin >> Z;

    cout << "Enter the energy level 1: ";
    cin >> n1;

    cout << "Enter the energy level 2: ";
    cin >> n2;


    auto fEL = [electron_charge,m_electron,epsilon_0,planck](Z, n1,n2){
        return -((pow(electron_charge,4)*m_electron*pow(Z,2))/(8*pow(M_PI,2)*pow(epsilon_0,2)*pow(planck,2)*pow(n1,2))) + ((pow(electron_charge,4)*m_electron*pow(Z,2))/(8*pow(M_PI,2)*pow(epsilon_0,2)*pow(planck,2)*pow(n2,2)));
    };

    double delta_E = fEL(Z,n1,n2);
    cout << "The energy of the electron is: " << delta_E << endl;
    
    
    // function to create the energy level matrix E[z][n] , z[1-10], n[1-20]

    auto fEM = [E_matrix,electron_charge,m_electron,epsilon_0,planck](int z,double n){
        for(int i=0;i<z;i++){
            for(int j=0;j<n;j++){
                E_matrix[i][j] = -((pow(electron_charge,4)*m_electron*pow(z,2))/(8*pow(M_PI,2)*pow(epsilon_0,2)*pow(planck,2)*pow(n,2)));
            }
        }
    };

    
    return 0;
}



