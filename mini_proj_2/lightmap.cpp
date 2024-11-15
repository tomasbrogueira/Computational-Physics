#include "lightmap.hpp"


// constructors



lightmap::lightmap(std::array<int,2> ncell, std::array<double,2> cellsize, std::array<double,3> center_coo) : nCELL(ncell), CELLsize(cellsize), CENTERcoo(center_coo) {
    initializeGrid();
}

lightmap::lightmap(lightsource source, std::array<int,2> ncell, std::array<double,2> cellsize, std::array<double,3> center_coo) {
    initializeGrid();
    AddLightSource(source);
}

void lightmap::initializeGrid() {
    // initialize grid
    // ncell = {nx,ny}
    // cellsize = {dx,dy}
    // center_coo = {x0,y0,z0}

    // set number of cells
    int nx = nCELL[0];
    int ny = nCELL[1];

    // set cell size
    double dx = CELLsize[0];
    double dy = CELLsize[1];
    double c_area = dx*dy;

    // set center coordinates
    double x0 = CENTERcoo[0];
    double y0 = CENTERcoo[1];
    double z0 = CENTERcoo[2];

    // set grid
    for (int i = -nx/2; i < nx/2; i++) {
        std::vector<cell> row;
        for (int j = -ny/2; j < ny/2; j++) {
            cell c;
            c.center_coo = {x0 + (i+0.5)*dx, y0 + (j+0.5)*dy, z0};
            c.area = c_area;
            c.power = 0;
            row.push_back(c);
        }
        GRID.push_back(row);
    }
}








// getters








const std::pair<int,int> lightmap::get_CellIndex(std::array<double,3> cellCoo) const {
    // return cell index
    // cellCoo = {x,y,z}
    // index = {index_x, index_y}

    // get cell coordinates
    double x = cellCoo[0];
    double y = cellCoo[1];

    // get cell size
    double dx = CELLsize[0];
    double dy = CELLsize[1];

    // get center coordinates
    double x0 = CENTERcoo[0];
    double y0 = CENTERcoo[1];

    // get cell index
    int index_x = ((x-x0)/dx) + nCELL[0]/2;
    int index_y = ((y-y0)/dy) + nCELL[1]/2;

    return {index_x, index_y};
}

const std::pair<double,double> lightmap::get_CellCoo(int index_x, int index_y) const {
    // return cell coordinates
    // index = {index_x, index_y}
    // cellCoo = {x,y,z}

    // get cell size
    double dx = CELLsize[0];
    double dy = CELLsize[1];

    // get center coordinates
    double x0 = CENTERcoo[0];
    double y0 = CENTERcoo[1];

    // get cell coordinates
    double x = x0 + (index_x-nCELL[0]/2)*dx;
    double y = y0 + (index_y-nCELL[1]/2)*dy;

    return {x, y};
}


double lightmap::getCellPower(int index_x, int index_y) const {
    // return cell power
    // index = {index_x, index_y}

    // get cell power
    return GRID[index_x][index_y].power;
}

double lightmap::getCellPower(std::array<double,3> cellCoo) const {
    // return cell power
    // cellCoo = {x,y,z}

    // get cell index
    std::pair<int,int> index = get_CellIndex(cellCoo);
    int index_x = index.first;
    int index_y = index.second;

    // get cell power
    return GRID[index_x][index_y].power;
}

double lightmap::getCellPower(const cell& c) const {
    // return cell power
    // c = cell

    // get cell index
    std::pair<int,int> index = get_CellIndex(c.center_coo);
    int index_x = index.first;
    int index_y = index.second;

    // get cell power
    return GRID[index_x][index_y].power;
}





// cell size related methods




int lightmap::getCellNx() const {
    // return number of cells in x direction
    return nCELL[0];
}

int lightmap::getCellNy() const {
    // return number of cells in y direction
    return nCELL[1];
}

double lightmap::getCellDx() const {
    // return cell size in x direction
    return CELLsize[0];
}

double lightmap::getCellDy() const {
    // return cell size in y direction
    return CELLsize[1];
}

double lightmap::getCellArea() const {
    // return cell area
    return CELLsize[0]*CELLsize[1];
}

double lightmap::getGridArea() const {
    // return grid area
    return nCELL[0]*nCELL[1]*getCellArea();
}






// outta place methods





