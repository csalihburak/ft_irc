#include "Command.hpp"

string Command::mergeMessage(vector<string>& words) {
    unsigned long i;
    std::string result;
    i = 0;
    if (words[0] == "PRIVMSG")
        i = 2;
    for (;i < words.size(); i++) {
        result.append(words[i]);
        if (i + 1 != words.size())
            result.append(" ");
    }
    return result;
}

string Command::privmsg(vector<string>& words, Server &serv, Client &cli) {
	vector<Channel*> allChannels;
	string message; //mesaj mergelanacak
	Server::client_iterator it;
	Server::channel_iterator ct;
	map<int, Client *> clients = serv.getClients();

	allChannels = serv.getChannel();
	if (words[1].empty()) {
		message = ":ircserv 411 " + cli.nickName +" :Recipient not given\r\n";
		cli.write(message);
	}
	if (words[1].find('#') == 0) {
		
		for(ct = allChannels.begin(); ct != allChannels.end(); ct++) {
			if ((*ct)->channelName == words[1]) {
				string test;

				test = mergeMessage(words);
				for(unsigned long  i = 0; i < cli.channels.size(); i++) {
					if (words[1] == cli.channels[i]) {
						for(unsigned long  i = 0; i < (*ct)->users.size() - 1; i++) {
							message = ":" + cli.nickName + "!~" + cli.userName + "@localhost" + " PRIVMSG " + words[1] + " :" + test + "\r\n";
							if (cli.nickName != (*ct)->users[i]->nickName)
								(*ct)->users[i]->write(message);
						}
						return (words[0]);
					}
				}
				cli.write(":ircserv 404 " + cli.nickName + " " + words[1] + " :User not in the channel!\r\n");
				return (words[0]);
			}
		}
		if (ct == allChannels.end()) {
			message = ":ircserv 411 " + cli.nickName +" :Recipient not found\r\n";
			cli.write(message);
		}
	} else {
		for (it = clients.begin(); it != clients.end(); it++) {
			if (it->second->nickName == words[1]) {
				string test;
				test = mergeMessage(words);
				message = ":" + cli.nickName + "!~" + cli.nickName + "@localhost" + " PRIVMSG " + words[1] + " :" + test + "\r\n";
				it->second->write(message);
				break;
			}
		}
		if (it == clients.end()) {
			message = ":ircserv 411 " + cli.nickName +" :Recipient not found\r\n";
			cli.write(message);
		}
	}
	return "Sa";
}