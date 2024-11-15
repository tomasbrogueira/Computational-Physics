#include "lightmap.hpp"
#include <iostream>
#include "TCanvas.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TColor.h"


int main() {
  std::array<int,2> nCells = {20,20};
  std::array<double,2> cellSize = {0.1,0.1};
  std::array<double,3> origin = {0,0,0};

  lightmap mp(nCells, cellSize, origin);
  lightsource ls1; ls1.coo = std::array<double, 3>{-0.5,-0.5,1}; ls1.power = 100;
  lightsource ls2; ls2.coo = std::array<double, 3>{0.5,0.5,1}; ls2.power = 100;
  mp.AddLightSource(ls1);
  mp.AddLightSource(ls2);
  mp.updateCellPower();

  std::vector<cell> cells = mp.vGRID();

  // Create histogram
  double x0 = origin[0]-nCells[0]/2*cellSize[0];
  double y0 = origin[1]-nCells[1]/2*cellSize[1];
  double x1 = origin[0]+nCells[0]/2*cellSize[0];
  double y1 = origin[1]+nCells[1]/2*cellSize[1];

  TH2F hist("hist", "Mapa de luz", nCells[0], x0, x1, nCells[1], y0, y1);

  for (cell c : cells) {
    hist.Fill(c.center_coo[0], c.center_coo[1], c.power);
  } 

  // Create canvas
  TCanvas c1("c1", "Mapa de luz", 800, 600);

  hist.Draw("colz");

  c1.SaveAs("mapa.png");

  return 0;
}
