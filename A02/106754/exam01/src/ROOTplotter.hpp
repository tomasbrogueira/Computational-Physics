# ifndef __ROOTPLOTTER__
# define __ROOTPLOTTER__

# include <vector>
# include <string>
# include <functional>
# include "TCanvas.h"
# include "TGraph.h"
# include "TAxis.h"
# include "TH1F.h"
# include "TH2F.h"
# include "TStyle.h"

# include "ODEpoint.hpp"
# include "ODEsolver.hpp"

const int XDIM = 1000; // Canvas dimensions
const int YDIM = 1000;

class ROOTplotter {
    public:
        ROOTplotter() = default;
        ~ROOTplotter() = default;

        static TCanvas* PlotMultipleGraphs(std::vector<std::vector<double>> X_values, std::vector<std::vector<double>> Y_values, 
            std::vector<std::vector<std::string>> labels, bool side_by_side = true); // Divides canvas
        // static TCanvas* PlotMultipleGraphsSamePad(std::vector<std::vector<double>> X_values, std::vector<std::vector<double>> Y_values, 
            // std::vector<std::vector<std::string>> labels); // Doesnt divide canvas
        static TCanvas* PlotFunction(std::function<double(double)> f, double x_min, double x_max, std::vector<std::string> labels, double dt = 0.01);

        static TCanvas* Plot1DHistogram(std::vector<double> X_values, std::vector<double> Y_values, std::vector<std::string> labels);
        static TCanvas* Plot2DHistogram(std::vector<std::vector<double>>, std::vector<std::string> labels, EColorPalette colour_palette = kBird);
        static TCanvas* Plot2DHistogram(std::vector<std::vector<double>>, std::vector<std::string> labels, double x0, double x1, 
            double y0, double y1, EColorPalette colour_palette = kBird); // Only accepts positive x and y values!

};

# endif