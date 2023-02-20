#include "Command.hpp"

void sendChannel(vector<string> &words, Client &cli, Server &serv) {
    vector<Channel *> allchannels;
    string message;
    Server::channel_iterator cit;
    Channel::chnlUsersit it;

    message = ":" + cli.nickName + "!~" + cli.nickName + "@localhost" + " PRIVMSG " + words[3] + " :Hellllllooooo teaam my name is " + cli.userName + " and I like icecream. Want to meet?\r\n";
    allchannels = serv.getChannel();
    for (cit = allchannels.begin(); cit != allchannels.end(); cit++) {
        if ((*cit)->channelName == words[3]) {
            for (it = (*cit)->users.begin(); it != (*cit)->users.end(); it++) {      
                if ((*it).first->nickName == cli.nickName)
                    break;
            }
            if (it != (*cit)->users.end()) {
                for (it = (*cit)->users.begin(); it != (*cit)->users.end(); it++)
                    (*it).first->write(message);
                return;
            } else
                cli.write(":ircserv 404 " + cli.nickName + " " + words[1] + " :User not in the channel!\r\n");
        }
    }
    if (cit == allchannels.end()) {
        message = ":ircserv 411 " + cli.nickName +" :Recipient not found\r\n";
		cli.write(message);
    }
}

void    sendUser(vector<string> &words, Client &cli, Server &serv) {
    Server::client_iterator    it;
    string  message;

    message = ":" + cli.nickName + "!~" + cli.nickName + "@localhost" + " PRIVMSG " + words[3] + " :say my name " + cli.userName + " and I want you! ;)\r\n";
    for (it = serv.getClients().begin(); it != serv.getClients().end(); it++) {
        if ((*it).second->nickName == words[3]) {
            (*it).second->write(message);
            return;
        } else {
            cli.write(":ircserv 411 " + cli.nickName + " " + words[1] + " :No such a nickname!\r\n");
        }
    }
}

string Command::agunes() {
    string message;

    message.append(" (            (    (                  )           )           )              )   *                    )            )           ) \r\n");
    message.append(")\\ )   (     )\\ ) )\\ )   (        ( /(  (     ( /(  (     ( /(     (     ( /( (  `        *   )   ( /(  (      ( /(  (     ( /(  \r\n");
    message.append("(()/(   )\\   (()/((()/(   )\\       )\\()) )\\    )\\()) )\\    )\\())    )\\    )\\()))\\))(  (  ` )  /(   )\\()) )\\     )\\()) )\\    )\\())\r\n");
    message.append(" /(_)|(((_)(  /(_))/(_)|(((_)(   |((_)((((_)( ((_)((((_)( ((_)\\  ((((_)( ((_)\\((_)()\\ )\\  ( )(_)) ((_)((((_)( |((_)((((_)( ((_)\\\r\n");
    message.append("(_))  )\\ _ )\\(_)) (_))  )\\ _ )\\  |_ ((_)\\ _ )\\ _((_)\\ _ )\\ _((_)  )\\ _ )\\ _((_|_()((_|(_)(_(_())   _((_)\\ _ )\\|_ ((_)\\ _ )\\ _((_)\r\n");
    message.append("/ __| (_)_\\(_) |  | |   (_)_\\(_) | |/ /(_)_\\(_)_  /(_)_\\(_) \\| |  (_)_\\(_) || |  \\/  | __|_   _|  | || (_)_\\(_) |/ /(_)_\\(_) \\| |\r\n");
    message.append("\\__ \\  / _ \\ | |__| |__  / _ \\     ' <  / _ \\  / /  / _ \\ | .` |   / _ \\ | __ | |\\/| | _|  | |    | __ |/ _ \\   ' <  / _ \\ | .` | \r\n");
    message.append("|___/ /_/ \\_\\|____|____|/_/ \\_\\   _|\\_\\/_/ \\_\\/___|/_/ \\_\\|_|\\_|  /_/ \\_\\|_||_|_|  |_|___| |_|    |_||_/_/ \\_\\ _|\\_\\/_/ \\_\\|_|\\_| \r\n");
    return (message);
}


void Command::bot(vector<string> &words, Client &cli, Server &serv) {

    if (words[1] == "!me") {
        me(cli);
    } else if (words[1] == "!send") {
        if (words[2] == "hello") {
            if ((int)words[3].find("#") != -1) {
                sendChannel(words, cli, serv);
            } else {
                sendUser(words, cli, serv);
            }
        }
    } else if (words[1] == "!whois") {
        whois(words, cli, serv);
    } else if (words[1] == "!agunes") {
        cli.write(agunes());
    } else {
        cli.write(":bot command not found!\r\n");
    }

}