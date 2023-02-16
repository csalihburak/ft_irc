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

void Command::part(vector<string>& words, Server &serv, Client &cli) {
    vector<Channel*> allChannels;
    vector<Client*>::iterator it;
    vector<string> usrChnls;
    string message;
    string cmd;
    Server::channel_iterator ct;

    usrChnls = cli.getChannels();
    allChannels = serv.getChannel();
    cmd = "PART";
    for(ct = allChannels.begin(); ct != allChannels.end(); ct++) {
        if (std::find(usrChnls.begin(), usrChnls.end(), (*ct)->channelName) != usrChnls.end()) {
            for (it = (*ct)->users.begin(); it != (*ct)->users.end(); it++) {
                message =  ":" + cli.nickName + "!~" + cli.userName + "@localhost PART " + (*ct)->channelName + " :(Disconnected)\r\n";
                cout << message << endl;
                (*it)->write(message);
            }
            (*ct)->users.erase(std::find((*ct)->users.begin(), (*ct)->users.end(), &cli));
            break;
        }
    }
    if (ct == allChannels.end()) {
        message = ":ircserv 404 " + cli.nickName + " " + words[1] + " :Not in the channel\r\n";
        cli.write(message);
    }
}

void Command::colloquy(vector<string> &words, Client *cli) {   
    cli->nickName = words[25];
    cli->userName = words[27];
    string s = ":ircserv 001 " +  cli->nickName + " :Welcome to ft_irc server!\r\nPlease enter the password:\r\n";
    cli->is_avl = 2;
    cli->write(s);
}

void Command::commands(vector<string> &words, Server &serv, Client *cli) {
    if (words[0] == ("NICK") || words[0] == ("nick")) {
        cli->nickName = words[1];
    } else if (words[0] == "USER" || words[0] == "user") {
        cli->userName = words[1];
    } else if (words[0] == ("PRIVMSG") || words[0] == ("privmsg")) {
        privmsg(words, serv, *cli);
    } else if (words[0] == ("JOIN") || words[0] == ("join")) {
        join(words, serv);
    } else if (words[0] == ("PING") || words[0] == ("ping")) {
        string rep = "PONG :localhost: " + words[1];
        cli->write(rep);
    } else if (words[0] == ("LIST") || words[0] == ("list")) {
        list(words, serv);
    } else if (words[0] == ("QUIT") || words[0] == ("quit")) {
        cout << "before: " << serv.getClients().size() << endl;
        serv.quit(cli->soc_fd);
        cout << "after: " << serv.getClients().size() << endl;
    }
}

string Command::parse(Server &serv) {

    cout << "ilk: " << serv.getClients().size() << endl;
    Client *cli = serv.getClient();
    std::stringstream ss(command);
    string word;
    vector<string> words;

    while (ss.good() && ss >> word) 
        words.push_back(word);
    if (!words[24].empty() && words[24] == "NICK") { // for colloquy
        colloquy(words, cli);
    } else if (cli->nickName.empty() || cli->userName.empty() || cli->is_avl == 0 || cli->is_avl == 2)// for nc
        checks(serv, words, cli);
    else // other commands
        commands(words, serv, cli);
    return word;
}