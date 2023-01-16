#define _CRT_SECURE_NO_WARNINGS
#include "Head.h"
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

int main()
{
	char s[2048];
	memset(s, 0, 2048);
	cout << "�����������ַ�����" << endl;
	cin >> s;
	text txt;
	in(s, txt);
	encrypt(txt);
	cout << "����:";
	txt.cipherprint();
	int sum = 0;
	double avg = 0;
	for (int i = 0; i < 8; i++) {
		cout << endl <<"��"<<i+1<< "��ѩ�����ԣ�" << endl;
		cout << "�������µ������ַ�����" << endl;
		char s1[2048];
		memset(s1, 0, 2048);
		cin >> s1;
		text txt1;
		in(s1, txt1);
		encrypt(txt1);
		cout << "����:";
		txt1.cipherprint();
		int count = compare(txt, txt1);
		sum += count;
	}
	avg = (double)sum / 8;
	cout << "ƽ���ı�λ���� " << avg;
	system("pause");
}

void newint::copy(newint b)
{
	for (int i = 0; i < 4; i++)
	{
		this->a[i] = b.a[i];
	}
}

void smallbit(char* temp, int a)
{
	a *= 8;
	int i = 0;
	if (a % 512 < 448)
	{
		i = a / 512 * 512 + 448;
	}
	else i = (a + 512) / 512 * 512 + 448;
	while (a)
	{
		temp[i] = (int)a % 2;
		a /= 2;
		i++;
	}
}

void smallbit(int len, newint& a)
{
	int i = 0;
	len *= 8;
	for (int i = 0; i < 4; i++)
	{
		a.a[i] = len % 256;
		len /= 256;
	}
}

void in(char* a, text& txt)//��������
{
	memset(txt.m, 0, sizeof(txt.m));

	int index = 0;
	int i;
	int len = strlen(a);
	i = len;

	for (int j = 0; j < i + 64; j++)
	{
		txt.m[j / 512][j / 4].a[j % 4] = a[j];
	}

	txt.m[i / 512][i / 4].a[i % 4] = 128;
	i += 1;

	int t = i * 8 / 512;
	if (i * 8 % 512 > 448)
		t++;
	smallbit(len, txt.m[t][14]);
	big(A, txt.fabcd[0][0]);
	big(B, txt.fabcd[0][1]);
	big(C, txt.fabcd[0][2]);
	big(D, txt.fabcd[0][3]);
	txt.round = t;
}

void big(unsigned int a, newint& b)
{
	memset(&b, 0, sizeof(b));
	int i = 0;
	while (a)
	{
		b.a[3 - i] = a % 256;
		a /= 256;
		i++;
	}
}

void small(unsigned int a, newint& b)
{
	memset(&b, 0, sizeof(b));
	int i = 0;
	while (a)
	{
		b.a[i] = a % 256;
		a /= 256;
		i++;
	}
}

newint::newint()
{
	memset(this, 0, sizeof(newint));
}

newint add_(newint a, newint b)
{
	newint c;
	for (int i = 0; i < 4; i++)
		c.a[i] = a.a[i] + b.a[i];
	for (int i = 0; i < 3; i++)
	{
		c.a[i + 1] += c.a[i] / 256;
		c.a[i] %= 256;
	}
	c.a[3] %= 256;
	return c;
}
newint add_big(newint a, newint b)
{
	newint c;
	for (int i = 0; i < 4; i++)
		c.a[i] = a.a[i] + b.a[i];
	for (int i = 3; i > 0; i--)
	{
		c.a[i - 1] += c.a[i] / 256;
		c.a[i] %= 256;
	}
	c.a[0] %= 256;
	return c;
}
newint and_(newint a, newint b)
{
	newint c;
	for (int i = 0; i < 4; i++)
	{
		c.a[i] = a.a[i] & b.a[i];
	}
	return c;
}

newint or_(newint a, newint b)
{
	newint c;
	for (int i = 0; i < 4; i++)
	{
		c.a[i] = a.a[i] | b.a[i];
	}
	return c;
}

