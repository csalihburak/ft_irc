#pragma once

#include "server.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;

class Command {
    private:
        string command;
    public:
		Command();
		Command(const char *);
        Command(std::string &);
		~Command();
        string parse();

		// commands
		string nick(vector<string> &);
		string privmsg(vector<string>);
};