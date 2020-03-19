
#include <iostream>

#define  _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include<WS2tcpip.h>


#include <regex>
#pragma comment(lib,"ws2_32.lib")

using namespace std;


bool checkValidURL(string url) {

	//Xac dinh xem dung ten mien hay chưa
	string pattern = "(?:[a-z0-9](?:[a-z0-9-]{0,61}[a-z0-9])?\.)+[a-z0-9][a-z0-9-]{0,61}[a-z0-9]";

	regex url_regex(pattern);

	if (regex_match(url, url_regex) == true) return true;

	else {
		return false;
	}

}

int main() {

	//khoi tao thu vien
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	sockaddr_in addr;
	addrinfo* info;

	//Nhap vao ten mien tu ban phim
	string tmp;
	cin >> tmp;

	if (checkValidURL(tmp) == true) {
		cout << "Ten mien hop le" << endl;
	}
	else {
		cout << "Ten mien khong hop le";
		return 0;
	}

	const char* url = tmp.c_str(); // convert tu string  sang const* char 
	int ret = getaddrinfo(url, "http", NULL, &info);
	if (ret == 0) {
		memcpy(&addr, info->ai_addr, info->ai_addrlen);
		cout << "Phan giai thanh cong" << endl;
		cout << "Dia chi IP la:  " << inet_ntoa(addr.sin_addr) << endl;//inet_ntoa 
	}
	else cout << "Phan giai dia chi  khong thanh cong " << endl;

	return 1;


}



