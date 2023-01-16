#pragma once

unsigned int A = 0x01234567, 
B = 0x89abcdef,
C = 0xfedcba98, 
D = 0x76543210;

int s[4][16] =
{
	{7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22},
	{5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20},
	{4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23},
	{6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21}
};

struct newint
{
	int a[4];
	newint();
	void copy(newint b);
	void print();
	unsigned int value(); //以小端方式读入和设置值
	void set(unsigned int);
};

newint add_(newint a, newint b);
newint add_big(newint a, newint b);
newint and_(newint a, newint b);
newint or_(newint a, newint b);
newint xor_(newint a, newint b);
newint not_(newint a);
newint leftmove(newint a, int s);//循环左移
unsigned int leftmove(unsigned int a, int s);
struct text
{
	int round;
	newint m[1500][16]; //明文
	newint fabcd[17][4];
	newint gabcd[17][4];
	newint habcd[17][4];
	newint iabcd[17][4];
	newint cipher[4];
	void cipherprint();
	void tostring(char*);
};
void in(char* a, text& m);//输入明文
void small(unsigned int a, newint& b);//小端
void big(unsigned int a, newint& b);//大端
void smallbit(int len, newint& a);
void enF(int index, text& txt);
void enG(int index, text& txt);
void enH(int index, text& txt);
void enI(int index, text& txt);
void encrypt(text& txt);
int compare(text& txt1, text& txt2);

