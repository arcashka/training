#include "webServer.h"

#include "TaskManager/TaskManager.h"
#include "TaskManager/Task.h"

#include <WinSock2.h>
#include <string>
#include <iostream>

constexpr int port = 8080;

struct WebServer::Impl {
	Impl() {}
	~Impl() {
		closesocket(listenSocket);
		WSACleanup();
		while (!taskManager.isFinished())
			std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	bool initServer(const int port) {
		WORD wVersionRequested = MAKEWORD(1, 1);
		WSADATA wsaData;
		int error;
		error = WSAStartup(wVersionRequested, &wsaData);
		if (error != 0)
			return false;

		listenSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (listenSocket == 0)
			return false;

		sockaddr_in adr;
		memset((char *)&adr, 0, sizeof(adr));
		adr.sin_family = AF_INET;
		adr.sin_port   = htons(port);
		adr.sin_addr.s_addr = htonl(INADDR_ANY);

		error = bind(listenSocket, (struct sockaddr*)&adr, sizeof(adr));
		if (error == SOCKET_ERROR)
			return false;
	}

	void runMainCycle() {
		while(true)
		{
			int error;
			error = listen(listenSocket, 1);
			if (error != 0)
				continue;

			SOCKET sendDataSocket;
			sendDataSocket = accept(listenSocket, nullptr, nullptr);
			if (sendDataSocket == INVALID_SOCKET)
				continue;

			taskManager.addTask(createTask([](SOCKET socket){
									int error;
									char buf[1024];
									error = recv(socket, buf, 1024, 0);
									std::string message("Message");
									send(socket, message.data(), message.size(), MSG_DONTROUTE);
									closesocket(socket);
								}, sendDataSocket));
			listen(listenSocket, 1);
			accept(listenSocket, nullptr, nullptr);
		}
	}

private:
	SOCKET listenSocket;
	TaskManager taskManager;
};

WebServer::WebServer(const int port)
	: impl(std::make_unique<WebServer::Impl>())
{
	impl->initServer(port);
	impl->runMainCycle();
}

WebServer::~WebServer()
{
}