newint xor_(newint a, newint b)
{
	newint c;
	for (int i = 0; i < 4; i++)
	{
		c.a[i] = a.a[i] ^ b.a[i];
	}
	return c;
}

newint not_(newint a)
{
	newint c;
	for (int i = 0; i < 4; i++)
	{
		c.a[i] = ~a.a[i] & 0xff;
	}
	return c;
}

unsigned int leftmove(unsigned int a, int s)
{
	unsigned int t1 = a >> (32 - s);
	unsigned int t2 = a << s;
	unsigned int temp = t2 + t1;
	return temp;
}

newint leftmove(newint a, int s)
{
	unsigned int temp = 0;
	for (int i = 0; i < 4; i++)
	{
		temp = a.a[3 - i] + temp * 256;
	}
	unsigned int t1 = temp >> (32 - s);
	unsigned int t2 = temp << s;
	temp = t2 + t1;

	newint c;
	small(temp, c);
	return c;
}

unsigned int newint::value()
{
	unsigned temp = 0;
	for (int i = 3; i >= 0; i--)
	{
		temp = temp * 256 + a[i];
	}
	return temp;
}

void newint::set(unsigned int s)
{
	memset(a, 0, sizeof(a));
	int i = 0;
	while (s)
	{
		a[i] = s % 256;
		s /= 256;
		i++;
	}
}

void enF(int index, text& txt)//����F
{
	for (int i = 0; i < 16; i++)
	{
		unsigned int a = txt.fabcd[i][0].value();
		unsigned int b = txt.fabcd[i][1].value();
		unsigned int c = txt.fabcd[i][2].value();
		unsigned int d = txt.fabcd[i][3].value();


		unsigned int temp = (b & c) | (~b & d);
		temp += a;
		unsigned int value = txt.m[index][i].value();
		temp += value;
		unsigned int tt = abs(sin(i + 1)) * pow(2, 32);
		temp += tt;
		temp = leftmove(temp, s[0][i]);
		temp += b;

		txt.fabcd[i + 1][0].copy(txt.fabcd[i][3]);//A.copy(D
		txt.fabcd[i + 1][2].copy(txt.fabcd[i][1]);//C.copy(B
		txt.fabcd[i + 1][3].copy(txt.fabcd[i][2]);//D.copy(C
		txt.fabcd[i + 1][1].set(temp);

	}
	for (int i = 0; i < 4; i++)
	{
		txt.gabcd[0][i].copy(txt.fabcd[16][i]);
	}
}
void enG(int index, text& txt)
{
	newint e[16];
	for (int i = 0; i < 16; i++)
	{
		e[i].copy(txt.m[index][(1 + 5 * i) % 16]);
	}
	for (int i = 0; i < 16; i++)
	{
		unsigned int a = txt.gabcd[i][0].value();
		unsigned int b = txt.gabcd[i][1].value();
		unsigned int c = txt.gabcd[i][2].value();
		unsigned int d = txt.gabcd[i][3].value();

		unsigned int temp = (b & d) | (c & ~d);
		temp += a;
		unsigned int value = e[i].value();
		temp += value;
		unsigned int tt = abs(sin(i + 17)) * pow(2, 32);
		temp += tt;
		temp = leftmove(temp, s[1][i]);
		temp += b;

		txt.gabcd[i + 1][0].copy(txt.gabcd[i][3]);//A.copy(D
		txt.gabcd[i + 1][2].copy(txt.gabcd[i][1]);//C.copy(B
		txt.gabcd[i + 1][3].copy(txt.gabcd[i][2]);//D.copy(C
		txt.gabcd[i + 1][1].set(temp);

	}

	for (int i = 0; i < 4; i++)
	{
		txt.habcd[0][i].copy(txt.gabcd[16][i]);
	}
}