const std::vector<std::vector<cell>>& lightmap:: getCells() const {
    // return grid
    return GRID;
}

void lightmap::AddLightSource(lightsource source) {
    SOURCES.push_back(source);
}

cell& lightmap::getMaxCell() {
    // return cell with maximum power
    return vGRIDsort()[0];
}







// distance methods






double lightmap::distanceOriginCell(int index_x, int index_y) const {
    // return distance from origin
    // index = {index_x, index_y}

    // get cell coordinates
    double x = GRID[index_x][index_y].center_coo[0];
    double y = GRID[index_x][index_y].center_coo[1];

    // get distance from origin
    return std::sqrt(x*x + y*y);
}

double lightmap::distanceOriginCell(std::array<double,3> cellCoo) const {
    // return distance from origin
    // cellCoo = {x,y,z}

    // get cell coordinates
    double x = cellCoo[0];
    double y = cellCoo[1];

    // get distance from origin
    return std::sqrt(x*x + y*y);
}

double lightmap::distanceOriginCell(const cell& c) const {
    // return distance from origin
    // c = cell

    // get cell coordinates
    double x = c.center_coo[0];
    double y = c.center_coo[1];

    // get distance from origin
    return std::sqrt(x*x + y*y);
}





double lightmap::distancePointCell(int index_x, int index_y, std::array<double,3> point) const {
    // return distance from point
    // index = {index_x, index_y}
    // point = {x,y,z}

    // get cell coordinates
    double x = GRID[index_x][index_y].center_coo[0];
    double y = GRID[index_x][index_y].center_coo[1];

    // get distance from point
    return std::sqrt((x-point[0])*(x-point[0]) + (y-point[1])*(y-point[1]));
}

double lightmap::distancePointCell(std::array<double,3> cellCoo, std::array<double,3> point) const {
    // return distance from point
    // cellCoo = {x,y,z}
    // point = {x,y,z}

    // get cell coordinates
    double x = cellCoo[0];
    double y = cellCoo[1];

    // get distance from point
    return std::sqrt((x-point[0])*(x-point[0]) + (y-point[1])*(y-point[1]));
}

double lightmap::distancePointCell(const cell& c, std::array<double,3> point) const {
    // return distance from point
    // c = cell
    // point = {x,y,z}

    // get cell coordinates
    double x = c.center_coo[0];
    double y = c.center_coo[1];

    // get distance from point
    return std::sqrt((x-point[0])*(x-point[0]) + (y-point[1])*(y-point[1]));
}





double lightmap::distanceSourceCell(int index_x, int index_y, const lightsource& source) const {
    // return distance from source
    // index = {index_x, index_y}
    // source = lightsource

    // get cell coordinates
    double x = GRID[index_x][index_y].center_coo[0];
    double y = GRID[index_x][index_y].center_coo[1];

    // get distance from source
    return std::sqrt((x-source.coo[0])*(x-source.coo[0]) + (y-source.coo[1])*(y-source.coo[1]));
}

double lightmap::distanceSourceCell(std::array<double,3> cellCoo, const lightsource& source) const {
    // return distance from source
    // cellCoo = {x,y,z}
    // source = lightsource

    // get cell coordinates
    double x = cellCoo[0];
    double y = cellCoo[1];

    // get distance from source
    return std::sqrt((x-source.coo[0])*(x-source.coo[0]) + (y-source.coo[1])*(y-source.coo[1]));
}

double lightmap::distanceSourceCell(const cell& c, const lightsource& source) const {
    // return distance from source
    // c = cell
    // source = lightsource

    // get cell coordinates
    double x = c.center_coo[0];
    double y = c.center_coo[1];

    // get distance from source
    return std::sqrt((x-source.coo[0])*(x-source.coo[0]) + (y-source.coo[1])*(y-source.coo[1]));
}


double lightmap::distanceSourcePoint(const lightsource& source, std::array<double,3> pointCoo) const {
    // return distance from source
    // source = lightsource
    // pointCoo = {x,y,z}

    // get source coordinates
    double x = source.coo[0];
    double y = source.coo[1];
    double z = source.coo[2];

    // get distance from point
    return std::sqrt((x-pointCoo[0])*(x-pointCoo[0]) + (y-pointCoo[1])*(y-pointCoo[1]) +(z-pointCoo[2])*(z-pointCoo[2]) );
}



