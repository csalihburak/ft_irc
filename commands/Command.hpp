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

		string privmsg(vector<string>&, Server &, Client &);
		string join(vector<string>&, Server &);
		void part(vector<string>&, Server &, Client &);
		void list(vector<string> &, Server &);
		static void quit(int, Server &);
		//void who(vector<string>&, Server &);
		void commands(vector<string>&, Server &, Client *);
		int checks(Server &, vector<string> &, Client *);
		void colloquy(vector<string> &, Client *);
		string mergeMessage(vector<string>& words);
		string welcomemsg(void);
};