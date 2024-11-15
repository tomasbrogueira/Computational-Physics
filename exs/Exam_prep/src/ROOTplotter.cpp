# include "ROOTplotter.hpp"
using namespace std;

TCanvas* ROOTplotter::PlotMultipleGraphs(vector<vector<double>> X_values, vector<vector<double>> Y_values, vector<vector<string>> labels, bool side_by_side){
    // Labels has the form Title, Xlabel, Ylabel
    string PLOTSTYLE = "AC"; // Could be APL, AC, AL, etc.
    int n = X_values.size();

    // Create canvas
    TCanvas* C = new TCanvas("C", "C", XDIM, YDIM);
    side_by_side ? C->Divide(n, 1) : C->Divide(1, n);

    // Create graphs
    vector<TGraph*> graphs;
    for (int i = 0; i < n; ++i) {
        graphs.push_back(new TGraph(X_values[i].size(), X_values[i].data(), Y_values[i].data()));
    }

    // Plot graphs
    for (int i = 0; i < n; ++i) {
        C->cd(i+1);
        graphs[i]->Draw(PLOTSTYLE.c_str());
        graphs[i]->SetTitle(labels[i][0].c_str());
        graphs[i]->GetXaxis()->SetTitle(labels[i][1].c_str());
        graphs[i]->GetYaxis()->SetTitle(labels[i][2].c_str());
    }

    return C;
}

TCanvas* ROOTplotter::PlotFunction(function<double(double)> f, double x_min, double x_max, vector<string> labels, double dt){
    // Labels has the form Title, Xlabel, Ylabel
    string PLOTSTYLE = "AC"; // Could be APL, AC, AL, etc.

    // Create canvas
    TCanvas* C = new TCanvas("C", "C", XDIM, YDIM);

    // Create graph
    TGraph* g = new TGraph;
    for (double x = x_min; x <= x_max; x += dt) {
        g->AddPoint(x, f(x));
    }

    // Plot graphs
    g->Draw(PLOTSTYLE.c_str());
    g->SetTitle(labels[0].c_str());
    g->GetXaxis()->SetTitle(labels[1].c_str());
    g->GetYaxis()->SetTitle(labels[2].c_str());

    return C;
}

TCanvas* ROOTplotter::Plot1DHistogram(vector<double> X_values, vector<double> Y_values, vector<string> labels){
    // Labels has the form Title, Xlabel, Ylabel
    string PLOTSTYLE = "AC"; // Could be APL, AC, AL, etc.

    // Create canvas
    TCanvas* C = new TCanvas("C", "C", XDIM, YDIM);

    // Create histogram
    TH1F* h = new TH1F("h", "h", X_values.size(), X_values[0], X_values[X_values.size()-1]);

    // Fill histogram
    for (int i = 0; i < X_values.size(); ++i) {
        h->Fill(X_values[i], Y_values[i]);
    }

    // Plot histogram
    h->Draw(PLOTSTYLE.c_str());
    h->SetTitle(labels[0].c_str());
    h->GetXaxis()->SetTitle(labels[1].c_str());
    h->GetYaxis()->SetTitle(labels[2].c_str());

    return C;
}

TCanvas* ROOTplotter::Plot2DHistogram(vector<vector<double>> Z_values, vector<string> labels, EColorPalette colour_palette){
    // Labels has the form Title, Xlabel, Ylabel, Zlabel
    string PLOTSTYLE = "COLZ"; // Add colour palette

    // Create canvas
    TCanvas* C = new TCanvas("C", "C", XDIM, YDIM);

    // Create histogram
    TH2F* h = new TH2F(labels[3].c_str(), labels[3].c_str(), Z_values.size(), 0, Z_values.size(), Z_values[0].size(), 0, Z_values[0].size());

    int nx = Z_values.size() - 1;
    int ny = Z_values[0].size() - 1;

    // Fill histogram
    for (int i = 0; i < Z_values.size(); ++i) {
        for (int j = 0; j < Z_values[i].size(); ++j) {
            h->Fill(j, ny - i, Z_values[i][j]);
        }
    }

    // Plot histogram
    h->Draw(PLOTSTYLE.c_str());
    h->SetTitle(labels[0].c_str());
    h->GetXaxis()->SetTitle(labels[1].c_str());
    h->GetYaxis()->SetTitle(labels[2].c_str());
    gStyle->SetPalette(colour_palette);

    return C;
}

TCanvas* ROOTplotter::Plot2DHistogram(vector<vector<double>> Z_values, vector<string> labels, double x0, double x1, double y0, double y1, EColorPalette colour_palette){
    // Labels has the form Title, Xlabel, Ylabel, Zlabel
    string PLOTSTYLE = "COLZ"; // Add colour palette

    // Create canvas
    TCanvas* C = new TCanvas("C", "C", XDIM, YDIM);

    // Create histogram
    TH2F* h = new TH2F(labels[3].c_str(), labels[3].c_str(), Z_values.size(), x0, x1, Z_values[0].size(), y0, y1);

    int nx = Z_values.size() - 1;
    int ny = Z_values[0].size() - 1;
    int dx = (x1 - x0) / nx;
    int dy = (y1 - y0) / ny;

    // Fill histogram
    for (int i = 0; i < Z_values.size(); ++i) {
        for (int j = 0; j < Z_values[i].size(); ++j) {
            h->Fill(j * dx, (ny - i) * dy, Z_values[i][j]);
        }
    }

    // Plot histogram
    h->Draw(PLOTSTYLE.c_str());
    h->SetTitle(labels[0].c_str());
    h->GetXaxis()->SetTitle(labels[1].c_str());
    h->GetYaxis()->SetTitle(labels[2].c_str());
    gStyle->SetPalette(colour_palette);

    return C;
}