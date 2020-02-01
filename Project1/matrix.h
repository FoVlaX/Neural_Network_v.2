#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
template <class T>
class matrix : public vector<vector<T>> //класс матриц, предназначенный для хранения входных выходных векторов, промежуточный значений нейрнов, значений весов и дополнений
{//унаследуем класс vector<vector<T>> 
	public:
		matrix() : vector<vector<T>>() { //Пустой конструктор
		}

		matrix(vector<vector<T>> a) : vector<vector<T>>() { //констурктор в который можно передать значения из вектора или в формате {{..},{..},{..},{..},{..}}
			(*this).resize(a.size());
			for (int i = 0; i < a.size(); i++) {
				(*this)[i].resize(a[i].size());
				for (int j = 0; j < a[i].size(); j++) {
					(*this)[i][j] = a[i][j];
				}
			}
		}

		matrix(int a, int b) : vector<vector<T>>() { //констуктор задает матрице фиксированный размер и нулевые значения
			(*this).resize(a);
			for (int i = 0; i < a; i++) {
				(*this)[i].resize(b,0);
			}
		}

		matrix(int a, int b, T(*f)()) : vector<vector<T>>() {//констуктор задает матрице фиксированный размер и значения генерируемы передаваемой функцией (*f)()
			(*this).resize(a);
			for (int i = 0; i < a; i++) {
				(*this)[i].resize(b, 0);
			}
			RandFunc = f;
			for (int i = 0; i < a; i++) {
				for (int j = 0; j < b; j++) {
					(*this)[i][j] = RandFunc();
				}
			}
		}

		void SetRandFunc(T (*f)()) { //установить функция генерации значений для матрицы
			RandFunc = f;
		}
		matrix Tr() { //возвращает транспонированную матрицу
			matrix ans((*this)[0].size(), (*this).size());
			for (int i = 0; i < ans.size(); i++) {
				for (int j = 0; j < ans[i].size(); j++) {
					ans[i][j] = (*this)[j][i];
				}
			}
			return ans;
		}
		void change(int a, int b) { //изменяет размер матрицы и заполняет либо нулевыми значениями если RandFunc == NULL либо значениями генерируемы функцией RandFunc
			(*this).resize(a);
			for (int i = 0; i < a; i++) {
				(*this)[i].resize(b,0);
			}

			if (RandFunc) {
				for (int i = 0; i < a; i++) {
					for (int j = 0; j < b; j++) {
						(*this)[i][j] = RandFunc();
					}
				}
			}
			
		}

		 matrix operator*(const matrix &a) { //Перегрузка оператора * 

			matrix ans;
			
			if ((*this)[0].size() == a.size()) { //если выполняется условие умножение матриц умножаем матрицы по правилам алгебры
				ans.change((*this).size(), a[0].size());
				for (int i = 0; i < (*this).size(); i++) {
					for (int j = 0; j < a[0].size(); j++) {
						for (int k = 0; k < a.size(); k++) {
							ans[i][j] += (*this)[i][k] * a[k][j];
						}
					}
				}
			}
			else {
				if ((*this).size() == a.size() && (*this)[0].size() == a[0].size()) { // иначен если матрицы равного размера поэлемента умножаем (требуется на этапе обучения, где ванчале необходимо поэлементно перемножить два вектора (п, 1))
					ans.change((*this).size(), a[0].size());
					for (int i = 0; i < (*this).size(); i++) {
						for (int j = 0; j < a[0].size(); j++) {
							ans[i][j] = (*this)[i][j] * a[i][j];
						}
					}
				}
			}
			return ans;
		}
		 matrix operator+(const matrix& a) {//перегрузка оператора +
			 matrix<double> ans = (*this);
			if ((*this)[0].size() == a[0].size() && (*this).size() == a.size()) { //если размеры матриц равны поэлементно складываем
				
				for (int i = 0; i < a.size(); i++) {
					for (int j = 0; j < a[i].size(); j++) {
						ans[i][j] = (*this)[i][j] + a[i][j];
					}
				}

			}
			return ans;
		}

		 matrix operator-(const matrix& a) { // перегрузка оператора -
			 matrix<double> ans = (*this);
			if ((*this)[0].size() == a[0].size() && (*this).size() == a.size()) { //если матрицы равного размера из элементов 1 вычитаем элементы 2

				for (int i = 0; i < a.size(); i++) {
					for (int j = 0; j < a[i].size(); j++) {
						ans[i][j] = (*this)[i][j] - a[i][j];
					}
				}

			}
			return ans;
		 }

		 pair<int,int> MaxIndex() { //возвращает положение максимального элемента в матрице
			 int max_i = 0, max_j = 0;double max = (*this)[0][0];
			 for (int i = 0; i < (*this).size(); i++) {
				 for (int j = 0; j < (*this)[i].size(); j++) {
					 if ((*this)[i][j] > max) {
						 max = (*this)[i][j];
						 max_i = i;
						 max_j = j;
					 }
				 }
			 }
			 return make_pair(max_i, max_j);
		 }

		 friend std::ostream& operator<< (std::ostream& out,const matrix &a) { // перегрузка оператора << для возможности вывода матрицы посредством cout на экран или любого обекта класса ostream например в файл
			 out << "[";
			 for (int i = 0; i < a.size(); i++) {
				 if (i > 0) out << " ";
				 out << "[ ";
				 for (int j = 0; j < a[i].size(); j++) {
					 out << a[i][j] << " ";
				 }
				 out << "]";
				 if (i<a.size()-1) out << endl;
			}
			 out << "]" << endl;
			 return out;
		 }
		 friend matrix operator*(double x,  matrix a) { //перегрузка * для умножении матрицы на число
			
			 for (int i = 0; i < a.size(); i++) {
				 for (int j = 0; j < a[i].size(); j++) {
					 a[i][j] *= x; // поэлементно умножаем матрицу на число
				 }
			 }
			 return a;
		 }
private:
	T (*RandFunc)() = NULL; //указатель на функцию генерации чисел 
};

