/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <cstring>
#include "commands.h"
#include "CLI.h"


using namespace std;

class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};


class SocketIO : public DefaultIO {
    int socketID;
public:
    SocketIO(int n) {
        this->socketID = n;
    }
    string read() override {
        string input = "";
        char buffer = 0;
        while (buffer != '\n') {
            recv(socketID, &buffer, 1, 0);
            input += buffer;
        }
        return input;
    }
    void read(float* f) override {
        recv(socketID, f, sizeof(float), 0);
    }
    void write(string text) override{
        send(socketID, &text[0], text.length(), 0);
    }
    void write(float f) override{
        string text = to_string(f);
        send(socketID, &text[0], text.length(), 0);
    }
};


class AnomalyDetectionHandler:public ClientHandler{
	public:
    virtual void handle(int clientID){
        SocketIO io(clientID);
        CLI cli(&io);
        cli.start();
    }
};

class Server {
        thread* t; // the thread to run the start() method in
public:
    int serverFD;
    struct sockaddr_in address;

	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */
