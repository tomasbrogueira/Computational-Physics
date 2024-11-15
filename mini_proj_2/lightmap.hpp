#ifndef __LIGHTMAP_HPP__
#define __LIGHTMAP_HPP__


#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>


struct cell {
std::array<double,3> center_coo {0,0,1}; // cell center coordinates (m), os valores por defeito tão mal
double area; // cell area (mˆ2)
double power; // cell incident power (W)
};


struct lightsource {
  std::array<double, 3> coo; // source coordinates (m)
  double power; // source power (W)
};



class lightmap {
  public:

  // constructors

  lightmap() = default;

  lightmap(std::array<int,2> ncell, std::array<double,2> cellsize, std::array<double,3> center_coo);
  lightmap(lightsource source, std::array<int,2> ncell, std::array<double,2> cellsize, std::array<double,3> center_coo);

  void initializeGrid();
  
  
  // getters

  const std::pair<int,int> get_CellIndex(std::array<double,3> cellCoo) const;  // return cell index

  const std::pair<double,double> get_CellCoo(int index_x, int index_y) const;  // return cell coordinates

  double getCellPower(int index_x, int index_y) const;  // return cell power (W)
  double getCellPower(std::array<double,3> cellCoo) const;   // return cell power (W)
  double getCellPower(const cell& c) const;   // return cell power (W)

  int getCellNx() const;  // return number of cells along x
  int getCellNy() const;  // return number of cells along y

  double getCellDx() const;  // return cell size along x
  double getCellDy() const;  // return cell size along y

  double getCellArea() const;  // return cell area

  double getGridArea() const;  // return grid area

  const std::vector<std::vector<cell>>& getCells() const;  // return cells grid

  // other functions

  void AddLightSource(lightsource source);  // add sources

  cell& getMaxCell() ;  // return cell with max power

  double distanceOriginCell(int index_x, int index_y) const;  // return distance from cell to origin
  double distanceOriginCell(std::array<double,3> cellCoo) const;  // return distance from cell to origin
  double distanceOriginCell(const cell& c) const;  // return distance from cell to origin

  double distancePointCell(int index_x, int index_y, std::array<double,3> pointCoo) const;  // return distance from point to cell
  double distancePointCell(std::array<double,3> cellCoo, std::array<double,3> pointCoo) const;  // return distance from point to cell
  double distancePointCell(const cell& c,  std::array<double,3> pointCoo) const;  // return distance from point to cell

  double distanceSourceCell(int index_x, int index_y, const lightsource& source) const;  // return distance from source to cell
  double distanceSourceCell(std::array<double,3> cellCoo, const lightsource& source) const;  // return distance from source to cell
  double distanceSourceCell(const cell& c, const lightsource& source) const;  // return distance from source to cell

  double distanceSourcePoint(const lightsource& source, std::array<double,3> pointCoo) const;  // return distance from source to point


  double dotProduct(std::array<double,3> v1, std::array<double,3> v2);  // return dot product

  double irradiance(std::array<double,3> pointCoo);  // return I on point

  double CellPower(cell& c) ;  // calculate the power of cell based on I (W)
  
  void updateCellPower();  // update cell power
  void updateUnitaryCellPower(cell& c);  // update cell power

  std::vector<cell> vGRID();  // return cells grid as vector

  std::vector<cell>& vGRIDsort();  // return cells grid as vector sorted by power


  double medianPower() ;  // return median power
  double meanPower() ;  // return mean power
  double maxPower() ;  // return max power
  double minPower() ;  // return min power

  double maxovermeanPower() ;  // return max/mean
  double maxovermedianPower() ;  // return max/median


  private:
  
  std::vector<std::vector<cell>> GRID;  // cells grid
  std::vector<lightsource> SOURCES;  // sources vector
  std::array<int,2> nCELL;  // number of cells along x and y
  std::array<double,2> CELLsize;  // cell size along x and y
  std::array<double,3> CENTERcoo;  // center coordinates
  std::array<double,3> NORMALvector = {0,0,1};  // normal vector
};


#endif