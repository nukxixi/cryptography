#include<iostream>
#include<string>
//S?? 
int S[16][16] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};
//S?е????û??? 
int r_S[16][16] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};
int rC[10] = {
	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36
};
int confuseMatrix1[4][4] = {
	2,3,1,1,
	1,2,3,1,
	1,1,2,3,
	3,1,1,2
};

int confuseMatrix2[4][4] = {
	14,11,13,9,
	9,14,11,13,
	13,9,14,11,
	11,13,9,14
};

int key[4][4] = { 0 };
//int key[4][4] = {
//	43,126,21,22,40,174,210,166,171,247,21,136,9,207,79,60
//};
int last_cipher[4][4] = { 0 };
int plain_text[4][4] = { 0 };
int temp_text[4][4] = { 0 };


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

//٤???????ϵĳ˷?
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

//??Կ??չ
void KeyExpansion(int key[4][4], int w[11][4][4])
{
	for (int i = 0; i < 4; ++i)//??key????w[0]??
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

//?ֽڴ???
void ByteSub1(int a[4][4]) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//?ֽڵĸ???λ??Ϊ?к?,????λ??Ϊ?к?,??S??????ȡ
			a[i][j] = S[a[i][j] >> 4][a[i][j] & 0x0F];
		}
	}
}
void ByteSub2(int a[4][4]) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//?ֽڵĸ???λ??Ϊ?к?,????λ??Ϊ?к?,??r_S??????ȡ
			a[i][j] = r_S[a[i][j] >> 4][a[i][j] & 0x0F];
		}
	}
}

//????λ
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

//???????ˣ?ע???˷??ͼӷ???????٤???????Ͻ??е?
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

//?л???
void MixColumn1(int a[4][4])
{
	matrixMul(confuseMatrix1, a);
}
void MixColumn2(int a[4][4])
{
	matrixMul(confuseMatrix2, a);
}


//??Կ??
void AddRoundKey(int a[4][4], int key[4][4])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			a[i][j] ^= key[j][i];
		}
	}
}

/*
//????
void Encode(int cipher[4][4], int key[4][4])
{
	int subKey[11][4][4];
	//??????????Կ
	KeyExpansion(key, subKey);
	//һ????Կ??
	AddRoundKey(cipher, subKey[0]);
	for (int i = 1; i <= 10; ++i)
	{
		ByteSub1(cipher);//?ֽڴ???
		ShiftRow1(cipher);//????λ?任
		if (i != 10) MixColumn1(cipher); //?л??ϱ任??ĩβ??û???л??ϱ任
		AddRoundKey(cipher, subKey[i]); //??Կ??
	}
}
//????
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
}*/

//????
void Encode(int cipher[4][4], int key[4][4])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cipher[i][j] ^= last_cipher[i][j];
		}
	}
	int subKey[11][4][4];
	//??????????Կ
	KeyExpansion(key, subKey);
	//һ????Կ??
	AddRoundKey(cipher, subKey[0]);
	for (int i = 1; i <= 10; ++i)
	{
		ByteSub1(cipher);//?ֽڴ???
		ShiftRow1(cipher);//????λ?任
		if (i != 10) MixColumn1(cipher); //?л??ϱ任??ĩβ??û???л??ϱ任
		AddRoundKey(cipher, subKey[i]); //??Կ??
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			last_cipher[i][j] = cipher[i][j];
		}
	}
}
//????
void Decode(int plain[4][4], int key[4][4])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp_text[i][j] = plain[i][j];
		}
	}
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
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			plain[i][j] ^= plain_text[i][j];
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			plain_text[i][j] = temp_text[i][j];
		}
	}
}