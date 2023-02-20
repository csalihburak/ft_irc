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
		string join(vector<string>&, Server &, Client &);
		void part(vector<string>&, Server &, Client &);
		void list(vector<string> &, Server &);
		static void quit(int, Server &, vector<string> &);
		void me(Client &);
		void topic(vector<string> &, Client &, Server &);
		void nick(vector<string>&, Client &, Server &);
		void notify(vector<string>&, Client &, Server &, string &);
		void ison(vector<string>&, Client &, Server &);
		void mode(vector<string>&, Client &, Server &);
		void kick(vector<string> &, Server &, Client &);
		void kickMessage(Channel const *, Client &, string);
		void commands(vector<string>&, Server &, Client *);
		int checks(Server &, vector<string> &, Client &);
		void colloquy(vector<string> &, Client *);
		string mergeMessage(vector<string>&);
		string welcomemsg(void);
		void bot(vector<string> &, Client &, Server &);
		void whois(vector<string> &, Client &, Server &);
		string agunes();
		int kickCont(vector<string> &, Server &, Client &);
};