double lightmap::dotProduct(std::array<double,3> v1, std::array<double,3> v2) {
    // return dot product of two vectors
    // v1 = {x,y,z}
    // v2 = {x,y,z}

    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}







// power methods







double lightmap::irradiance(std::array<double,3> pointCoo) {
    // return irradiance at point
    // pointCoo = {x,y,z}
    
/*I'll be right back*/

    // get irradiance
    double irradiance = 0;
    std::array<double,3> displacement;
    
    for (int i = 0; i < SOURCES.size(); i++) {
        double r = distanceSourcePoint(SOURCES[i],pointCoo);
        displacement = {(SOURCES[i].coo[0]-pointCoo[0])/r, (SOURCES[i].coo[1]-pointCoo[1])/r, (SOURCES[i].coo[2]-pointCoo[2])/r};
        irradiance += SOURCES[i].power / (4*M_PI*distanceSourcePoint(SOURCES[i],pointCoo)*distanceSourcePoint(SOURCES[i], pointCoo))*dotProduct(displacement,NORMALvector);
    }
    return irradiance;
}

double lightmap::CellPower(cell& c) {    // calculate the power of cell based on irradiance (W)
    double I = irradiance(c.center_coo);
    double A = c.area;
    return I*A;
}

void lightmap::updateCellPower() {
    // update power of all cells
    for (int i = 0; i < nCELL[0]; i++) {
        for (int j = 0; j < nCELL[1]; j++) {
            GRID[i][j].power = CellPower(GRID[i][j]);
        }
    }
}

void lightmap::updateUnitaryCellPower(cell& c) {
    // update power of cell
    c.power = CellPower(c);
}







// flux methods







double lightmap::medianPower()  {
    // return median power of all cells
    std::vector<double> vPOWER;
    for (int i = 0; i < nCELL[0]; i++) {
        for (int j = 0; j < nCELL[1]; j++) {
            vPOWER.push_back(GRID[i][j].power);
        }
    }
    std::sort(vPOWER.begin(), vPOWER.end());
    return vPOWER[vPOWER.size()/2];
    // edge case de vPower ser de tamanho par ???
}

double lightmap::meanPower() {
    // return mean power of all cells
    double mean = 0;
    for (int i = 0; i < nCELL[0]; i++) {
        for (int j = 0; j < nCELL[1]; j++) {
            mean += GRID[i][j].power;
        }
    }
    return mean / (nCELL[0]*nCELL[1]);
}

double lightmap::maxPower() {
    // return max power of all cells
    double max = 0;
    for (int i = 0; i < nCELL[0]; i++) {
        for (int j = 0; j < nCELL[1]; j++) {
            if (GRID[i][j].power > max) {
                max = GRID[i][j].power;
            }
        }
    }
    return max;
    // posso tambem usar o vGRIDsort() e ir buscar o primeiro elemento
}

double lightmap::minPower() {
    // return min power of all cells
    double min = 0;
    for (int i = 0; i < nCELL[0]; i++) {
        for (int j = 0; j < nCELL[1]; j++) {
            if (GRID[i][j].power < min) {
                min = GRID[i][j].power;
            }
        }
    }
    return min;
    // posso tambem usar o vGRIDsort() e ir buscar o ultimo elemento
}

double lightmap::maxovermeanPower() {
    // return max over mean power of all cells
    return maxPower() / meanPower();
}

double lightmap::maxovermedianPower() {
    // return max over median power of all cells
    return maxPower() / medianPower();
}



// grid methods

std::vector<cell> lightmap::vGRID() {
    // return vector of cells
    std::vector<cell> vGRID;
    for (int i = 0; i < nCELL[0]; i++) {
        for (int j = 0; j < nCELL[1]; j++) {
            vGRID.push_back(GRID[i][j]);
        }
    }
    return vGRID;
}

std::vector<cell>& lightmap::vGRIDsort() {
    // sort grid by power
    std::vector<cell> vGRID;
    for (int i = 0; i < nCELL[0]; i++) {
        for (int j = 0; j < nCELL[1]; j++) {
            vGRID.push_back(GRID[i][j]);
        }
    }
    std::sort(vGRID.begin(), vGRID.end(), [](const cell& c1, const cell& c2) {return c1.power > c2.power;});
    return vGRID;
 }

