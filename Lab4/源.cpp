#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "BigInt.h"
#include "GenPrime.h"
#include <ctime>
using namespace std;

int main()
{
	cout << "���ɴ�����p:" << endl;
	BigInt p = GeneratePrime();
	p.display();
	cout << endl;
	cout << "���ɴ�����q:" << endl;

	BigInt q = GeneratePrime();
	q.display();
	cout << endl;

	cout << "��Կn = p * q ���Ϊ��" << endl;
	BigInt n = p * q;
	n.display();
	cout << endl;
	//��ŷ������
	BigInt t = (p - 1) * (q - 1);
	//eΪ����Կ
	BigInt e;
	//dΪ��Կ����eģt�ĳ˷���Ԫ
	BigInt d;
	//y���ڲ�����չŷ��������㣬�洢tģe�ĳ˷���Ԫ
	BigInt y;
	BigInt temp;
	while (1)
	{
		//������t���ʵ�e
		e.Random();
		while (!(Gcd(e, t) == 1))
		{
			e.Random();
		}

		//����չŷ������㷨���eģt�ĳ˷���Ԫ
		temp = ExtendedGcd(e, t, d, y);
		break;

	}

	cout << "��ԿeΪ�� " << endl;
	e.display();
	cout << endl;

	cout << "��ԿdΪ�� " << endl;
	d.display();
	cout << endl;
	cout << "����������ķ���mΪ�� " << endl;
	BigInt m;
	m.Random();
	m.display();
	cout << endl;
	cout << "����Կe��m����,�õ����ķ���cΪ�� " << endl;
	BigInt c = PowerMode(m, e, n);
	c.display();
	cout << endl;
	cout << "�ù�Կd��c���ܣ��õ����ķ���mΪ: " << endl;
	BigInt m2 = PowerMode(c, d, n);
	m2.display();
	cout << endl;

	system("pause");
	return 0;
}
