#pragma once
#include "matrix.h"
#include <math.h>
#include <fstream>
struct answer { //������ ������ ������������ �������� ������� ����������� feedforward
	matrix<double> ans; //�������� �� ������ 
	vector<matrix<double>> f; //������ �������� �������� �������� ����
	vector<matrix<double>> h; //������ �������� �������� �������� �� ������������� ������� ���������
};

class NN
{
public:
	NN(int n, int m, int In, int Out); //����������� ��� n - �������(���-�� �����), m - ���-�� �������� � ����, In - ������ ������� ������, Out - ������ �������� ������
	NN(string str) { //�������� ���������� � ������ ��������� �� ����� 
		load(str);
	}
	matrix<double> Afun(matrix<double> a); //������� ���������� ��� ������� � �����
	matrix<double> d_Afun(matrix<double> a);//����������� ������� ��������� ��� ������� � �����
	answer feedfoward(matrix<double> a); //������ ����������� �� ����
	void teach(matrix<double> In, matrix<double> Out); //�������� ����������� (����� ������������ ������ ����������) In ������� ������ Out ��������� �������� ������
	void save(string str); //���������� ���������� ��������� � ����
	void load(string str); //�������� ���������� ��������� �� �����
private:
	int deep;  //�������
	int width; //������ ���-�� �������� � ���� ������ �� �������� �� ��� ����� ����� ������ ���
	vector<matrix<double>> W; //������ �������� �������� ����� ���������
	vector<matrix<double>> b; //������ �������� �������� ���������� ���������
	double Afun_e(double a); //������� ���������� ��� ��������
	double d_Afun_e(double a);//����������� ������� ��������� ��� ���������
};

