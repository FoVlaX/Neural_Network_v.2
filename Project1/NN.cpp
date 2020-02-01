#include "NN.h"
double RF() {

	return double(rand() % 2456) / 2457.0; //функция для случайного задания весов и  дополений

}

NN::NN(int n, int m, int In, int Out)

{
	W.resize(n+1);
	b.resize(n+1);
	deep = n;
	width = m;
	W[0].SetRandFunc(RF);
	W[0].change(m, In);
	b[0].SetRandFunc(RF);
	b[0].change(m, 1);

	for (int i = 1; i < n; i++) {
		W[i].SetRandFunc(RF);
		W[i].change(m, m);                          //создаем матрицы весов и веторы дополнений и заполняем их случайными значениями в соответвии с входными параметрами
		b[i].SetRandFunc(RF);
		b[i].change(m, 1);
	}

	W[n].SetRandFunc(RF);
	W[n].change(Out, m);
	b[n].SetRandFunc(RF);
	b[n].change(Out, 1);
}

matrix<double> NN::Afun(matrix<double> a)
{
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++) {
			a[i][j] = Afun_e(a[i][j]);
		}
	}
	return a;
}

matrix<double> NN::d_Afun(matrix<double> a)
{
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++) {
			a[i][j] = d_Afun_e(a[i][j]);
		}
	}
	return a;
}

answer NN::feedfoward(matrix<double> a)
{
	answer f;
	
	f.f.push_back(a);
	f.h.push_back(a);

	for (int i = 0; i < deep+1; i++) {
		matrix<double> s = W[i] * f.f[i] + b[i]; //прямое прохожение по сети
		f.h.push_back(s);
		s = Afun(s);
		f.f.push_back(s);
	}
	f.ans = f.f[f.f.size() - 1];
	return f;
}

void NN::teach(matrix<double> In, matrix<double> Out)
{
	answer ans;
	ans = feedfoward(In); //прямое прохождение получение необходимых значений нейронвов 
	matrix<double> y = ans.ans; //присваивание значений для удобства локальным переменным
	vector<matrix<double>> f = ans.f;
	vector<matrix<double>> h = ans.h;
	vector<matrix<double>> d_W = W;
	vector<matrix<double>> d_b = b;
	int l = 1;
	matrix<double> Y;
	
	//здесь мы наодим чатсные производные по весам и дополнениям по квадратичной функции ошибки (Out - y)^2/2 где у - вывод нейросети Out - эталонное значение

	Y =  (Out - y) * d_Afun(h[deep + 1]); //нахоим производную по конечный дополнениям
	
	while (deep + 2 - l > 0)
	{
		d_b[deep + 1 - l] = Y; //частные производные по дополнениям
		d_W[deep + 1 - l] = Y * f[deep + 1 - l].Tr(); //частные производные по весам
		if (deep + 2 - l > 1) {
			Y = (Y.Tr() * W[deep + 1 - l]).Tr() * d_Afun(h[deep + 1 - l]); //частные производные дополнений следующего слоя
		}
		l++; //обратное прохождение
	}

	for (int i = 0; i < deep + 1; i++)
	{
		b[i] = b[i] + 0.8*d_b[i]; // изменение весов и дополнение на полученные значения частных производных
		W[i] = W[i] + 0.8*d_W[i];
	}
}

void NN::save(string str)
{
	ofstream out(str);
	out << deep << " " << width << endl;
	for (int i = 0; i <= deep; i++) {
		out << W[i].size() << " " << W[i][0].size() << endl;
		for (int k = 0; k < W[i].size(); k++) {
			for (int j = 0; j < W[i][0].size(); j++) {
				out << W[i][k][j] << " ";
			}
			out << endl;
		}
		out << b[i].size() << " " << b[i][0].size() << endl;
		for (int k = 0; k < b[i].size(); k++) {
			for (int j = 0; j < b[i][0].size(); j++) {
				out << b[i][k][j] << " ";
			}
			out << endl;
		}
	}
	out.close();
}

void NN::load(string str)
{
	ifstream in(str);
	in >> deep >> width;
	W.resize(deep + 1);
	b.resize(deep + 1);
	for (int i = 0; i <= deep; i++) {
		int n, m;
		in >> n >> m;
		W[i].resize(n);
		for (int k = 0; k < W[i].size(); k++) {
			W[i][k].resize(m);
			for (int j = 0; j < W[i][0].size(); j++) {
				in >> W[i][k][j];
			}
		}
		in >> n >> m;
		b[i].resize(n);
		for (int k = 0; k < b[i].size(); k++) {
			b[i][k].resize(m);
			for (int j = 0; j < b[i][0].size(); j++) {
				in >> b[i][k][j];
			}
		}
	}
	in.close();
}

double NN::Afun_e(double a)
{
	return 1 / ( 1 + exp(-0.004*a)); //испольуем сигмоиду
}

double NN::d_Afun_e(double a)
{
	double c = Afun_e(a);
	return c*(1 - c);
}
