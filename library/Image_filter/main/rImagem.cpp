#include<iostream>
#include<fstream>
#include<cmath>
#include<algorithm>
#include<cstdlib>




#include<vector>
#include<string>
#include<sstream>

#define BREAK cout << "**************************************************" <<endl

using namespace std;
using mtr = vector<vector<int>>;	// stores an image matrix
using mtrw = vector<vector<double>>;	// strores a weight matrix
using cood = pair<unsigned int, unsigned int>;


bool valid_index(const mtr& M, int y, int x)
{
	return (y < M.size()) && (y >= 0) && (x < M[y].size()) && (x >= 0);
}

mtr ReadImage(string filename, int* wm = nullptr)		// creates an image matrix from an .pgm file
{
	ifstream FI(filename);
	string line;
	getline(FI, line);		// 1st line

	if (line != "P2") {		// has to be a .pgm file (P2)
		cerr << "Unknown file type" << endl;
		return mtr();
	}
	
	getline(FI, line);		// 2nd line 
	istringstream iss(line);	// meta data is retrieved line by line to avoid corrupted files
	int ncols, nrows;
	iss >> ncols >> nrows;
	int max_white;
	FI >> max_white;
	mtr M(nrows, vector<int>(ncols));
	for(auto& c : M){		// fill matrix
		for(auto& e : c){
			FI >> e;
		}
	}

	if(wm != nullptr)
		*wm = max_white;
	return M;
}

int write_image(int max_white, const mtr& M, string filename)	// writes .pgm file
{
	int nrows = M.size(), ncols = M[0].size();
	ofstream FO(filename);
	FO << "P2" << endl;			// write meta data
	FO << ncols << " " << nrows << endl;
	FO << max_white << endl;
	for(const auto& c : M){			// fill file with matrix
		for(const auto& e : c){
			FO << e <<" ";
		}
		FO << endl;
	}
	return 0;
}

vector<int> ColourFreq(int white_max, const mtr& M){		// makes histogram of colors in matrix
	vector<int> v(white_max+1,0);				// +1 beacuse [0,whitemax]
	for(auto& c : M){
		for(auto& e : c){
			v[e]++;					// add one to the e channel
		}
	}
	return v;
}

double mean(const mtr& M)			// calculate the matrix mean
{
	unsigned int size = M.size()*M[0].size();
	double total=0;
	for(const auto& c : M){
		for(const auto& e : c){
			total += e;
		}
	}
	return total/size;
}

double variance(const mtr& M)			// calculate the matrix variance
{
	unsigned int size = M.size()*M[0].size();
	double m = mean(M);
	double s=0, tmp;
	for(const auto& c : M){
		for(const auto& e : c){
			tmp = e-m;
			tmp *= tmp;
			s += tmp;
		}
	}
	return s/(size-1);
}

mtr invert(int max_white, const mtr& M){	// create inverted matrix
	mtr M2(M);
	for(auto& c : M2){
		for(auto& e : c){
			e = max_white-e;
		}
	}
	return M2;
}

mtr filter(const mtr& M, const mtrw& W){	// applies a mask to the matrix
	mtr M2(M.size(), vector<int>(M[0].size()));
	for (int i = 0; i < M.size(); ++i) {
		for (int j = 0; j < M[i].size(); ++j) {
			double weight = 0;
			double sum = 0;
			for (int k = -1; k <= 1; ++k) {
				for (int l = -1; l <= 1; ++l) {
					if(valid_index(M, i+k, j+l)){
						sum += W[1+k][1+l]*M[i+k][j+l];
						weight += W[1+k][1+l];
					}
				}
			}
			if(weight != 0)
				M2[i][j] = round(sum/weight);	// normalizes the corners to total weight used in caculations
		}
	}
	return M2;
}

mtr median_filter(const mtr& M, vector<cood> mask)
{
	mtr M2(M.size(), vector<int>(M[0].size()));
	vector<int> v(mask.size());
	int count;
	for (int i = 0; i < M.size(); ++i) {
		for (int j = 0; j < M[i].size(); ++j) {
			count = 0;
			for(auto m : mask){
				if(valid_index(M, i+m.first, j+m.second)){
					v[count++] = M[i+m.first][j+m.second];
				}
			}
			sort(v.begin(), v.begin()+count);
			if(count % 2 == 0)
				M2[i][j] = (v[count/2 -1]+v[count/2])/2;
			else
				M2[i][j] = v[count/2];
		}
	}
	return M2;
}

