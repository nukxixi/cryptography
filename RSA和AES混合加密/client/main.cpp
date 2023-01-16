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
	::cout << "请输入RSA公钥 n :" << endl;
	n.getBigInt(32);
	::cout <<endl<< "请输入RSA公钥 e :" << endl;
	e.getBigInt(16);

	::cout << endl << "AES加密密钥为：" << endl;
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
	::cout << endl << "对会话密钥进行加密..." << endl;
	BigInt a;
	a.getNewBigInt(key);
	BigInt c = PowerMode(a, e, n);
	::cout << "会话密钥加密结果为：" << endl;
	c.display();

	::cout <<endl<< "===========================================================" << endl;
	::cout << "服务器ip : 127.0.0.1" << endl;
	::cout << "端口号：6000" << endl;
	WSADATA wsaData;    // 用于接收Windows Socket的结构信息
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		::cout << "  WSAStartup Failed." << endl;
		return -1;
	}
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);//创建SOCKET，与远程主机相连
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET; //协议簇（TCP/IP）
	serverAddr.sin_addr.S_un.S_addr = inet_addr(serverIp.c_str());//服务器地址
	serverAddr.sin_port = htons(PORT);//端口号
	connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR));//连接服务器

	::cout << "发送加密后的会话密钥：" ;
	cin.ignore();
	string msg1;
	getline(cin, msg1);
	msg1.append(" ");
	send(clientSocket, msg1.c_str(), 2000, 0);
	::cout << "成功发送加密后的会话密钥!" << endl;
	::cout << "===========================================================" << endl;

	DWORD WINAPI receiveThread(LPVOID IpParameter);
	DWORD WINAPI sendThread(LPVOID IpParameter);
	HANDLE sThread = CreateThread(NULL, 0, sendThread, NULL, 0, NULL);
	HANDLE rThread = CreateThread(NULL, 0, receiveThread, NULL, 0, NULL);
	WaitForSingleObject(sThread, INFINITE);  // 等待线程结束  
	WaitForSingleObject(rThread, INFINITE);  // 等待线程结束  
	return 0;
}

DWORD WINAPI receiveThread(LPVOID IpParameter) //接收线程
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

			string all_plain = "【server】:";
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

DWORD WINAPI sendThread(LPVOID IpParameter) //发送线程
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
			//数组转为string
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
		::cout << "发送成功!" << endl;
	}
	return 0;
}