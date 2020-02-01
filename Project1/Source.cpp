#include <iostream>
#include "matrix.h"
#include "NN.h"
#include <algorithm>
#include <Magick++.h>
#include "MNIST.h"
using namespace std;
using namespace Magick;

	double RandFunc() {
		return double(rand() % 2456)/2457.0;
	}




int main(int argc, char** argv) {
	InitializeMagick(*argv);
	Image image;
	
	vector<matrix<double>> train;
	ReadMNIST("image/train-images.idx3-ubyte", 60000, 784, train);

	vector<uint8_t> labels = read_mnist_label_file("image/train-labels.idx1-ubyte");

	
	//NN network(1,100,784,10);
	NN network("test.txt");

	vector<matrix<double>> a(10);
	for (int i = 0; i < 10; i++) {
		a[i].change(10, 1);
		a[i][i][0] = 1;
	}

	const int count = 0;
	for (int i = 0; i < count; i++){
		network.teach(train[i], a[(int)labels[i]]);
		if (i % 30) {
			system("cls");
			cout << (double(i) / count * 100);
		}
	}
	cout.precision(3);
	cout <<endl<< fixed << network.feedfoward(train[4]).ans << endl << (int)labels[4];
	network.save("test.txt");
	return 0;
}
