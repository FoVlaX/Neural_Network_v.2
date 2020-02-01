#include <iostream>
#include "matrix.h"
#include "NN.h"
#include <algorithm>
#include <Magick++.h>
#include "MNIST.h"
using namespace std; 
using namespace Magick; //���������� ��� ������ � �������������� �  ������ ������� �� ���������� ��� ���� � imageMagicCode.txt � ����� image

	double RandFunc() { //������� ��������� �������� ���������, ����� ���� �������� � ����� matrix ��� ��������� �������� � �������
		return double(rand() % 2456)/2457.0; 
	}




int main(int argc, char** argv) {

	
	vector<matrix<double>> train; //������ ��� �������� ������������� �������
	ReadMNIST("image/t10k-images.idx3-ubyte", 10000, 784, train); //������ �������������� ������� � ������ �� �����

	vector<uint8_t> labels = read_mnist_label_file("image/t10k-labels.idx1-ubyte"); //������ ����� �.�. ��� ����� ����� ��-�������

	
	//NN network(1,100,784,10); //�������� ��������� � ���� ���� � 100 ��������� � ������� �������� �������� 784 � �������� 10
	NN network("test.txt"); //�������� ��������� � �������� �� ���������� �� ������ �.�. ������� ��-��� ���-� ������ ������� ���-�� �������� � ���� � ��� ���� � ����������

	vector<matrix<double>> a(10); //������ ��� �������� ��������� �������� ������
	for (int i = 0; i < 10; i++) {
		a[i].change(10, 1); //�������� ������ ������� �� (10, 1)
		a[i][i][0] = 1; // ������������� 1 � �������������� ��������������� ����� �������
	}

	const int count = 0; // ���-�� �������� � ������� ������ 0 �.�. ���� ������� � �������� � ����� test.txt
	for (int i = 0; i < count; i++){
		network.teach(train[i], a[(int)labels[i]]); //�������� ����������� � ������� i ��� ��������� � ��������������� labels[i] ��������� ���������
		if (i % 300 == 0) {
			system("cls");
			cout << (double(i) / count * 100);//����� �������� ������������ ������
		}
	}
	cout.precision(3);
	int stat = 0; //����� ������� ������ �������
	for (int i = 0; i < 10000; i++) {
		if (network.feedfoward(train[i]).ans.MaxIndex().first == (int)labels[i]) { //���� ����� ��������� ���������� � ��������� ��������� MaxIndex().first ������ ������ ������������� �������� � ������� �.�. ������������ ����������� ��� ���� ������ � ���� ������ �����
			stat++;//���������� � ����� ������ �������
		}
		if (i % 300 == 0) {
			system("cls");
			cout << (double(i) / 100);
		}
	}
	cout <<endl<< double(stat) / 100; //����� �������� ������ �������
	//network.save("test.txt");
	return 0;
}
