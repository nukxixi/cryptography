#include <iostream>  
#include <cstdio>  
#include <string>  
#include <cstring>  
#include <winsock2.h>  
#include <Windows.h>  
#include"BigInt.h"
#include"GenPrime.h"
#include"AES.h"
#pragma comment(lib, "ws2_32.lib")
using namespace std;

SOCKET clientSocket;
int PORT=6000;
string serverIp="127.0.0.1";

int main() {
	::cout << "===========================================================" << endl;
	::cout << "**************************client***************************" << endl;
	::cout << "===========================================================" << endl;
	BigInt e;
	BigInt n;
	::cout << "������RSA��Կ n :" << endl;
	n.getBigInt(32);
	::cout <<endl<< "������RSA��Կ e :" << endl;
	e.getBigInt(16);

	::cout << endl << "AES������ԿΪ��" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			key[j][i] = rand() % 255;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (key[j][i] < 16)::cout << "0";
			cout << hex << key[j][i] << dec << " ";
		}
	}
	::cout << endl << "�ԻỰ��Կ���м���..." << endl;
	BigInt a;
	a.getNewBigInt(key);
	BigInt c = PowerMode(a, e, n);
	::cout << "�Ự��Կ���ܽ��Ϊ��" << endl;
	c.display();

	::cout <<endl<< "===========================================================" << endl;
	::cout << "������ip : 127.0.0.1" << endl;
	::cout << "�˿ںţ�6000" << endl;
	WSADATA wsaData;    // ���ڽ���Windows Socket�Ľṹ��Ϣ
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		::cout << "  WSAStartup Failed." << endl;
		return -1;
	}
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);//����SOCKET����Զ����������
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET; //Э��أ�TCP/IP��
	serverAddr.sin_addr.S_un.S_addr = inet_addr(serverIp.c_str());//��������ַ
	serverAddr.sin_port = htons(PORT);//�˿ں�
	connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR));//���ӷ�����

	::cout << "���ͼ��ܺ�ĻỰ��Կ��" ;
	cin.ignore();
	string msg1;
	getline(cin, msg1);
	msg1.append(" ");
	send(clientSocket, msg1.c_str(), 2000, 0);
	::cout << "�ɹ����ͼ��ܺ�ĻỰ��Կ!" << endl;
	::cout << "===========================================================" << endl;

	DWORD WINAPI receiveThread(LPVOID IpParameter);
	DWORD WINAPI sendThread(LPVOID IpParameter);
	HANDLE sThread = CreateThread(NULL, 0, sendThread, NULL, 0, NULL);
	HANDLE rThread = CreateThread(NULL, 0, receiveThread, NULL, 0, NULL);
	WaitForSingleObject(sThread, INFINITE);  // �ȴ��߳̽���  
	WaitForSingleObject(rThread, INFINITE);  // �ȴ��߳̽���  
	return 0;
}

DWORD WINAPI receiveThread(LPVOID IpParameter) //�����߳�
{
	while (1)
	{
		char recvBuf[2000];
		if (recv(clientSocket, recvBuf, 2000, 0) > 0) {
			string s1 = string(recvBuf);
			int m = 0;
			int start = 0;
			int tmp_plain[1000];
			for (int i = 0; i < s1.length(); i++) {
				if (s1[i] == ' ') {
					string tmp = s1.substr(start, i - start);
					int temp = atoi(tmp.c_str());
					tmp_plain[m] = temp;
					m++;
					start = i + 1;
				}
			}

			string all_plain = "��server��:";
			int count = m / 16 + (m % 16 == 0 ? 0 : 1);
			int index = 0;
			for (int i = 0; i < count; i++) {
				int plain[4][4];
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						plain[k][j] = tmp_plain[index];
						index++;
					}
				}
				Decode(plain, key);
				string tmp = "";
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						if (plain[j][i] != ' ') {
							char temp = plain[j][i] + ' ';
							tmp += temp;
						}
					}
				}
				all_plain += tmp;
			}
			::cout <<endl<< all_plain << endl;
		}
	}
	return 0;
}

DWORD WINAPI sendThread(LPVOID IpParameter) //�����߳�
{
	while (1)
	{
		string msg;
		getline(cin, msg);
		msg.append(" ");
		int count = (msg.length() - 1) / 16 + ((msg.length() - 1) % 16 == 0 ? 0 : 1);
		string allmsg = "";
		for (int i = 0; i < count; i++) {
			int cipher[4][4];
			if (i != count - 1) {
				string str = msg.substr(i * 16, 16);
				int m = 0;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						cipher[j][i] = str[m] - ' ';
						m++;
					}
				}
			}
			else {
				string str = msg.substr(i * 16, (msg.length() - 1) % 16);
				int m = 0;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						if (m < str.length()) {
							cipher[j][i] = str[m] - ' ';
							m++;
						}
						else {
							cipher[j][i] = ' ';
							m++;
						}
					}
				}
			}
			Encode(cipher, key);
			//����תΪstring
			string send_msg = "";
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					send_msg += to_string(cipher[j][i]);
					send_msg += ' ';
				}
			}
			allmsg += send_msg;
		}
		send(clientSocket, allmsg.c_str(), 2000, 0);
		::cout << "���ͳɹ�!" << endl;
	}
	return 0;
}