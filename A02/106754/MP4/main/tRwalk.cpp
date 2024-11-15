#include"../src/Rwalk1D.hpp"
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TH1.h>
#include<iostream>
using namespace std;


int main(int argc, char *argv[])
{
	Rwalk1D R1(200);
	R1.Run(100);
	double time_points[200];
	for (int i = 0; i < 200; ++i) {
		time_points[i]=i;
	}
    // Create a TCanvas to display the graphs
    TCanvas* canvas = new TCanvas("canvas", "My Data", 800, 600);
    canvas->SetGrid();

    // Create a TGraph for each data vector
    TMultiGraph* multiGraph = new TMultiGraph();
    for (int i = 0; i < 5; ++i) {
        TGraph* graph = new TGraph(100, time_points, R1.GetTrajectory(i).data());
	for(auto& e : R1.GetTrajectory(i)){
		cout << e << ",  ";
	}
	cout << " end " << R1.GetTrajectory(i).size() << endl;
        multiGraph->Add(graph);
    }

  // Set the titles and colors for each graph
    for (int i = 0; i < multiGraph->GetListOfGraphs()->GetSize(); i++) {
        TGraph* graph = (TGraph*)multiGraph->GetListOfGraphs()->At(i);
        graph->SetTitle(("Graph " + std::to_string(i)).c_str());
        graph->SetLineColor(i + 1); // Use different color for each graph
    }

    // Draw the TMultiGraph on the canvas
    multiGraph->Draw("APL");

    // Save the plot as an image file (optional)
    canvas->SaveAs("Trajectories.png");
    TH1D* histogram_10 = new TH1D("histogram_10", "Positions after 10 steps", 20, -20., 20.);
    TH1D* histogram_100 = new TH1D("histogram_100", "Positions after 100 steps", 30, -60., 60.);

    // Set the fill color to green
    histogram_10->SetFillColor(kGreen);
    histogram_100->SetFillColor(kGreen);

    double delta_x_10 = 0;
    double delta_x_100 = 0;
    double delta_s_10 = 0;
    double delta_s_100 = 0;
    for (int i = 0; i < 200; ++i) {
	double delta_x =  R1.GetTrajectory(i)[10]-R1.GetTrajectory(i)[0];
    	delta_x_10 += delta_x;
    	delta_s_10 += abs(delta_x);
	histogram_10->Fill(delta_x);
    }
    for (int i = 0; i < 200; ++i) {
	double delta_x =  R1.GetTrajectory(i)[100]-R1.GetTrajectory(i)[0];
    	delta_x_100 += delta_x;
    	delta_s_100 += abs(delta_x);
	histogram_100->Fill(delta_x);
    }
    cout << "Valor Medio do deslocamento n = 10 : " << delta_x_10/200 << endl;
    cout << "Valor Medio do deslocamento n = 100 : " << delta_x_100/200 << endl;
    cout << "Valor Medio do afastamento n = 10 : " << delta_s_10/200 << endl;
    cout << "Valor Medio do afastamento n = 100 : " << delta_s_100/200 << endl;
	histogram_10->Draw();
	canvas->SaveAs("Histogram_10.png");
	histogram_100->Draw();
	canvas->SaveAs("Histogram_100.png");
}
