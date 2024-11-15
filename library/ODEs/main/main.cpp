#include "../src/ODEsolver.h"
#include <vector>
#include <iostream>
#include <functional>
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TPad.h"
#include "../src/ODEpoint.h"
#include "../src/BVSolver.hpp"
#include <cmath>

using namespace std;

int main(){
    const double g = 9.806;
    const double L  = 4.;
    const double m = 0.5;
    
    
    // init point
    auto Em = [g,L](ODEpoint P){return 0.5 * pow(P[1]*L,2) + g*L * (1-cos(P[0]));};
    ODEpoint P0(0, {M_PI/6, 0}); 
    cout << P0 << endl;
    cout << Em(P0) << endl;

    // functions
    vector<std::function<double(ODEpoint)>> functions {
        [](ODEpoint P)->double {return P.X()[1];}, 
        [=](ODEpoint P)->double {return -(g/L)*sin(P[0]);},
    };

    vector<double> time;
    vector<double> Em_eu;
    vector<double> Em_tr;
    vector<double> Em_lf;
    vector<double> Em_RK2;
    vector<double> Em_RK4;

    ODEsolver S(functions);
    cout <<"func\n";
    double step = 0.1; // [s]
    double Ttotal = 25;
    for (double t = 0; t < Ttotal; t+=step) {
    	time.push_back(t);
    }

    cout<<"Euler: "<<endl;
    auto eulerv = S.Euler(P0, step, Ttotal);
    auto eulerv1 = S.Euler(P0, step/10., Ttotal);

    for(auto& e : eulerv){
	//cout << e << ", ";
    	Em_eu.push_back(Em(e)/Em(P0));
    }

    cout<<eulerv.back()<<endl;
    cout<<"-----------------------------------------------"<<endl;

    cout<<"Trapezoidal: "<<endl;

    auto predictorcorrectorv = S.PredictorCorrector(P0, step, Ttotal);
    auto predictorcorrectorv1 = S.PredictorCorrector(P0, step/10., Ttotal);
    for(auto& e : predictorcorrectorv){
	//cout << e << ", ";
    	Em_tr.push_back(Em(e)/Em(P0));
    }
    cout<<predictorcorrectorv.back()<<endl;
    cout<<"-----------------------------------------------"<<endl;

    cout<<"LeapFrog: "<<endl;
    auto leapfrogv = S.LeapFrog(P0, step, Ttotal);
    auto leapfrogv1 = S.LeapFrog(P0, step/10., Ttotal);
    for(auto& e : leapfrogv){
    	Em_lf.push_back(Em(e)/Em(P0));
    }

    cout<<leapfrogv.back()<<endl;
    cout<<"-----------------------------------------------"<<endl;

    cout<<"RK2: "<<endl;
    auto rk2v = S.RK2(P0, step, Ttotal);
    auto rk2v1 = S.RK2(P0, step/10., Ttotal);

    for(auto& e : rk2v){
    	Em_RK2.push_back(Em(e)/Em(P0));
    }

    cout<<rk2v.back()<<endl;
    cout<<"-----------------------------------------------"<<endl;

    cout<<"RK4: "<<endl;
    auto rk4v = S.RK4(P0, step, Ttotal);
    auto rk4v1 = S.RK4(P0, step/10., Ttotal);
    for(auto& e : rk4v){
    	Em_RK4.push_back(Em(e)/Em(P0));
    }

    cout<<rk4v.back()<<endl;
    cout<<"-----------------------------------------------"<<endl;

    TCanvas* c = new TCanvas("c", "Title", 1600, 1000);
    TGraph g1 = TGraph(time.size(), time.data(), Em_eu.data());
    g1.Draw("AL");
    TGraph g2 = TGraph(time.size(), time.data(), Em_lf.data());
    g2.Draw("same");
    TGraph g3 = TGraph(time.size(), time.data(), Em_tr.data());
    g3.Draw("same");
    TGraph g4 = TGraph(time.size(), time.data(), Em_RK2.data());
    g4.Draw("same");
    TGraph g5 = TGraph(time.size(), time.data(), Em_RK4.data());
    g5.Draw("same");
    c->SaveAs("Em.png");
	

    vector<double> Time1, Angle1, Vel1, Time2, Angle2, Vel2, Time3, Angle3, Vel3, Time4, Angle4, Vel4, Time5, Angle5, Vel5;
    vector<double> Time6, Angle6, Vel6, Time7, Angle7, Vel7, Time8, Angle8, Vel8, Time9, Angle9, Vel9, Time10, Angle10, Vel10;
    for(auto v: rk4v){
        Time1.push_back(v.T());
        Angle1.push_back(v.X()[0]);
        Vel1.push_back(v.X()[1]);
    }

    for(auto v: rk2v){
        Time2.push_back(v.T());
        Angle2.push_back(v.X()[0]);
        Vel2.push_back(v.X()[1]);
    }


    for(auto v: eulerv){
        Time3.push_back(v.T());
        Angle3.push_back(v.X()[0]);
        Vel3.push_back(v.X()[1]);
    }


    for(auto v: predictorcorrectorv){
        Time4.push_back(v.T());
        Angle4.push_back(v.X()[0]);
        Vel4.push_back(v.X()[1]);
    }


    for(auto v: leapfrogv){
        Time5.push_back(v.T());
        Angle5.push_back(v.X()[0]);
        Vel5.push_back(v.X()[1]);
    }

    // For step/10
    for(auto v: rk4v1){
        Time6.push_back(v.T());
        Angle6.push_back(v.X()[0]);
        Vel6.push_back(v.X()[1]);
    }

    for(auto v: rk2v1){
        Time7.push_back(v.T());
        Angle7.push_back(v.X()[0]);
        Vel7.push_back(v.X()[1]);
    }


    for(auto v: eulerv1){
        Time8.push_back(v.T());
        Angle8.push_back(v.X()[0]);
        Vel8.push_back(v.X()[1]);
    }


    for(auto v: predictorcorrectorv1){
        Time9.push_back(v.T());
        Angle9.push_back(v.X()[0]);
        Vel9.push_back(v.X()[1]);
    }


    for(auto v: leapfrogv1){
        Time10.push_back(v.T());
        Angle10.push_back(v.X()[0]);
        Vel10.push_back(v.X()[1]);
    }


    c->Clear();
    c->Divide(2, 1);
    c->cd(1);
    TGraph* graph1 = new TGraph(rk4v.size(), Time1.data(), Angle1.data());
    TGraph* graph2 = new TGraph(rk2v.size(), Time2.data(), Angle2.data());
    TGraph* graph3 = new TGraph(eulerv.size(), Time3.data(), Angle3.data());
    TGraph* graph4 = new TGraph(predictorcorrectorv.size(), Time4.data(), Angle4.data());
    TGraph* graph5 = new TGraph(leapfrogv.size(), Time5.data(), Angle5.data());
    
    // RK4
    graph1->Draw();
    graph1->SetTitle("angle(rad(ical))");
    graph1->GetXaxis()->SetTitle("time (s)");
    graph1->SetLineWidth(3);
    graph1->SetLineColor(kBlue);

    // RK2
    graph2->Draw("same");
    graph2->SetTitle("angle(rad(ical))");
    graph2->GetXaxis()->SetTitle("time (s)");
    graph2->SetLineWidth(3);
    graph2->SetLineColor(kGreen);

    // Euler
    graph3->Draw("same");
    graph3->SetTitle("angle(rad(ical))");
    graph3->GetXaxis()->SetTitle("time (s)");
    graph3->SetLineWidth(3);
    graph3->SetLineColor(kRed);

    // Trapezoidal
    graph4->Draw("same");
    graph4->SetTitle("angle(rad(ical))");
    graph4->GetXaxis()->SetTitle("time (s)");
    graph4->SetLineWidth(3);
    graph4->SetLineColor(kYellow);

    // Leapfrog
    graph5->Draw("same");
    graph5->SetTitle("angle(rad(ical))");
    graph5->GetXaxis()->SetTitle("time (s)");
    graph5->SetLineWidth(3);
    graph5->SetLineColor(kViolet);

    c->cd(2);
    TGraph* graph6 = new TGraph(rk4v1.size(), Time6.data(), Angle6.data());
    TGraph* graph7 = new TGraph(rk2v1.size(), Time7.data(), Angle7.data());
    TGraph* graph8 = new TGraph(eulerv1.size(), Time8.data(), Angle8.data());
    TGraph* graph9 = new TGraph(predictorcorrectorv1.size(), Time9.data(), Angle9.data());
    TGraph* graph10 = new TGraph(leapfrogv1.size(), Time10.data(), Angle10.data());
    
    // RK4, step/10
    graph6->Draw();
    graph6->SetTitle("angle(rad(ical))");
    graph6->GetXaxis()->SetTitle("time (s)");
    graph6->SetLineWidth(3);
    graph6->SetLineColor(kBlue);

    // RK2, step/10
    graph7->Draw("same");
    graph7->SetTitle("angle(rad(ical))");
    graph7->GetXaxis()->SetTitle("time (s)");
    graph7->SetLineWidth(3);
    graph7->SetLineColor(kGreen);

    // Euler, step/10
    graph8->Draw("same");
    graph8->SetTitle("angle(rad(ical))");
    graph8->GetXaxis()->SetTitle("time (s)");
    graph8->SetLineWidth(3);
    graph8->SetLineColor(kRed);

    // Trapezoidal, step/10
    graph9->Draw("same");
    graph9->SetTitle("angle(rad(ical))");
    graph9->GetXaxis()->SetTitle("time (s)");
    graph9->SetLineWidth(3);
    graph9->SetLineColor(kYellow);

    // Leapfrog, step/10
    graph10->Draw("same");
    graph10->SetTitle("angle(rad(ical))");
    graph10->GetXaxis()->SetTitle("time (s)");
    graph10->SetLineWidth(3);
    graph10->SetLineColor(kViolet);

    gPad->SetGrid();
    //A.Run();
    c->Update();
    //gSystem->ProcessEvents();
    //c->WaitPrimitive();
    c->SaveAs("Pendulum.png");

    array<function<double(double)>, 4> Func={
		    [](double x){return 1.;},
		    [](double x){return (1-x)*-4.;},
		    [](double x){return cos(6*x);},
		    [](double x){return 0;}
    };
    BVSolver BV(Func);
    ODEpoint pi(0,{1,});
    vector<ODEpoint> pf;
    for (int i = 0; i < 10; ++i) {
    	pf.push_back(ODEpoint{2, {1+0.10*i}});
    }
    vector<vector<ODEpoint>> sol;
    for(auto& p : pf){
    	sol.push_back(BV.Solve(pi, p, 100));
    }
    vector<double> x_sol;
    for(auto& v : sol[0]){
    	x_sol.push_back(v.T());
    }
    vector<vector<double>> y_sol;
    for(auto s: sol){
	    y_sol.push_back(vector<double>(0));
	    for(auto& v : s){
	    	y_sol.back().push_back(v[0]);
	    }
    }
    delete c;
    c = new TCanvas("c", "Title", 1600, 1000);
    TGraph* gsol = new TGraph(x_sol.size(), x_sol.data(), y_sol.back().data());
    gsol->Draw("APL");
    vector<TGraph*> BVsol;
    for(auto& v : y_sol){
    	BVsol.push_back(new TGraph(x_sol.size(), x_sol.data(), v.data()));
	BVsol.back()->Draw("same");
    }
    c->Update();
    c->SaveAs("BV.png");
}
