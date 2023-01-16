#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "BigInt.h"
#include "GenPrime.h"
#include <ctime>
using namespace std;

int main()
{
	cout << "生成大素数p:" << endl;
	BigInt p = GeneratePrime();
	p.display();
	cout << endl;
	cout << "生成大素数q:" << endl;

	BigInt q = GeneratePrime();
	q.display();
	cout << endl;

	cout << "公钥n = p * q 结果为：" << endl;
	BigInt n = p * q;
	n.display();
	cout << endl;
	//求欧拉函数
	BigInt t = (p - 1) * (q - 1);
	//e为公开钥
	BigInt e;
	//d为密钥，即e模t的乘法逆元
	BigInt d;
	//y用于参与扩展欧几里得运算，存储t模e的乘法逆元
	BigInt y;
	BigInt temp;
	while (1)
	{
		//产生与t互质的e
		e.Random();
		while (!(Gcd(e, t) == 1))
		{
			e.Random();
		}

		//用扩展欧几里德算法求出e模t的乘法逆元
		temp = ExtendedGcd(e, t, d, y);
		break;

	}

	cout << "公钥e为： " << endl;
	e.display();
	cout << endl;

	cout << "密钥d为： " << endl;
	d.display();
	cout << endl;
	cout << "随机生成明文分组m为： " << endl;
	BigInt m;
	m.Random();
	m.display();
	cout << endl;
	cout << "用密钥e对m加密,得到密文分组c为： " << endl;
	BigInt c = PowerMode(m, e, n);
	c.display();
	cout << endl;
	cout << "用公钥d对c解密，得到明文分组m为: " << endl;
	BigInt m2 = PowerMode(c, d, n);
	m2.display();
	cout << endl;

	system("pause");
	return 0;
}
