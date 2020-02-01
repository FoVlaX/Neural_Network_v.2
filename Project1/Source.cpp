#include <iostream>
#include "matrix.h"
#include "NN.h"
#include <algorithm>
#include <Magick++.h>
#include "MNIST.h"
using namespace std; 
using namespace Magick; //библиотека для работы с изоббражениями в  данном примере не используюю код есть в imageMagicCode.txt в папке image

	double RandFunc() { //функция получения значений случайных, может быть передана в класс matrix для генерации значений в матрице
		return double(rand() % 2456)/2457.0; 
	}




int main(int argc, char** argv) {

	
	vector<matrix<double>> train; //вектор для хранения тренировочной выборки
	ReadMNIST("image/t10k-images.idx3-ubyte", 10000, 784, train); //чтение тренирововчной выборки в вектор из файла

	vector<uint8_t> labels = read_mnist_label_file("image/t10k-labels.idx1-ubyte"); //чтение меток т.е. где какая цифра по-порядку

	
	//NN network(1,100,784,10); //создание нейросети в один слой с 100 нейронами с входным вектором размером 784 и выходным 10
	NN network("test.txt"); //создание нейросети и загрузка ее параметров из файлов т.е. размера вх-ных вых-х данный глубина кол-во нейронов в слое и все веса и дополнения

	vector<matrix<double>> a(10); //вектор для хранения эталонных выходный данных
	for (int i = 0; i < 10; i++) {
		a[i].change(10, 1); //изменяем размер матрицы на (10, 1)
		a[i][i][0] = 1; // устанавляваем 1 в соответсвующей предсказываемой цифры позиции
	}

	const int count = 0; // кол-во картинок в выборке сейчас 0 т.к. сеть обучена и хранится в файле test.txt
	for (int i = 0; i < count; i++){
		network.teach(train[i], a[(int)labels[i]]); //обратное прохождение с текущей i той картинкой и соответствующим labels[i] эталонным значением
		if (i % 300 == 0) {
			system("cls");
			cout << (double(i) / count * 100);//вывод процента обработанных данных
		}
	}
	cout.precision(3);
	int stat = 0; //далее подсчет верных ответов
	for (int i = 0; i < 10000; i++) {
		if (network.feedfoward(train[i]).ans.MaxIndex().first == (int)labels[i]) { //если ответ нейросети совпадаает с эталонным значением MaxIndex().first выдает индекс максимального элемента в матрице т.е. максимальную вероятность что этот индекс и есть нужная цифра
			stat++;//прибавляем к колву верных решений
		}
		if (i % 300 == 0) {
			system("cls");
			cout << (double(i) / 100);
		}
	}
	cout <<endl<< double(stat) / 100; //вывод процента верных решений
	//network.save("test.txt");
	return 0;
}
