#include <iostream>  
#include <string>  
#include <cstring>  
#include <vector>  
#include <iterator>  
#include <algorithm>  
#include <Winsock2.h>  
#include <Windows.h>  
#include"BigInt.h"
#include"GenPrime.h"
#include"AES.h"
using namespace std;
#pragma comment(lib,"ws2_32.lib")   //����socket��̬���ӿ�

int PORT=6000;//�������˿ں�
SOCKET clientSocket; //�û�socket

int main() {
	::cout << "===========================================================" << endl;
	::cout << "**************************server***************************" << endl;
	::cout << "===========================================================" << endl;
	::cout << "����RSA��Կ��˽Կ..." << endl;
	::cout << "��һ�������� p :" << endl;
	//���ɴ�����p
	BigInt p = GeneratePrime();
	p.display();
	::cout << endl;
	//���ɴ�����q
	::cout << "�ڶ��������� q :" << endl;
	BigInt q = GeneratePrime();
	q.display();
	::cout << endl;
	::cout << "��Կ n = p * q Ϊ��" << endl;
	BigInt n = p * q;
	n.display();
	::cout << endl;
	//��ŷ������
	BigInt t = (p - 1) * (q - 1);
	//eΪ����Կ
	BigInt e;
	//dΪ��Կ����eģt�ĳ˷���Ԫ
	BigInt d;
	//y���ڲ�����չŷ��������㣬�洢tģe�ĳ˷���Ԫ
	BigInt y;
	BigInt temp;
	while (1)
	{
		//������t���ʵ�e
		e.Random();
		while (!(Gcd(e, t) == 1))
		{
			e.Random();
		}
		//����չŷ������㷨���eģt�ĳ˷���Ԫ
		temp = ExtendedGcd(e, t, d, y);
		break;
	}
	::cout << "��Կ e �� " << endl;
	e.display();
	::cout << endl;
	::cout << "˽Կ d �� " << endl;
	d.display();
	::cout << endl;

	::cout << "===========================================================" << endl;
	::cout << "������ip : 127.0.0.1" << endl;
	::cout << "�˿ںţ�6000" << endl;
	WSADATA wsaData;//��ȡ�汾��Ϣ
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{ //����SOCKET�⣬ʧ���˳�
		::cout << "[ INFO    ] WSAStartup Failed." << endl;
		return -1;
	}
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);//����SOCKET(��ַ���ͣ��������ͣ�Э�飩
	//����ַ�󶨵�SOCKET
	SOCKADDR_IN serverAddr; //sockaddr_in�׽��ֽṹ��
	serverAddr.sin_family = AF_INET; //Э��أ�TCP/IP��
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//��������ַ
	serverAddr.sin_port = htons(PORT);//�˿ں�
	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));//�󶨵�ָ����socket
	//��ʼ����ģʽ
	if (listen(serverSocket, 20) != 0)
	{
		::cout << "[ INFO    ] Listen Failed." << endl;
		return -1;
	}
	::cout << "������..." << endl;
	clientSocket = accept(serverSocket, NULL, NULL);
	::cout << "�ɹ����ӵ��ͻ��ˣ�" << endl;

	char buf[2000];
	if (recv(clientSocket, buf, 2000, 0) > 0) {
		::cout << "���յ����ܺ�ĻỰ��ԿΪ: "<<endl;
		//::cout <<endl<< strlen(buf) << endl;
		for (int i = 0; i < strlen(buf); i++)
		{
			::cout << buf[i];
		}
		::cout << endl;
	}

	BigInt c;
	char_to_bigint(buf, c);
	::cout << "ʹ��˽Կ�ԻỰ��Կ���н���..." << endl;
	BigInt m = PowerMode(c, d, n);
	int s = 15;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			key[j][i] = m.data[s];
			s--;
		}
	}
	::cout << "���ܺ�ĻỰ��ԿΪ��";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (key[j][i] < 16)::cout << "0";
			::cout <<hex<< key[j][i]<<dec << " ";
		}
	}
	::cout << "������ɣ����Է�����Ϣ��~" << endl;
	::cout << "===========================================================" << endl;

	//�̺߳��������
	DWORD WINAPI sendThread(LPVOID IpParameter);
	DWORD WINAPI receiveThread(LPVOID IpParameter);
	HANDLE rThread = CreateThread(NULL, 0, receiveThread, (LPVOID)clientSocket, 0, NULL);
	HANDLE sThread = CreateThread(NULL, 0, sendThread, NULL, 0, NULL);//���������̣߳�ֻ��һ��

	WaitForSingleObject(sThread, INFINITE);  // �ȴ��߳̽���  
	WaitForSingleObject(rThread, INFINITE);  // �ȴ��߳̽���  

	CloseHandle(sThread); //�رշ��ͽ���
	closesocket(serverSocket);
	WSACleanup();   // ��ֹ���׽��ֿ��ʹ�� 
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

DWORD WINAPI receiveThread(LPVOID IpParameter) //�����߳�
{
	SOCKET ClientSocket = (SOCKET)(LPVOID)IpParameter;
	while (1)
	{
		char buf[2000];
		if (recv(ClientSocket, buf, 2000, 0) > 0) {
			string s1 = string(buf);
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
			string all_plain = "��client��:";
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

