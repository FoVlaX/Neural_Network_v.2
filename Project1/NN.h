#pragma once
#include "matrix.h"
#include <math.h>
#include <fstream>
struct answer { //формат данных возвращаемых функцией прфмого прохождения feedforward
	matrix<double> ans; //значение на выходе 
	vector<matrix<double>> f; //вектор хранящий значения нейронов сети
	vector<matrix<double>> h; //вектор хранящий значения нейронов ДО использования функции активации
};

class NN
{
public:
	NN(int n, int m, int In, int Out); //констурктор где n - глубина(кол-во слоев), m - кол-во нейронов в слое, In - размер входных данных, Out - размер выходных данных
	NN(string str) { //загрузка параметров и данных нейросети из файла 
		load(str);
	}
	matrix<double> Afun(matrix<double> a); //функция активанции для матрицы в целом
	matrix<double> d_Afun(matrix<double> a);//производная функции активации для матрицы в целом
	answer feedfoward(matrix<double> a); //прямое прохождение по сети
	void teach(matrix<double> In, matrix<double> Out); //обратное прохождение (метод градиентного спуска реализован) In входные данные Out эталонное значение ответа
	void save(string str); //сохранение параметров нейросети в файл
	void load(string str); //загрузка параметров нейросети из файла
private:
	int deep;  //глубина
	int width; //ширина кол-во нейронов в слое посути не исползую ни где пусть будет просто так
	vector<matrix<double>> W; //вектор хранящий значение весов нейросети
	vector<matrix<double>> b; //вектор хранящий значение дополнений нейросети
	double Afun_e(double a); //функция активанции для элемента
	double d_Afun_e(double a);//производная функции активации для эелемента
};

