#include"lightmap.hpp"
#include<string>
#include<TEllipse.h>
#include <vector>



static std::string removeExtension(const std::string& filename)
{
    // Find the position of the last dot in the filename
    size_t dotIndex = filename.rfind('.');

    // If a dot is found and it's not the first or last character
    if (dotIndex != std::string::npos && dotIndex != 0 && dotIndex != filename.length() - 1)
    {
        // Extract the substring without the extension
        return filename.substr(0, dotIndex);
    }

    // Return the original filename if no extension is found
    return filename;
}

lightmap::lightmap(std::array<int, 2> ncell, std::array<float, 2> size) : GRID{(unsigned int)ncell[1], std::vector<cell>((unsigned int)ncell[0])} {
	// Initialize the grid with cells
	auto cellx= size[0]/ncell[0];		// cell x size
	auto celly= size[1]/ncell[1];		// cell y size
	auto offset_x = ((ncell[0]+1)%2)*0.5f;
	auto offset_y = ((ncell[1]+1)%2)*0.5f;
	cell_dim = {cellx, celly};
	for (int i = -ncell[1]/2; i < (ncell[1]+ncell[1]%2)/2; ++i) {		// y iterator
	for (int j = -ncell[0]/2; j < (ncell[0]+ncell[0]%2)/2; ++j) {		// x iterator
		GRID[i+ncell[1]/2][j+ncell[0]/2].area = cellx*celly;
		GRID[i+ncell[1]/2][j+ncell[0]/2].center_coo = {cellx*(offset_x+j),celly*(offset_y+i), 0};
		GRID[i+ncell[1]/2][j+ncell[0]/2].power = 0.0;
	}
	}
}

lightmap::lightmap(lightsource S, std::array<int, 2> ncell, std::array<float, 2> size) : lightmap(ncell, size) {
	// Add the light source to the grid
	AddLightSource(S);
}

std::pair<int, int> lightmap::GetCellIndex(float x, float y) const {
	int index_x = static_cast<int>(x / cell_dim[0]);
	int index_y = static_cast<int>(y / cell_dim[1]);
	return { index_x, index_y };
}

std::pair<float, float> lightmap::GetCellCoo(int index_x, int index_y) const {
	auto [cell_x, cell_y, cell_z] = GRID[index_y][index_x].center_coo;
	return { cell_x, cell_y};
}

double lightmap::GetCellPower(int index_x, int index_y) const {
	return GRID[index_y][index_x].power;
}

double lightmap::GetCellPower(float x, float y) const {
	std::pair<int, int> indices = GetCellIndex(x, y);
	return GetCellPower(indices.first, indices.second);
}

int lightmap::GetCellNy() const {
	return GRID.size();
}

int lightmap::GetCellNx() const {
	return GRID[0].size();
}

const std::vector<std::vector<cell>>& lightmap::GetCells() const {
	return GRID;
}

std::vector<std::vector<cell>>& lightmap::GetCells() {
	return GRID;
}

std::array<float, 3> lightmap::GetNormal() {
	// Assuming the wall is parallel to the yz plane
	return { 0.0f, 0.0f, -1.0f };
}

void lightmap::AddLightSource(lightsource S) {
	lsrcs.push_back(S);		// add light source to system
	for(auto& row : GRID){	// update power of all cells in system
		for(auto& cell : row){
			UpdateCellPower(cell, S);
		}
	}
}

const cell& lightmap::GetMaxCell() const {
	// Find the cell with the maximum power
	const cell* maxCell = &GRID[0][0];
	for (const auto& row : GRID) {
		for (const auto& c : row) {
			if (c.power > maxCell->power) {
				maxCell = &c;
			}
		}
	}
	return *maxCell;
}

float lightmap::CellPower(const cell& C) {
	// Calculate the average power received by a cell based on its area and incident power
	return Irradiance(C.center_coo) * C.area;
}

void lightmap::RecalculateCellPower(){
	for(auto& col : GRID){
		for(auto& cell_ : col){
			cell_.power = CellPower(cell_);
		}
	}
}


float lightmap::dot(std::array<float,3> v1, std::array<float, 3> v2)const{		// v1.v2
	float sum = 0;
	for (int i = 0; i < 3; ++i) {
		sum += v1[i]*v2[i];
	}
	return sum ;
}

std::array<float, 3>  lightmap::sub(std::array<float,3> v1, std::array<float, 3> v2)const{		// v1-v2
	for (int i = 0; i < 3; ++i) {
		v1[i] -= v2[i];
	}
	return v1;
}

float lightmap::distance2cell(std::array<float, 3> SourceCoo, std::array<float, 3> PointCoo) const{		// |S-P|
	std::array<float, 3> r = sub(SourceCoo, PointCoo);
	return sqrt(dot(r, r));
}

float lightmap::Irradiance(std::array<float, 3> PointCoo){		// Ei
	float Ei=0;
	for(auto l : lsrcs){
		Ei += l.power * dot(sub(PointCoo, l.coo), GetNormal()) / pow(distance2cell(l.coo, PointCoo),3) / (4* M_PI);		// power * (r.normal)/(r³ 4 PI)
	}
	return Ei;
}

float lightmap::Irradiance(std::array<float, 3> PointCoo, lightsource lsrc){
	return lsrc.power * dot(sub(PointCoo, lsrc.coo), GetNormal()) / pow(distance2cell(lsrc.coo, PointCoo),3) / (4* M_PI);		// power * (r.normal)/(r³ 4 PI)
}