void enH(int index, text& txt)
{
	newint e[16];
	for (int i = 0; i < 16; i++)
	{
		e[i].copy(txt.m[index][(5 + 3 * i) % 16]);
	}
	for (int i = 0; i < 16; i++)
	{
		unsigned int a = txt.habcd[i][0].value();
		unsigned int b = txt.habcd[i][1].value();
		unsigned int c = txt.habcd[i][2].value();
		unsigned int d = txt.habcd[i][3].value();


		unsigned int temp = (b ^ c ^ d);
		temp += a;
		unsigned int value = e[i].value();
		temp += value;
		unsigned int tt = abs(sin(i + 33)) * pow(2, 32);
		temp += tt;
		temp = leftmove(temp, s[2][i]);
		temp += b;


		txt.habcd[i + 1][0].copy(txt.habcd[i][3]);//A.copy(D
		txt.habcd[i + 1][2].copy(txt.habcd[i][1]);//C.copy(B
		txt.habcd[i + 1][3].copy(txt.habcd[i][2]);//D.copy(C
		txt.habcd[i + 1][1].set(temp);

	}

	for (int i = 0; i < 4; i++)
	{
		txt.iabcd[0][i].copy(txt.habcd[16][i]);
	}
}

void enI(int index, text& txt)
{
	newint e[16];
	for (int i = 0; i < 16; i++)
	{
		e[i].copy(txt.m[index][(7 * i) % 16]);
	}
	for (int i = 0; i < 16; i++)
	{
		unsigned int a = txt.iabcd[i][0].value();
		unsigned int b = txt.iabcd[i][1].value();
		unsigned int c = txt.iabcd[i][2].value();
		unsigned int d = txt.iabcd[i][3].value();


		unsigned int temp = (c ^ (b | (~d)));
		temp += a;
		unsigned int value = e[i].value();
		temp += value;
		unsigned int tt = abs(sin(i + 49)) * pow(2, 32);
		temp += tt;
		temp = leftmove(temp, s[3][i]);
		temp += b;

		txt.iabcd[i + 1][0].copy(txt.iabcd[i][3]);//A.copy(D
		txt.iabcd[i + 1][2].copy(txt.iabcd[i][1]);//C.copy(B
		txt.iabcd[i + 1][3].copy(txt.iabcd[i][2]);//D.copy(C
		txt.iabcd[i + 1][1].set(temp);
	}


}

void encrypt(text& txt)
{
	for (int i = 0; i <= txt.round; i++)
	{
		enF(i, txt);
		enG(i, txt);
		enH(i, txt);
		enI(i, txt);
		for (int j = 0; j < 4; j++)
		{

			txt.fabcd[0][j] = add_(txt.fabcd[0][j], txt.iabcd[16][j]);
		}
	}
}

void newint::print()
{
	for (int i = 0; i < 4; i++)
		printf("%02X", a[i]);
}

void text::cipherprint()
{
	for (int i = 0; i < 4; i++)
	{
		fabcd[0][i].print();
	}
	cout << endl;
}

void int2bin(int a, char bin[8])
{
	memset(bin, '0', 8);
	int i = 7;
	while (1)
	{
		if (a == 0)break;
		a % 2 == 1 ? bin[i] = '1' : bin[i] = '0';
		a /= 2;
		i--;
	}

}
int compare(text& txt1, text& txt2) {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			char bin1[8], bin2[8];
			int2bin(txt1.fabcd[0][i].a[j], bin1);
			int2bin(txt2.fabcd[0][i].a[j], bin2);
			for (int k = 0; k < 8; k++) {
				if (bin1[k] != bin2[k])
					count++;
			}
		}
	}
	cout << "�ı�λ��Ϊ�� " << count << endl;;
	return count;
}

void text::tostring(char* cipher)
{
	int len = 0;
	for (int i = 0; i < 4; i++)
	{
		char str[5] = {};
		for (int j = 0; j < 4; j++)
		{
			sprintf(str, "%02X", fabcd[0][i].a[j]);
			int s = strlen(str);
			for (int k = 0; k < s; k++)
			{
				cipher[len++] = str[k];
			}
		}
	}
}