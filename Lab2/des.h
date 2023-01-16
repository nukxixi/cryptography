#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <exception>
using namespace std;

//明文IP置换表
int IP_table[64] =
{
	58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
};

//E扩展表
int E_table[48] =
{
	32,1,2,3,4,5,4,5,6,7,8,9,
	8,9,10,11,12,13,12,13,14,15,16,17,
	16,17,18,19,20,21,20,21,22,23,24,25,
	24,25,26,27,28,29,28,29,30,31,32,1
};

//左循环移位位数表
int shift_table[16] =
{
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};
//PC-1置换选择表
int pc1_table[56] =
{
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4
};
//PC-2置选择表
int pc2_table[48] =
{
	14,17,11,24,1,5,
	3,28,15,6,21,10,
	23,19,12,4,26,8,
	16,7,27,20,13,2,
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32
};

//S盒
int S_Box[8][4][16] = {
	{
		{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 },
	},
	{
		{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 },
	},
	{
		{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 },
	},
	{
		{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 },
	},
	{
		{ 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 },
	},
	{
		{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 },
	},
	{
		{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
{ 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 },
	},
	{
		{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 },
	}
};
//P置换表
int P_table[32] =
{
	16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25
};

//逆IP置换IPR表
int IPR_table[64] =
{
	40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
};

class DES
{
public:
	DES() {};                                               
	void getKey(string keytxt); 
	string encrypt(string input);   
	string decrypt(string input);
public:
	int plain[64], cipher[64], key[64]; 
};

void getBin(string hex, int* bin) {
	int k = 0;
	char c;
	for (int i = 0; i < hex.length(); i++) {
		int num = 0;
		c = hex[i];
		if (hex[i] >= '0' && hex[i] <= '9') {
			num = c - '0';
		}
		else if (hex[i] >= 'A' && hex[i] <= 'F') {
			num = c - 'A' + 10;
		}
		else if (hex[i] >= 'a' && hex[i] <= 'f') {
			num = c - 'a' + 10;
		}
		for (k = 4 * i + 3; k >= 4 * i; k--) {
			bin[k] = num % 2;
			num /= 2;
		}
	}
}

void getHex(int* bin, string &hex) {
	char tmp[17];
	for (int i = 0, k = 0; i < 16; i++) {
		int val = 0;
		for (k = 4 * i; k <= 4 * i + 3; k++) {
			val *= 2;
			val += bin[k];
		}
		if (val < 10) {
			tmp[i] = val + '0';
		}
		else if (val >= 10 && val <= 15) {
			tmp[i] = val - 10 + 'A';
		}
	}
	tmp[16] = '\0';
	hex = tmp;
}

void DES::getKey(string keytxt) {
	getBin(keytxt, key);
}

void PC1_subs(int key[64],int new_key[56])
{
	for (int i = 0; i < 56; i++)
		new_key[i] = key[pc1_table[i] - 1];
}
void PC2_subs(int key[56], int new_key[48])
{
	for (int i = 0; i < 48; i++)
		new_key[i] = key[pc2_table[i] - 1];
}

//移位
void shift(int key[56], int shift_bit)
{
	int tmp[56];
	for (int i = 0; i < 56; i++) {
		if (i < 28)
			tmp[i] = key[(i + shift_bit) % 28];
		else
			tmp[i] = key[(i - 28 + shift_bit) % 28 + 28];
	}
	for (int i = 0; i < 56; i++)
		key[i] = tmp[i];
}

//密钥置换过程
void keySubs(int rol, int key[64], int new_key[48])
{																																	
	int tmp[56];
	//PC-1置换
	PC1_subs(key, tmp);
	//一分为二，分别循环左移，迭代移位次数为当前轮数
	for (int i = 0; i < rol; i++)
		shift(tmp, shift_table[i]);
	//PC-2置换，结果为48位轮密钥
	PC2_subs(tmp, new_key);
}
//明文IP置换
void IP_subs(int plain[64], int new_plain[64]){
	for (int i = 0; i < 64; i++)
		new_plain[i] = plain[IP_table[i] - 1];
}

//E扩展
void E_extend(int plain[32], int new_plain[48])
{
	for (int i = 0; i < 48; i++)
		new_plain[i] = plain[E_table[i] - 1];
}

//S盒替换
void S_subs(int plain[48], int new_plain[32])
{
	for (int i = 0; i < 8; i++)    //8个S盒*6位
	{
		//行数为第1和6位
		int row = plain[i * 6] * 2 + plain[i * 6 + 5] * 1;
		//列数为中间四位
		int col = plain[i * 6 + 1] * 8 + plain[i * 6 + 2] * 4 + plain[i * 6 + 3] * 2 + plain[i * 6 + 4] * 1;
		int s = S_Box[i][row][col];  
		//十进制转为二进制
		for (int j = 1; j <= 4; j++) {
			new_plain[(4 - j) + 4 * i] = s % 2;
			s /= 2;
		}
	}
}

//P盒替换
void P_subs(int plain[32], int new_plain[32])
{
	for (int i = 0; i < 32; i++)
		new_plain[i] = plain[P_table[i] - 1];
}

//IP逆置换
void IP_R_subs(int plain[64], int new_plain[64])
{
	for (int i = 0; i < 64; i++)
		new_plain[i] = plain[IPR_table[i] - 1];
}

//DES单轮加密
void roleDES(int plain[64], int new_plain[64], int rol_key[48])
{
	int left[32], right[32];
	for (int i = 0; i < 32; i++) {
		left[i] = plain[i];
	}
	for (int i= 0; i < 32; i++) {
		right[i] = plain[i+32];
	}
	//左半部分结果为右半部分输入
	for (int i = 0; i < 32; i++)
		new_plain[i] = right[i];
	//右半部分输入先做E扩展，到48位
	int right1[48];
	E_extend(right, right1);
	//与当前轮密钥异或
	int right2[48];
	for (int i = 0; i < 48; i++)
		right2[i] = right1[i] ^ rol_key[i];
	//S盒置换
	int right3[32];
	S_subs(right2, right3);
	//P盒置换
	int right4[32];
	P_subs(right3, right4);
	//与原左半部分异或
	int right5[32];
	for (int i = 0; i < 32; i++)
		right5[i] = right4[i] ^ left[i];
	//右半部分输出结果
	for (int i = 0; i < 32; i++)
		new_plain[i+32] = right5[i];
}

//加密函数
string DES::encrypt(string plaintxt)
{
	getBin(plaintxt, plain);
	
	//IP置换
	int plain2[64];
	IP_subs(plain, plain2);

	int plain3[64];
	int rolekey[48];//轮密钥

	for (int i = 0; i < 16; i++)
	{
		//生成当前轮的密钥
		keySubs(i+1, key, rolekey);
		//利用轮密钥进行加密
		roleDES(plain2, plain3, rolekey);
		//本轮输出作为下一轮的输入
		for (int i = 0; i < 64; i++) {
			plain2[i] = plain3[i];
		}
	}
	//左右两部分互换位置
	int tmp[64];
	for (int i = 0; i < 64; i++)
	{
		if (i < 32)
			tmp[i] = plain3[i + 32];
		else 
			tmp[i] = plain3[i - 32];
	}

	//初始置换的逆置换
	IP_R_subs(tmp, cipher);
	//二进制转十六进制
	string cipher_hex;
	getHex(cipher, cipher_hex);
	return cipher_hex;
}

//解密函数，返回明文
string DES::decrypt(string ciphertxt)
{
	getBin(ciphertxt, cipher);

	//IP置换
	int cipher2[64];
	IP_subs(cipher, cipher2);
	
	int cipher3[64];
	int rolekey[48];

	for (int i = 16; i >=1; i--) {
		keySubs(i, key, rolekey);
		roleDES(cipher2, cipher3, rolekey);
		for (int i = 0; i < 64; i++) {
			cipher2[i] = cipher3[i];
		}
	}

	int tempres[64];
	for (int i = 0; i < 64; i++)
	{
		if (i < 32)
			tempres[i] = cipher3[i + 32];
		else
			tempres[i] = cipher3[i - 32];
	}
	IP_R_subs(tempres, plain);

	string plain_hex;
	getHex(plain, plain_hex);
	return plain_hex;
}