#include<iostream>
using namespace std;
void shift_decryption(char cipher[], char plain[]) {
	for (int j = 1; j < 26; j++) {
		cout << "密钥：" << j << "   明文为：";
		for (int i = 0; i < strlen(cipher); i++) {
			if (cipher[i] > 64 && cipher[i] < 91) {
				plain[i] = cipher[i] - j;
				if (plain[i] < 65) {
					plain[i] = plain[i] + 26;
				}
			}
			else if (cipher[i] > 96 && cipher[i] < 123) {
				plain[i] = cipher[i] - j;
				if (plain[i] < 97) {
					plain[i] = plain[i] + 26;
				}
			}
			else plain[i] = cipher[i];
		}
		plain[strlen(cipher)] = '\0';
		cout << plain << endl;
	}
}

int main() {
	char* plain = new char[1000];
	char* cipher = new char[1000];
	cout << "请输入密文：" << endl;
	cin.getline(cipher, 1000);
	shift_decryption(cipher, plain);
}