float lightmap::UpdateCellPower(cell& C, lightsource lsrc){
	return C.power += Irradiance(C.center_coo, lsrc) * C.area;
}
std::ostream& operator<<(std::ostream& os, const lightmap& lm){
	for(auto& row : lm.GRID){
		for(auto& cell : row){
			os << cell.power << " ";
		}
		os << std::endl;
	}
	return os;
}

std::vector<cell> lightmap::OrderedCells() const{
	std::vector<cell> vG;
	for(auto& row : GRID){
		vG.insert(vG.end(), row.begin(), row.end());
	}
	std::sort(vG.begin(), vG.end(), [](cell& c1, cell& c2){return c1.power>c2.power;});
	return vG;
}

float lightmap::RatioPower() const{
	auto vG = OrderedCells();
	float median;
	if(vG.size() & 1)	// if size is odd
		median = vG[vG.size()/2].power;
	else				// if size is even
		median =( vG[vG.size()/2].power+ vG[vG.size()/2-1].power)/2;
	return vG[vG.size()-1].power/median;
}

float lightmap::TotalPower() const{
	float total_power;
	for(auto& row : GRID){
		for(auto& cell : row){			// loop over all cells
			total_power += cell.power;
		}
	}
	return total_power;
}

void lightmap::MakeDraw(const char* filename) const
{
    // Create a 2D histogram
    TH2F *hist = new TH2F("hist", "My Plot", GRID[0].size(), -GRID[0].size()*cell_dim[0]/2, GRID[0].size()*cell_dim[0]/2, GRID.size(), -GRID[1].size()*cell_dim[1]/2, GRID[1].size()*cell_dim[1]/2);

    // Fill the histogram with power data
    for(auto& row : GRID){
    	for(auto& cell : row){
    		hist->Fill(cell.center_coo[0], cell.center_coo[1], cell.power);
    	}
    }

    hist->SetTitle(removeExtension(filename).c_str());
    // Set the custom color palette using gStyle
    gStyle->SetPalette(kBird); // 53 corresponds to a yellow-based color palette

    // Set the plotting options
    hist->SetContour(100);    // Set the number of contour levels
    hist->SetStats(kFALSE);   // Disable statistics box
    hist->GetXaxis()->SetTitle("(cm)");
    hist->GetYaxis()->SetTitle("(cm)");

    // Create a canvas and draw the histogram
    TCanvas *canvas = new TCanvas("canvas", "My Canvas", 800, 600);
    hist->Draw("COLZ");  // COLZ option creates a color map plot
	// Add legend to color scale
    TLegend *legend = new TLegend(0.86, 0.85, 0.99, 0.98);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetTextAlign(32);
    legend->AddEntry(hist, "Intensity (W)", "palette");
    legend->SetEntrySeparation(-0.1); // Set negative value to remove the cross symbol
    legend->Draw();

    // Save the plot as an image file
    canvas->SaveAs(filename);
    delete hist;
    delete canvas;
    delete legend;
}

void lightmap::MakeDrawLevel(const char* filename, std::vector<double> radius) const
{
    // Create a 2D histogram
    TH2F *hist = new TH2F("hist", "My Plot", GRID[0].size(), -GRID[0].size()*cell_dim[0]/2, GRID[0].size()*cell_dim[0]/2, GRID.size(), -GRID[1].size()*cell_dim[1]/2, GRID[1].size()*cell_dim[1]/2);

    // Fill the histogram with power data
    for(auto& row : GRID){
    	for(auto& cell : row){
    		hist->Fill(cell.center_coo[0], cell.center_coo[1], cell.power);
    	}
    }

    hist->SetTitle(removeExtension(filename).c_str());
    // Set the custom color palette using gStyle
    gStyle->SetPalette(kBird); // 53 corresponds to a yellow-based color palette

    // Set the plotting options
    hist->SetContour(100);    // Set the number of contour levels
    hist->SetStats(kFALSE);   // Disable statistics box
    hist->GetXaxis()->SetTitle("(cm)");
    hist->GetYaxis()->SetTitle("(cm)");

    // Create a canvas and draw the histogram
    TCanvas *canvas = new TCanvas("canvas", "My Canvas", 800, 600);
    hist->Draw("COLZ");  // COLZ option creates a color map plot
			 
    // Add legend to color scale
    TLegend *legend = new TLegend(0.86, 0.85, 0.99, 0.98);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetTextAlign(32);
    legend->AddEntry(hist, "Intensity (W)", "palette");
    legend->SetEntrySeparation(-0.1); // Set negative value to remove the cross symbol
    legend->Draw();

    // Make cricles of level
    std::vector<TEllipse*> circles(radius.size());
    for (size_t i = 0; i < radius.size(); ++i) {
	    circles[i] = new TEllipse(0, 0, radius[i], radius[i]);
    	    circles[i]->SetFillColorAlpha(kBlue, 0.0);
    	    circles[i]->SetLineColor(kRed-3);
    	    circles[i]->SetLineWidth(kBlack);
    	    circles[i]->Draw();
    }

    // Save the plot as an image file
    canvas->SaveAs(filename);
    delete hist;
    delete canvas;
    delete legend;
}
