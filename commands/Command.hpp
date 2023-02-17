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
		void part(vector<string>&, Server &, Client &);
		//string ping(vector<string>&);
		string welcomemsg(void);
		string mergeMessage(vector<string>& words);
		void list(vector<string> &, Server &);
		void colloquy(vector<string> &, Client *);
		void commands(vector<string>&, Server &, Client *);
		int checks(Server &, vector<string> &, Client *);
		void kick(vector<string> &, Server &, Client &);
		void kickMessage(Channel const *, Client &, string);
};