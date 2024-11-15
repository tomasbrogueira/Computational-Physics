#include <Eigen/Dense>
#include <iostream>
#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TGraph.h"
#define DISPLAY

using namespace std;
using namespace Eigen;

int main (){

    //random's in [-1,1]

    MatrixXd M1(10,4);
    M1.setRandom();
    cout << "M1:" <<M1 << endl;


    MatrixXd M2 = MatrixXd :: Random(10,4); 
    cout << "M2:" << M2 << endl;

    MatrixXd M3 = MatrixXd :: Random(10,4); 
    cout << "M3:" << M3 << endl;


    // M2 : [5,10] 

    MatrixXd M4 = (2.5*M4.array()+7.5).matrix();
    cout << "M4:" << M4 << endl;


    #ifdef DISPLAY

    TApplication A("A",0,0);
    TCanvas c("c","brev",1200,1000);
    TH1F h("h","M3 randoms", 100, 0, 100);
    for (int i = 0; i < M3.rows(); i++)
  {
    for (int j = 0; j < M3.cols(); j++)
    {
      h.Fill(M3(i, j));
    }
  }
    
    h.SetFillColor(42);
    h.Draw();
    c.Update();
    gSystem->ProcessEvents();
    c.WaitPrimitive();

    #endif
}


