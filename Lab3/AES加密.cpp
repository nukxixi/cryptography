#include "myaes.h"
using namespace std;
string int2binstr(int input[4][4]) {
	string output;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			string str = "00000000";
			for (int k = 7; k >= 0; k--) {
				str[k] = '0' + input[j][i] % 2;
				input[j][i] /= 2;
			}
			output += str;
		}
	}
	return output;
}

void binstr2int(int input[4][4], string str) {
	unsigned char* out = new unsigned char[16];
	for (int i = 0; i <= 15; i++) {
		int start = i * 8;
		int temp = 0;
		for (int j = start; j <= start + 7; j++) {
			int each = 1;
			for (int s = 1; s <= 7 - j + start; s++) {
				each *= 2;
			}
			if (str[i] == '1') {
				temp += each;
			}
		}
		out[i] = temp;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			input[j][i] = out[j * 4 + i];
		}
	}
}

//伽罗瓦域上的乘法
unsigned char XTIME(unsigned char x) {
	return ((x << 1) ^ ((x & 0x80) ? 0x1b : 0x00));
}
int multiply(int a, int b)
{
	unsigned char temp[8] = { a };
	unsigned char result = 0x00;
	int i = 0;
	for (i = 1; i < 8; i++) {
		temp[i] = XTIME(temp[i - 1]);
	}
	result = (b & 0x01) * a;
	for (i = 1; i <= 7; i++) {
		result ^= (((b >> i) & 0x01) * temp[i]);
	}
	return result;
}

//密钥扩展
void KeyExpansion(int key[4][4], int w[11][4][4])
{
	for (int i = 0; i < 4; ++i)//将key存在w[0]中
	{
		for (int j = 0; j < 4; j++)
			w[0][i][j] = key[j][i];
	}
	for (int i = 1; i < 11; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			int temp[4];
			if (j == 0)
			{
				temp[0] = w[i - 1][3][1];
				temp[1] = w[i - 1][3][2];
				temp[2] = w[i - 1][3][3];
				temp[3] = w[i - 1][3][0];

				temp[0] = S[temp[0] >> 4][temp[0] & 0x0F] ^ rC[i - 1];
				temp[1] = S[temp[1] >> 4][temp[1] & 0x0F];
				temp[2] = S[temp[2] >> 4][temp[2] & 0x0F];
				temp[3] = S[temp[3] >> 4][temp[3] & 0x0F];
			}
			else
			{
				temp[0] = w[i][j - 1][0];
				temp[1] = w[i][j - 1][1];
				temp[2] = w[i][j - 1][2];
				temp[3] = w[i][j - 1][3];
			}
			for (int k = 0; k < 4; k++)
			{
				w[i][j][k] = w[i - 1][j][k] ^ temp[k];
			}
		}
	}
}

//字节代换
void ByteSub1(int a[4][4]) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//字节的高四位作为行号,低四位作为列号,到S盒里读取
			a[i][j] = S[a[i][j] >> 4][a[i][j] & 0x0F];
		}
	}
}
void ByteSub2(int a[4][4]) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//字节的高四位作为行号,低四位作为列号,到r_S盒里读取
			a[i][j] = r_S[a[i][j] >> 4][a[i][j] & 0x0F];
		}
	}
}

//行移位
void ShiftRow1(int a[4][4]) {
	for (int i = 1; i < 4; i++) {
		int j = i;
		while (j--) {
			int temp = a[i][0];
			a[i][0] = a[i][1];
			a[i][1] = a[i][2];
			a[i][2] = a[i][3];
			a[i][3] = temp;
		}
	}
}
void ShiftRow2(int a[4][4]) {
	for (int i = 1; i < 4; i++) {
		int j = i;
		while (j--) {
			int temp = a[i][3];
			a[i][3] = a[i][2];
			a[i][2] = a[i][1];
			a[i][1] = a[i][0];
			a[i][0] = temp;
		}
	}
}

//矩阵相乘，注意乘法和加法都是在伽罗瓦域上进行的
void matrixMul(int m1[4][4], int m2[4][4])
{
	int m3[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m3[i][j] = multiply(m2[0][j], m1[i][0]);
			for (int k = 1; k < 4; k++) {
				m3[i][j] ^= multiply(m2[k][j], m1[i][k]);
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m2[i][j] = m3[i][j];
		}
	}
}

//列混合
void MixColumn1(int a[4][4])
{
	matrixMul(confuseMatrix1,a);
}
void MixColumn2(int a[4][4])
{
	matrixMul(confuseMatrix2, a);
}


//密钥加
void AddRoundKey(int a[4][4], int key[4][4])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			a[i][j] ^= key[j][i];
		}
	}
}

