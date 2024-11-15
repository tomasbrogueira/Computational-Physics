#ifndef __LIGHTMAP__
#define __LIGHTMAP__ 
#include"utility.hpp"
#include<vector>
#include <cmath>
#include<iostream>
#include<algorithm>
#include <TH2.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>


class lightmap {
	/* 
		class to deal with the interactions between light sources and light receptory cells 
		cell power is automatically update upon lightsource add
	*/
public:
	lightmap() = default;
	lightmap(std::array<int, 2> ncell, std::array<float, 2> size);				// creates plane of size, with corner at (0,0), divided in ncell grid of cells 
	lightmap(lightsource S, std::array<int, 2> ncell, std::array<float, 2> size);		// same as above but also adds lightsource

	std::pair<int, int> GetCellIndex(float x, float y) const;				// Iindex of cell in GRID based on coordinates
	std::pair<float, float> GetCellCoo(int index_x, int index_y) const;			// get cell coordinates based on its index
	double GetCellPower(int index_x, int index_y) const;
	double GetCellPower(float x, float y) const;
	int GetCellNx() const;									// Number of x subdivisions in plane
	int GetCellNy() const;									// Number of y subdivisions in plane
	const std::vector<std::vector<cell>>& GetCells() const;					// retrieve GRID (const)
	std::vector<std::vector<cell>>& GetCells();						// retrieve GRID
	std::array<float, 3> GetNormal();							// return unitary vector normal to plane
	void AddLightSource(lightsource S);							// Adds light and updates cells power
	const cell& GetMaxCell() const;								// Returns cell with maximum power
	float distance2cell(std::array<float, 3> SourceCoo, std::array<float, 3> PointCoo) const;	// aux function too calculate distance between points
	std::vector<cell> OrderedCells() const;							// returns a vector with cells orderd by power
	float RatioPower() const;								// maxPower/medianPower
	float TotalPower() const;								// sum of the power of all cells
	friend std::ostream& operator<<(std::ostream& os, const lightmap& lm);			// print cell power 
	void MakeDraw(const char* filename) const;						// make bi-dimensional histogram of cell intensity
	void MakeDrawLevel(const char* filename, std::vector<double> radius) const;			// make bi-dimensional histogram of cell intensity
	float Irradiance(std::array<float,3> PointCoo);						// Calculate irradiance at specific point
	void RecalculateCellPower();

private:
	std::array<float, 2> cell_dim;
	std::vector<std::vector<cell>> GRID;							// vector of rows : GRID[y][x], stores all cells
	std::vector<lightsource> lsrcs;								// lightsources in system
	float Irradiance(std::array<float,3> PointCoo, lightsource lsrc);			// Calculate irradiance of a specific source
	float CellPower(const cell& C);								// calculate cell power and return it
	float UpdateCellPower(cell& C, lightsource lsrc);					// adds power provenient from lsrc
	float dot(std::array<float,3> v1, std::array<float, 3> v2) const;			// dot product
	std::array<float, 3>  sub(std::array<float,3> v1, std::array<float, 3> v2) const;	// subtraction of vectors
};

#endif /* ifndef __LIGHTMAP__ */
