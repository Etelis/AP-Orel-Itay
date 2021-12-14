#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include "Server.h"

Server::Server(int port)throw (const char*) {

    if (serverFD == 0){
        throw "socket failed";
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(serverFD, (struct sockaddr *) &address, sizeof (address)) < 0){
        throw "bind failed";

    }
    if (listen(serverFD, 3) < 0 ){
        throw "listen failed";
    }

}

void handle_alarm(int) {
    throw "timeout waiting for client";
}

void Server::start(ClientHandler& ch)throw(const char*){
        t = new thread([&ch, this]() {
            while (true) {
                int clientFD;
                socklen_t client_size = sizeof(address);
                signal(SIGALRM, handle_alarm);
                alarm(10);
                clientFD = accept(serverFD, (struct sockaddr *) &client, &client_size);
                if ((clientFD < 0)) {
                    throw "error on accept";
                }
                alarm(0);
                ch.handle(clientFD);
                close(clientFD);
                cout << "disconnecting client" << endl;
            }
        });

}

void Server::stop(){
	t->join(); // do not delete this!
    close(serverFD);
}

Server::~Server() {
}