//加密
void Encode(int cipher[4][4], int key[4][4])
{
	int subKey[11][4][4];
	//产生轮子密钥
	KeyExpansion(key, subKey);
	//一次密钥加
	AddRoundKey(cipher, subKey[0]);
	for (int i = 1; i <= 10; ++i)
	{
		ByteSub1(cipher);//字节代换
		ShiftRow1(cipher);//行移位变换
		if (i != 10) MixColumn1(cipher); //列混合变换，末尾轮没有列混合变换
		AddRoundKey(cipher, subKey[i]); //密钥加
	}
}
//解密
void Decode(int plain[4][4], int key[4][4])
{
	int subKey[11][4][4];
	KeyExpansion(key, subKey);
	AddRoundKey(plain, subKey[10]);
	for (int i = 9; i >= 0; --i)
	{
		ShiftRow2(plain);
		ByteSub2(plain);
		AddRoundKey(plain, subKey[i]);
		if (i != 0) MixColumn2(plain);
	}
}

int main() {
	int flag;
	cout << "请选择操作：1.加密  2.解密  3.改变明文，不改变密钥  4.改变密钥，不改变明文" << endl;
	while (1) {
		cin >> flag;
		if (flag == 1) {
			int plain[4][4];
			int cipher[4][4];
			int key[4][4];
			cout << "请输入128位明文（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cin >> (hex) >> plain[j][i];
				}
			}
			cout << "请输入128位密钥（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cin >> (hex) >> key[j][i];
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cipher[i][j] = plain[i][j];
				}
			}
			Encode(cipher, key);
			cout << "密文为（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (cipher[j][i] < 16)
						cout << "0";
					cout << (hex) << cipher[j][i] << " ";
				}
			}
			cout << endl;
			break;
		}

		else if (flag == 2) {
			int plain[4][4];
			int cipher[4][4];
			int key[4][4];
			cout << "请输入128位密文（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cin >> (hex) >> cipher[j][i];
				}
			}
			cout << "请输入128位密钥（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cin >> (hex) >> key[j][i];
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					plain[i][j] = cipher[i][j];
				}
			}
			Decode(plain, key);
			cout << "明文为（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (plain[j][i] < 16)
						cout << "0";
					cout << (hex) << plain[j][i] << " ";
				}
			}
			cout << endl;
			break;
		}
		else if (flag == 3) {
			int plain[4][4];
			int cipher[4][4];
			int key[4][4];
			int sum = 0;
			double avg = 0;
			cout << "请输入128位明文（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cin >> (hex) >> plain[j][i];
				}
			}
			cout << "请输入128位密钥（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cin >> (hex) >> key[j][i];
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cipher[i][j] = plain[i][j];
				}
			}
			Encode(cipher, key);
			cout << "密文为（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (cipher[j][i] < 16)
						cout << "0";
					cout << (hex) << cipher[j][i] << " ";
				}
			}
			cout << endl;
			int new_cipher[4][4];
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					new_cipher[i][j] = plain[i][j];
				}
			}
			string plain_str = int2binstr(plain);
			string cipher_str = int2binstr(cipher);
			
			for (int i = 0; i < 8; i++) {
				int count = 0;
				if (plain_str[i] == '0')
					plain_str[i] = '1';
				else
					plain_str[i] = '0';
				binstr2int(new_cipher, plain_str);
				Encode(new_cipher, key);
				string new_cipher_str= int2binstr(new_cipher);
				for (int j = 0; j < 128; j++) {
					if (new_cipher_str[j] != cipher_str[j])
						count++;
				}
				sum += count;
				cout << "明文改变第" << i << "位，密文改变了"<<dec << count << "位" << endl;
				if (plain_str[i] == '0')
					plain_str[i] = '1';
				else
					plain_str[i] = '0';
			}
			avg = double(sum) / 8;
			cout << "平均改变位数：" << avg << endl;
			break;
		}
		else if (flag == 4) {
			int plain[4][4];
			int cipher[4][4];
			int key[4][4];
			int sum = 0;
			double avg = 0;
			cout << "请输入128位明文（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cin >> (hex) >> plain[j][i];
				}
			}
			cout << "请输入128位密钥（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cin >> (hex) >> key[j][i];
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					cipher[i][j] = plain[i][j];
				}
			}
			Encode(cipher, key);
			cout << "密文为（16进制）:";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (cipher[j][i] < 16)
						cout << "0";
					cout << (hex) << cipher[j][i] << " ";
				}
			}
			cout << endl;
			int new_cipher[4][4];
			int new_key[4][4];
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					new_cipher[i][j] = plain[i][j];
				}
			}
			string key_str = int2binstr(key);
			string cipher_str = int2binstr(cipher);

			for (int i = 0; i < 8; i++) {
				int count = 0;
				if (key_str[i] == '0')
					key_str[i] = '1';
				else
					key_str[i] = '0';
				binstr2int(new_key, key_str);
				Encode(new_cipher, new_key);
				string new_cipher_str = int2binstr(new_cipher);
				for (int j = 0; j < 128; j++) {
					if (new_cipher_str[j] != cipher_str[j])
						count++;
				}
				sum += count;
				cout << "密钥改变第" << i << "位，密文改变了"<<dec << count << "位" << endl;
				if (key_str[i] == '0')
					key_str[i] = '1';
				else
					key_str[i] = '0';
			}
			avg = double(sum) / 8.0;
			cout << "平均改变位数为：" << avg << endl;
			break;
		}
		else continue;
	}
	system("pause");
	return 0;
}