int main(int argc, char *argv[])
{
	// Leitura de imagem.pgm
	int white_max;
	mtr M = ReadImage(argv[1], &white_max);
	cout << "Média original: " << mean(M) << endl;
	cout << "desvio padrão original: " << sqrt(variance(M)) << endl;

	// Calculo das frequências de cada cor (histograma)
	BREAK;
	vector<int> v = ColourFreq(255, M);
	cout << "Frequência das cores:" << endl;
	for(auto e: v){
		cout << e << " ";
	}
	cout << endl;

	BREAK;

	// Frequência relativa das cores
	vector<double> vr(v.size());
	cout << "Frequência relativas das cores" << endl;
	for(int i=0; i<v.size(); i++){
		vr[i] = 100.*(double)v[i]/M.size()/M[0].size();
	}
	for(auto e: vr){
		cout << e << " ";
	}
	cout << endl;

	BREAK;

	// Determinação das cores mais frequentes
	vector<int> freq_mais{0,1,2};
	sort(freq_mais.begin(), freq_mais.end(), [&v](int x1, int x2){return v[x1] > v[x2];});
	for(int i=3; i<v.size(); i++){
		if(v[i]>v[freq_mais[2]]){
			freq_mais[2] = i;
			sort(freq_mais.begin(), freq_mais.end(), [&v](int x1, int x2){return v[x1] > v[x2];});
		}
	}
	for(auto e: freq_mais){
		cout << "Cor:" << e << "\t" << v[e] <<"\t" <<(double)v[e]/M.size()/M[0].size() ;
		cout << endl;
	}
	
	BREAK;

	// Inversão da imagem
	mtr M2 = invert(white_max, M);
	write_image(white_max, M2, "peixe_noise10_inverted.ascii.pgm");

	// Matriz peso para reduced_noise
	mtrw W1{{1./8., 1./8., 1./8.}, {1./8., 0, 1./8.}, {1./8., 1./8., 1./8.}};

	// Escrita de reduced_noise
	mtr M3 = filter(M, W1);
	cout << "Média após redução de ruído: " << mean(M3) << endl;
	cout << "Desvio padrão após redução de ruído: " << sqrt(variance(M3)) << endl;
	write_image(white_max, M3, "peixe_reduced_noise.ascii.pgm");

	BREAK;
	// Matriz peso para box_blur
	mtrw W2{{1/9., 1/9.,1/9.},{1/9., 1/9.,1/9.},{1/9., 1/9.,1/9.}};
	
	// Escrita de box_blur
	mtr M4 = filter(M, W2);
	cout << "Média após box filtering: " << mean(M4) << endl;
	cout << "Desvio padrão após box filtering: " << sqrt(variance(M4)) << endl;
	write_image(white_max, M4, "peixe_box_blur.ascii.pgm");
	BREAK;

	// Mediana quadrado
	cout << "quadrado2"<<endl;
	vector<cood> mask1;
	for (int i = -2; i <= 2; ++i) {
		for (int j = -2; j <= 2; ++j) {
			mask1.push_back({i,j});
		}
	}
	mtr M5 = median_filter(M, mask1);
	write_image(white_max, M5, "peixe_filtro_mediana_quadrado.ascii.pgm");
	cout << "Média quadrado: " << mean(M5) << endl;
	cout << "Desvio padrão quadrado: " << sqrt(variance(M5)) << endl;
	BREAK;

	// Mediana diamante
	cout << "diamond2" << endl;
	vector<cood> mask2;
	for (int i = -2; i <= 2; ++i) {
		for (int j = abs(i)-2; j <= 2-abs(i); ++j) {
			mask2.push_back({i,j});
		}
	}
	mtr M6 = median_filter(M, mask2);
	write_image(white_max, M6, "peixe_filtro_mediana_diamante.ascii.pgm");
	cout << "Média diamante: " << mean(M6) << endl;
	cout << "Desvio padrão diamante: " << sqrt(variance(M6)) << endl;
	BREAK;

	// Mediana quadrado com r=3
	cout << "quadrado3"<<endl;
	vector<cood> mask3;
	for (int i = -3; i <= 3; ++i) {
		for (int j = -3; j <= 3; ++j) {
			mask3.push_back({i,j});
		}
	}
	mtr M7 = median_filter(M, mask3);
	write_image(white_max, M7, "square_median_filter3.pgm");
	cout << "Média quadrado (r=3): " << mean(M7) << endl;
	cout << "Desvio padrão quadrado (r=3): " << sqrt(variance(M7)) << endl;
	BREAK;

	// Mediana diamante com r=3
	cout << "diamond3" << endl;
	vector<cood> mask4;
	for (int i = -3; i <= 3; ++i) {
		for (int j = abs(i)-3; j <= 3-abs(i); ++j) {
			mask4.push_back({i,j});
		}
	}
	mtr M8 = median_filter(M, mask4);
	write_image(white_max, M8, "diamond_median_filter3.pgm");
	cout << "Média diamante: " << mean(M8) << endl;
	cout << "Desvio padrão diamante: " << sqrt(variance(M8)) << endl;
	BREAK;
}

