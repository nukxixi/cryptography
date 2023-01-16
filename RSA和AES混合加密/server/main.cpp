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
#pragma comment(lib,"ws2_32.lib")   //加载socket动态链接库

int PORT=6000;//服务器端口号
SOCKET clientSocket; //用户socket

int main() {
	::cout << "===========================================================" << endl;
	::cout << "**************************server***************************" << endl;
	::cout << "===========================================================" << endl;
	::cout << "生成RSA公钥和私钥..." << endl;
	::cout << "第一个大素数 p :" << endl;
	//生成大素数p
	BigInt p = GeneratePrime();
	p.display();
	::cout << endl;
	//生成大素数q
	::cout << "第二个大素数 q :" << endl;
	BigInt q = GeneratePrime();
	q.display();
	::cout << endl;
	::cout << "公钥 n = p * q 为：" << endl;
	BigInt n = p * q;
	n.display();
	::cout << endl;
	//求欧拉函数
	BigInt t = (p - 1) * (q - 1);
	//e为公开钥
	BigInt e;
	//d为密钥，即e模t的乘法逆元
	BigInt d;
	//y用于参与扩展欧几里得运算，存储t模e的乘法逆元
	BigInt y;
	BigInt temp;
	while (1)
	{
		//产生与t互质的e
		e.Random();
		while (!(Gcd(e, t) == 1))
		{
			e.Random();
		}
		//用扩展欧几里德算法求出e模t的乘法逆元
		temp = ExtendedGcd(e, t, d, y);
		break;
	}
	::cout << "公钥 e ： " << endl;
	e.display();
	::cout << endl;
	::cout << "私钥 d ： " << endl;
	d.display();
	::cout << endl;

	::cout << "===========================================================" << endl;
	::cout << "服务器ip : 127.0.0.1" << endl;
	::cout << "端口号：6000" << endl;
	WSADATA wsaData;//获取版本信息
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{ //加载SOCKET库，失败退出
		::cout << "[ INFO    ] WSAStartup Failed." << endl;
		return -1;
	}
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);//创建SOCKET(地址类型，服务类型，协议）
	//将地址绑定到SOCKET
	SOCKADDR_IN serverAddr; //sockaddr_in套接字结构体
	serverAddr.sin_family = AF_INET; //协议簇（TCP/IP）
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//服务器地址
	serverAddr.sin_port = htons(PORT);//端口号
	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));//绑定到指定的socket
	//开始监听模式
	if (listen(serverSocket, 20) != 0)
	{
		::cout << "[ INFO    ] Listen Failed." << endl;
		return -1;
	}
	::cout << "监听中..." << endl;
	clientSocket = accept(serverSocket, NULL, NULL);
	::cout << "成功连接到客户端！" << endl;

	char buf[2000];
	if (recv(clientSocket, buf, 2000, 0) > 0) {
		::cout << "接收到加密后的会话密钥为: "<<endl;
		//::cout <<endl<< strlen(buf) << endl;
		for (int i = 0; i < strlen(buf); i++)
		{
			::cout << buf[i];
		}
		::cout << endl;
	}

	BigInt c;
	char_to_bigint(buf, c);
	::cout << "使用私钥对会话密钥进行解密..." << endl;
	BigInt m = PowerMode(c, d, n);
	int s = 15;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			key[j][i] = m.data[s];
			s--;
		}
	}
	::cout << "解密后的会话密钥为：";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (key[j][i] < 16)::cout << "0";
			::cout <<hex<< key[j][i]<<dec << " ";
		}
	}
	::cout << "解密完成！可以发送信息了~" << endl;
	::cout << "===========================================================" << endl;

	//线程函数的入口
	DWORD WINAPI sendThread(LPVOID IpParameter);
	DWORD WINAPI receiveThread(LPVOID IpParameter);
	HANDLE rThread = CreateThread(NULL, 0, receiveThread, (LPVOID)clientSocket, 0, NULL);
	HANDLE sThread = CreateThread(NULL, 0, sendThread, NULL, 0, NULL);//建立发送线程，只有一个

	WaitForSingleObject(sThread, INFINITE);  // 等待线程结束  
	WaitForSingleObject(rThread, INFINITE);  // 等待线程结束  

	CloseHandle(sThread); //关闭发送进程
	closesocket(serverSocket);
	WSACleanup();   // 终止对套接字库的使用 
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

DWORD WINAPI receiveThread(LPVOID IpParameter) //接收线程
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
			string all_plain = "【client】:";
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

