#include <iostream>
#include "matrix.h"
#include "NN.h"
#include <algorithm>
#include <Magick++.h>
using namespace std;
using namespace Magick;
double RandFunc() {
	return double(rand() % 2456)/2457.0;
}

int main(int argc, char** argv) {
	InitializeMagick(*argv);
	Image image;
	vector<matrix<double>> digits(11);
	Quantum* pixels;
	for (int i = 0; i < 11; i++) {
		string str = to_string(i) + ".png";
		image.read(str);

		int w = image.columns();
		int h = image.rows();

		digits[i].change(w * h, 1);

		pixels = image.getPixels(0, 0, w, h);

		// now you can access single pixels like a vector
		for (int row = 0; row < h; row++) {
			for (int column = 0; column < w; column++) {
				digits[i][w*row+column][0] = double(65535 - pixels[w * row + column])/65535.0;
			}
		}
	}
	
	//NN network(1,1000,6400,10);
	NN network("test.txt");
	matrix<double> a0(vector<vector<double>> { {1.0}, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0}, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 } });
	matrix<double> a1(vector<vector<double>>{ {0.0}, { 1.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 } });
	matrix<double> a2(vector<vector<double>>{ {0.0}, { 0.0 }, { 1.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 } });
	matrix<double> a3(vector<vector<double>>{ {0.0}, { 0.0 }, { 0.0 }, { 1.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 } });
	matrix<double> a4(vector<vector<double>>{ {0.0}, { 0.0 }, { 0.0 }, { 0.0 }, { 1.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 } });
	matrix<double> a5(vector<vector<double>>{ {0.0}, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 1.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 } });
	matrix<double> a6(vector<vector<double>>{ {0.0}, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 1.0 }, { 0.0 }, { 0.0 }, { 0.0 } });
	matrix<double> a7(vector<vector<double>>{ {0.0}, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 1.0 }, { 0.0 }, { 0.0 } });
	matrix<double> a8(vector<vector<double>>{ {0.0}, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 1.0 }, { 0.0 } });
	matrix<double> a9(vector<vector<double>>{ {0.0}, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 0.0 }, { 1.0 } });
	const int count = 300;
	/*for (int i = 0; i < count; i++){
		network.teach(digits[0], a0);
		network.teach(digits[1], a1);
		network.teach(digits[2], a2);
		network.teach(digits[3], a3);
		network.teach(digits[4], a4);
		network.teach(digits[5], a5);
		network.teach(digits[6], a6);
		network.teach(digits[7], a7);
		network.teach(digits[8], a8);
		network.teach(digits[9], a9);
		if (i % 30) {
			system("cls");
			cout << (double(i) / count * 100);
		}
	}*/
	cout.precision(3);
	cout <<endl<< fixed << network.feedfoward(digits[0]).ans << endl;
	cout << network.feedfoward(digits[1]).ans<< endl;
	cout << network.feedfoward(digits[4]).ans.MaxIndex().first << endl;
	network.save("test.txt");
	
	return 0;
}
