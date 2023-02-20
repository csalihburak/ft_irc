#include "Command.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;


Command::Command(const char *) {

}



Command::Command() {
    this->command = "";
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


void Command::colloquy(vector<string> &words, Client *cli) {   
    cli->nickName = words[25];
    cli->userName = words[27];
    string s = ":ircserv 001 " +  cli->nickName + " :Welcome to ft_irc server!\r\nPlease enter the password:\r\n";
    cli->is_avl = 2;
    cli->write(s);
}

void help(Client &cli) {
    string message;

    message = ":ircserv 705 " + cli.nickName + "\r\n:'NICK'    command; sets the current user nickname\r\n";
    message.append("'USER'    command; sets the current user username\r\n");
    message.append("'JOIN'    command; Join a channel -if channle not exist creates one-\r\n");
    message.append("'PING'    command; Check the connection with server\r\n");
    message.append("'LIST'    command; List all the channels on the server\r\n");
    message.append("'PART'    command; Leave a channel -with a message or not-\r\n");
    message.append("'QUIT'    command; Close the connection with server\r\n");
    message.append("'KICK'    command; Kicks a user from the channel if user is moderator\r\n");
    message.append("'HELP'    command; Prints this message\r\n");
    message.append("'TOPIC'   command; set or view the topic of the channel\r\n");
    message.append("'NOTICE'  command; Notify the user or the users on the channel\r\n");
    message.append("'PRIVMSG' command; send a message to a client or channel\r\n");
    message.append("'ME'      command; one of the bot commands it send you a message of your informations like user and nickname, channels that you are currently in\r\n");
    cli.write(message);
}


void Command::commands(vector<string> &words, Server &serv, Client *cli) {
    string rep;
    
    if (words[0] == ("NICK") || words[0] == ("nick")) {
        nick(words, *cli, serv);
    } else if (words[0] == "USER" || words[0] == "user") {
        cli->userName = words[1];
    } else if (words[0] == ("PRIVMSG") || words[0] == ("privmsg")) {
        privmsg(words, serv, *cli);
    } else if (words[0] == ("JOIN") || words[0] == ("join")) {
        join(words, serv, *cli);
    } else if (words[0] == ("PING") || words[0] == ("ping")) {
        rep = "PONG :localhost: " + words[1];
        cli->write(rep);
    } else if (words[0] == ("LIST") || words[0] == ("list")) {
        list(words, serv);
    } else if (words[0] == ("PART") || words[0] == ("PART")) {
        part(words, serv, *cli);
    } else if (words[0] == ("QUIT") || words[0] == ("quit")) {
        quit(cli->soc_fd, serv, words);
        serv.getClients().erase(cli->soc_fd);
    } else if (words[0] == ("KICK") || words[0] == ("kick")) {
        kick(words, serv, *cli);
    } else if (words[0] == ("ISON") || words[0] == ("ison")) {
        ison(words, *cli, serv);
    } else if (words[0] == ("NOTICE") || words[0] == ("notice")) {
        notify(words, *cli, serv, rep);
    } else if (words[0] == ("MODE") || words[0] == ("mode")) {
        mode(words, *cli, serv);
    } else if (words[0] == ("TOPIC") || words[0] == ("topic")) {
        topic(words, *cli, serv);
    } else if (words[0] == ("HELP") || words[0] == ("help")) {
        help(*cli);
    } else if (words[0] == ("bot")) {
        bot(words, *cli, serv);
    } else {
        cli->write(":ircserv 403 " + cli->nickName + " :Command not found\r\n");
    }
}

string Command::parse(Server &serv) {

    Client *cli = serv.getClient();
    std::stringstream ss(command);
    string word;
    vector<string> words;
    cout << "cmd: " << command << endl;

    while (ss.good() && ss >> word) 
        words.push_back(word);
    if ((words.size() > 20) && (!words[24].empty() && words[24] == "NICK")) { // for colloquy
        colloquy(words, cli);
    } else if (cli->nickName.empty() || cli->userName.empty() || cli->is_avl == 0 || cli->is_avl == 2)// for nc
        checks(serv, words, *cli);
    else // other commands
        commands(words, serv, cli);
    return word;
}