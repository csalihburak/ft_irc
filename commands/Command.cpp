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

string Command::welcomemsg() {
	string welcome;
	welcome.append("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
	welcome.append("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
	welcome.append("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
	welcome.append("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
	welcome.append("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
	welcome.append(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\r\n");
	return (welcome);
};

//string modif = ":" + cli->nickName + "!~" + cli->nickName + "@localhost" + " PRIVMSG " + words[1] + " :" + words[2] + "\n";
//

string Command::parse(Server &serv) {

    Client *cli = serv.getClient();
    std::stringstream ss(command);
    string word;
    vector<string> words;
    
    while (ss.good() && ss >> word)
        words.push_back(word);
    if (cli->is_avl) {
        if (cli->nickName.empty()) {
            cout << "please provide a nickname";
        }
        else if(cli->userName.empty())
            cout << "please provide a username";
    }
    if (!words[24].empty() && words[24] == "NICK") { //special for colloquy
        cli->nickName = words[25];
        cli->userName = words[27];
        string s = ":" + words[25] +  " 001 :Welcome to localhost!\n";
        cli->write(s);
        cli->write(welcomemsg());
    }
    if (words[0] == ("NICK") || words[0] == ("nick")) {
        cli->nickName = words[1];
    } else if (words[0] == "USER" || words[0] == "user") {
        cli->userName = words[1];
    }else if (words[0] == ("PRIVMSG") || words[0] == ("privmsg")){
        //privmsg(words);
    } else if (words[0] == ("JOIN") || words[0] == ("join")) {
        join(words, serv);
    } else if (words[0] == ("PING") || words[0] == ("ping")) {
        //ping(words);
    } else if (words[0] == ("LIST") || words[0] == ("list")) {
        //list(words);
    } else if (words[0] == ("QUIT") || words[0] == ("quit")) {
        //list(words);
    }
    return word; 
}