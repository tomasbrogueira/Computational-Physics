#include <iostream>
#include"../src/utility.hpp"
#include"../src/lightmap.hpp"
#include <TGraph.h>
#include<TF1.h>

#include<string>



int main() {
		// Define the light source
	lightsource source1{{ 0, 0, 25 }, 100};

	// Define the wall dimensions
	std::array<int, 2> ncell = {19, 19}; // Number of cells in x and y directions
	std::array<float, 2> size = { 200, 200 };  // Total Size of each cell in x and y directions

	// Create the lightmap
	lightmap map(source1, ncell, size);
	PRINT(map.RatioPower());
	PRINT(map.TotalPower());

	// Simple histogram
	map.MakeDraw("FIG_source_mapa_de_luz.png");

	// level curves histogram
	std::vector<double> rs;							// vector for radius of level curves
	for (int i = 1; i < 5; ++i) {
		rs.push_back(25*sqrt(1/(pow(sqrt(1-0.22*i),3))-1));		// Ei = (1-i*0.22) * E_max
		std::cout << rs[i-1] << std::endl;
	}
	map.MakeDrawLevel("FIG_source_1_curvas_nivel.png", rs);

	// Most powerful cells
	auto OrderedCells = map.OrderedCells();
	for (int i = 0; i < 10; ++i) {
		std::cout << i << ": " << OrderedCells[i] << std::endl;
	}

	// Total power based on distance
	std::vector<double> light_distances;
	std::vector<double> totalpower;
	for (int i = 1; i < 100; ++i) {
		light_distances.push_back(10*i);
	}
	for(auto light_distance : light_distances){
		lightsource source{{ 0, 0, (float)light_distance }, 100};
		lightmap map(source, ncell, size);
		totalpower.push_back(map.TotalPower());
	}
	
	// Create a TGraph object
	int numPoints = light_distances.size();
	TGraph* graph = new TGraph(numPoints, light_distances.data(), totalpower.data());

	// Create a canvas to display the graph
	TCanvas* canvas = new TCanvas("canvas", "Total Power", 800, 600);
	canvas->SetGrid();
	
	// Set the line color to red
	graph->SetLineColor(kRed);

	// Set the graph title and axis labels
	graph->SetTitle("Total Power");
	graph->GetXaxis()->SetTitle("Light source distance (cm)");

	// Draw the graph on the canvas
	graph->Draw("APL");

	// Save the plot as an image file (optional)
	canvas->SaveAs("FIG_source_power_distance.png");
	delete graph;

	totalpower.clear();
	light_distances.clear();

	for (int i = 10; i < 100; ++i) {
		light_distances.push_back(100*i);
	}
	for(auto light_distance : light_distances){
		lightsource source{{ 0, 0, (float)light_distance }, 100};
		lightmap map(source, ncell, size);
		totalpower.push_back(map.TotalPower());
	}
	numPoints = light_distances.size();
	graph = new TGraph(numPoints, light_distances.data(), totalpower.data());
	TF1* function = new TF1("function", "100*40000/x^2/4/3.14159", 1000., 10000.0);

	// Create a canvas to display the graph
	
	// Set the line color to red
	graph->SetLineColor(kGreen+1);
	function->SetLineColor(kBlue+2);

	// Set the graph title and axis labels
	graph->SetTitle("Total Power");
	graph->GetXaxis()->SetTitle("Light distance (cm)");

	// Draw the graph on the canvas
	graph->Draw("APL");
	function->Draw("same");

	// Save the plot as an image file (optional)
	canvas->SaveAs("FIG_source_power_large_distance.png");



	return 0;
}
