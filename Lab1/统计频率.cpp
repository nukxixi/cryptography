#include<iostream>
using namespace std;

int main() {
	char* text = new char[1000];
	cin.getline(text, 1000);
	
	int* count = new int[27];
	for (int i = 0; i < 26; i++) {
		count[i] = 0;
	}
	int sum = 0;
	double* frequency = new double[27];
	for (int i = 0; i < strlen(text); i++) {
		if (text[i] > 64 && text[i] < 91) {
			count[text[i] - 'A']++;
		}
	}
	for (int i = 0; i < 26; i++) {
		sum += count[i];
	}
	for (int i = 0; i < 26; i++) {
		frequency[i] =1.0* count[i] / sum;
	}
	for (int i = 0; i < 26; i++) {
		cout << (char)(i + 'A') << "  " << frequency[i] << endl;
	}
	return 0;
}