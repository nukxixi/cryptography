#include "des.h"
#include <iostream>
#include <string>

int main()
{
	std::cout << "请选择：1.加密   2.解密  3.改变明文  4.改变密钥  5.退出" << endl;
	int m;
	std::cin >> m;
	string plain, cipher, key;
	if (m == 1)
	{
		std::cout << "请输入明文:";
		std::cin >> plain;
		std::cout << "请输入密钥:";
		std::cin >> key;
		DES des = DES();
		des.getKey(key);
		cipher = des.encrypt(plain);
		std::cout << "密文为: " << cipher << endl;
	}
	else if (m == 2)
	{
		std::cout << "请输入密文:";
		std::cin >> cipher;
		std::cout << "请输入密钥:";
		std::cin >> key;
		DES des = DES();
		des.getKey(key);
		plain = des.decrypt(cipher);
		std::cout << "明文为: " << plain << endl;
	}
	else if (m == 3)
	{
		int sum = 0;
		int avg = 0;
		int change = 0;
		std::cout << "请输入明文:";
		std::cin >> plain;
		std::cout << "请输入密钥:";
		std::cin >> key;
		DES des = DES();
		des.getKey(key);
		cipher = des.encrypt(plain);
		std::cout << "密文为: " << cipher << endl;
		int plain_bin[64], cipher_bin[64], new_cipher_bin[64];
		string new_plain, new_cipher;
		getBin(plain, plain_bin);
		getBin(cipher, cipher_bin);
		for (int i = 0; i < 64; i++) {
			change = 0;
			plain_bin[i] = !plain_bin[i];
			getHex(plain_bin, new_plain);
			new_cipher=des.encrypt(new_plain);
			getBin(new_cipher, new_cipher_bin);
			for (int j = 0; j < 64; j++) {
				if (cipher_bin[j] != new_cipher_bin[j])change++;
			}
			std::cout << "明文改变第" << i+1 << "位，引发密文改变" << change << "位" << endl;
			sum += change;
			plain_bin[i] = !plain_bin[i];
		}
		std::cout << endl << "平均值为：" << double(sum) / 64.00 << endl;
	}
	else if (m == 4)
	{
		int sum = 0;
		int avg = 0;
		int change = 0;
		std::cout << "请输入明文:";
		std::cin >> plain;
		std::cout << "请输入密钥:";
		std::cin >> key;
		DES des = DES();
		des.getKey(key);
		cipher = des.encrypt(plain);
		std::cout << "密文为 " << cipher << endl;
		int key_bin[64], cipher_bin[64],  new_cipher_bin[64];
		string new_key, new_cipher;
		getBin(key, key_bin);
		getBin(cipher, cipher_bin);
		for (int i = 0; i < 64 ; i++) {
			if ((i + 1) % 8 == 0)
				continue;
			change = 0;
			key_bin[i] = !key_bin[i];
			getHex(key_bin, new_key);
			des.getKey(new_key);
			new_cipher = des.encrypt(plain);
			getBin(new_cipher, new_cipher_bin);
			for (int j = 0; j < 64; j++) {
				if (cipher_bin[j] != new_cipher_bin[j]) change++;
			}
			std::cout << "密钥改变第" << i + 1 << "位，引发密文改变" << change << "位" << endl;
			sum += change;
			key_bin[i] = !key_bin[i];
		}
		std::cout << endl << "平均值为：" << double(sum) / 56.00 << endl;
	}
	system("pause");
	return 0;
}