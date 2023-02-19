#include "Command.hpp"

void Command::me(Client *cli)
{
    string nick = "Nickname: " + cli->nickName;
    string username = "Username: " + cli->userName;
    vector<string> channels = cli->channels;
    string cha = "channels: ";
    for (unsigned long i = 0; i < channels.size(); i++) {
        cha.append(channels[i] + " ");
    }
    string message = ":bot!~bot@localhost PRIVMSG "+  cli->nickName + " :" +  nick + " || "  + username +  " || " + cha + "\r\n";
    cli->write(message);
}