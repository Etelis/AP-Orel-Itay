#include "Server.h"

Server::Server(int port)throw (const char*) {

}

void Server::start(ClientHandler& ch)throw(const char*){	
}

void Server::stop(){
	t->join();
}

Server::~Server() {
}

