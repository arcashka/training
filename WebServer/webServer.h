#include <memory>

class WebServer
{
public:
	WebServer(const int port);
	~WebServer();

private:
	struct Impl;
	std::unique_ptr<WebServer::Impl> impl;
};
