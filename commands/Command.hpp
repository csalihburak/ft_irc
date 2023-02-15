#pragma once

#include "../server.hpp"
#include "../channel.hpp"
#include "../client.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;

class Server;

class Command {
    private:
        string command;
    public:
		Command();
		Command(const char *);
        Command(std::string &);
		~Command();
        string parse(Server &);

		// commands
		string privmsg(vector<string>&, Server &, Client &);
		string join(vector<string>&, Server &);
		//string ping(vector<string>&);
		string welcomemsg(void);
		//void list(vector<string>&);
};