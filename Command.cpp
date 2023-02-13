#include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;


Command::Command(const char *) {

}

Command::Command() {
    this->command = nullptr;
}


Command::Command(string &cmd) {
    this->command = cmd;
}

Command::~Command() {}


string Command::parse() {
    std::stringstream ss(command);
    string word;
    vector<string> words;
    while (ss.good() && ss >> word) {
        words.push_back(word);
    }
    if (command.find("NICK ") != -1 || command.find("nick ")) {
        return nick(words);
    } else if (command.find("PRIVMSG ") != -1 || command.find("privmsg ") != -1){
        return privmsg(words);
    } else if (command.find("JOIN ") != -1 || command.find("join ") != -1) {

    } else if (command.find("PING ") != -1 || command.find("ping ") != -1) {

    } else if (command.find("JOIN ") != -1 || command.find("join ") != -1) {

    } 
    return word; 
}