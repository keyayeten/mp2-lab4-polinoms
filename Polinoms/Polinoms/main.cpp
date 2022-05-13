#include"Polinom.h"
#include <iostream>
#include <locale.h>

using namespace std;


void main()
{
	int choise;
	setlocale(LC_ALL, "Russian");
	cout << "Выберите номер операции, которую хотите проделать:" << endl << " 1.Сложить 2 полинома" << endl << " 2.Добавить полином к текущему" << endl << " 3. Умножить на число/моном" << endl << "Для завершения нажмите 0" << endl;
	do
	{
		TPolinom p, q;
		int tmp;
		bool flag = true;
		cin >> choise;
		TPolinom res1, res2;
		switch (choise)
		{
		case 1:
			cout << "p: ";
			cin >> p;
			cout << endl << "q: ";
			cin >> q;
			res1 = p + q;
			cout << endl << p << " + " << q << " = " << res1 << endl;
			break;
		case 2:
			cout << "p: ";
			cin >> p;
			cout << endl << "q: ";
			cin >> q;
			cout << endl << p << " += " << q << " = ";
			p += q;
			cout << p << endl;
			break;
		case 3:
			cout << "1.Умножение на число" << endl << "2.Умножение на моном" << endl;
			std::cin >> tmp;
			switch (tmp)
			{
			case 1:
			{
				cout << "p:";
				cin >> p;
				cout << endl << "Число =";
				double val;
				cin >> val;
				res2 = p * val;
				cout << endl << p << " * " << val << " = " << res2 << endl;
				break;
			}
			case 2:
			{
				TPolinom res;
				cout << "p:";
				cin >> p;
				cout << endl << "Моном =";
				TMonom m;
				cin >> m;
				res = p * m;
				cout << endl << p << " * " << m << " = " << res << endl;
				break;
			}
			default:
				break;
			}break;

		}
	} while (choise != 0);
}