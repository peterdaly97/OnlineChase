#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <vector>
#pragma comment(lib, "ws2_32.lib")

class Client
{
public:
	Client(std::string ip, int port);
	~Client();
	bool run();
	void receive();
	void sendMessage(std::string message);

	SOCKET sock;
	sockaddr_in hint;

	std::string ipAddress;
	int port;

	char buf[4096];
	std::string returnMessage = "";

	std::vector<float> posUpdate;

	int number = 0;

	bool enemyJoin = false;

	bool gameOver = false;

	bool restart = false;

	bool win = false;
private:
	
};
#endif // !CLIENT_H

