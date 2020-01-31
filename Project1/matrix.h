#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
template <class T>
class matrix : public vector<vector<T>>
{
	public:
		matrix() : vector<vector<T>>() {
		}

		matrix(vector<vector<T>> a) : vector<vector<T>>() {
			(*this).resize(a.size());
			for (int i = 0; i < a.size(); i++) {
				(*this)[i].resize(a[i].size());
				for (int j = 0; j < a[i].size(); j++) {
					(*this)[i][j] = a[i][j];
				}
			}
		}

		matrix(int a, int b) : vector<vector<T>>() {
			(*this).resize(a);
			for (int i = 0; i < a; i++) {
				(*this)[i].resize(b,0);
			}
		}

		matrix(int a, int b, T(*f)()) : vector<vector<T>>() {
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

		void SetRandFunc(T (*f)()) {
			RandFunc = f;
		}
		matrix Tr() {
			matrix ans((*this)[0].size(), (*this).size());
			for (int i = 0; i < ans.size(); i++) {
				for (int j = 0; j < ans[i].size(); j++) {
					ans[i][j] = (*this)[j][i];
				}
			}
			return ans;
		}
		void change(int a, int b) {
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

		 matrix operator*(const matrix &a) {

			matrix ans;
			
			if ((*this)[0].size() == a.size()) {
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
				if ((*this).size() == a.size() && (*this)[0].size() == a[0].size()) {
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
		 matrix operator+(const matrix& a) {
			 matrix<double> ans = (*this);
			if ((*this)[0].size() == a[0].size() && (*this).size() == a.size()) {
				
				for (int i = 0; i < a.size(); i++) {
					for (int j = 0; j < a[i].size(); j++) {
						ans[i][j] = (*this)[i][j] + a[i][j];
					}
				}

			}
			return ans;
		}

		 matrix operator-(const matrix& a) {
			 matrix<double> ans = (*this);
			if ((*this)[0].size() == a[0].size() && (*this).size() == a.size()) {

				for (int i = 0; i < a.size(); i++) {
					for (int j = 0; j < a[i].size(); j++) {
						ans[i][j] = (*this)[i][j] - a[i][j];
					}
				}

			}
			return ans;
		 }

		 pair<int,int> MaxIndex() {
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

		 friend std::ostream& operator<< (std::ostream& out,const matrix &a) {
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
		 friend matrix operator*(double x,  matrix a) {
			
			 for (int i = 0; i < a.size(); i++) {
				 for (int j = 0; j < a[i].size(); j++) {
					 a[i][j] *= x;
				 }
			 }
			 return a;
		 }
private:
	T (*RandFunc)() = NULL;
};

