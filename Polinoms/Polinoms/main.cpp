#include"Polinom.h"
#include <iostream>
#include <locale.h>

using namespace std;


void main()
{
	int choise;
	setlocale(LC_ALL, "Russian");
	cout << "�������� ����� ��������, ������� ������ ���������:" << endl << " 1.������� 2 ��������" << endl << " 2.�������� ������� � ��������" << endl << " 3. �������� �� �����/�����" << endl << "��� ���������� ������� 0" << endl;
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
			cout << "1.��������� �� �����" << endl << "2.��������� �� �����" << endl;
			std::cin >> tmp;
			switch (tmp)
			{
			case 1:
			{
				cout << "p:";
				cin >> p;
				cout << endl << "����� =";
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
				cout << endl << "����� =";
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