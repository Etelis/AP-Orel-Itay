
#include "Server.h"

Server::Server(int port)throw (const char*) {
    if ((serverFD = socket(AF_INET, SOCK_STREAM, 0) == 0)){
        throw "socket failed";
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(serverFD, (struct sockaddr *)&address, sizeof (address)) < 0){
        throw "bind failed";

    }
    if (listen(serverFD, 3) < 0 ){
        throw "listen failed";
    }

}

void Server::start(ClientHandler& ch)throw(const char*){
    int clientFD;
    signal( SIGALRM, handle_alarm);
    alarm(10);
    socklen_t client_size = sizeof (address);

    if ((clientFD = accept(serverFD, (struct sockaddr *)&address, &client_size) < 0)){
        throw "error on accept";
    }
    alarm(0);

    t = new thread([&ch, &clientFD](){
        ch.handle(clientFD);
        close(clientFD);
    });

}

void Server::stop(){
	t->join(); // do not delete this!
    close(serverFD);
}

Server::~Server() {
}

