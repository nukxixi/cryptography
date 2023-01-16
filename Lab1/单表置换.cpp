#include<iostream>
#include<map>
#include<windows.h>
using namespace std;

map<char, char>displace_table;
int letters[26] = { 0 };

void getKey(char keytext[], char key[]) {
	int m = 0;
	for (int i = 0; i < strlen(keytext); i++) {
		if (keytext[i] > 64 && keytext[i] < 91) {
			if (letters[keytext[i] - 'A'] == 0) {
				key[m] = keytext[i];
				letters[key[m] - 'A'] = 1;
				m++;
			}
			else continue;
		}
		else if (keytext[i] > 96 && keytext[i] < 123) {
			if (letters[keytext[i] - 32 - 'A'] == 0) {
				key[m] = keytext[i] - 32;
				letters[key[m] - 'A'] = 1;
				m++;
			}
			else continue;
		}
	}
	key[m] = '\0';
}

void getTable(char key[], map<char, char>& displace_table, int letters[]) {
	for (int i = 0; i < strlen(key); i++) {
		displace_table.insert(pair<char, char>('A' + i, key[i]));
	}
	if (displace_table.size() < 26) {
		int j = displace_table.size();
		for (int i = 0; i < 26; i++) {
			if (letters[i] == 0) {
				displace_table.insert(pair<char, char>('A' + j, 'A' + i));
				j++;
			}
		}
	}
}

void printTable(map<char, char>& displace_table) {
	cout << "置换表如下：" << endl;
	map<char, char>::iterator iter;
	for (iter = displace_table.begin(); iter != displace_table.end(); iter++) {
		cout << iter->first << "  " << iter->second << endl;
	}
}

void getCipher(char plain[], char cipher[], map<char, char>& displace_table) {
	for (int i = 0; i < strlen(plain); i++) {
		if (plain[i] > 64 && plain[i] < 91) {
			cipher[i] = displace_table[plain[i]];
		}
		else if (plain[i] > 96 && plain[i] < 123) {
			cipher[i] = displace_table[plain[i] - 32] + 32;
		}
		else
		{
			cipher[i] = plain[i];
		}
	}
	cipher[strlen(plain)] = '\0';
}

int main() {
	char* keytext = new char[1000];
	char* key = new char[27];
	char* plain = new char[1000];
	char* cipher = new char[1000];

	cout << "请输入密钥，重复部分将被删除：" << endl;
	cin.getline(keytext, 1000);

	getKey(keytext, key);
	getTable(key, displace_table, letters);
	printTable(displace_table);

	cout << "请输入明文：" << endl;
	cin.getline(plain, 1000);
	getCipher(plain, cipher, displace_table);
	cout << "密文为：" << cipher;
	system("pause");
	//return 0;
}