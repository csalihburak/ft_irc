#include "Command.hpp"

void Command::notify(vector<string>&words, Client &cli, Server &serv, string &opt) {
	vector<Channel*> allChannels;
	string message;
	(void)opt;
	Server::client_iterator it;
	Server::channel_iterator ct;
	Channel::chnlUsersit cit;
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
						for(cit = (*ct)->users.begin(); cit != (*ct)->users.end(); cit++) {
							message = ":" + cli.nickName + " NOTICE " + (*ct)->channelName + " :" + test + "\r\n";
							if (cli.nickName != (*cit).first->nickName)
								(*cit).first->write(message);
						}
						return;
					}
				}
				cli.write(":ircserv 404 " + cli.nickName + " " + words[1] + " :User not in the channel!\r\n");
				return;
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
				message = ":" + cli.nickName + " NOTICE " + words[1] + " :" + test + "\r\n";
				it->second->write(message);
				break;
			}
		}
		if (it == clients.end()) {
			message = ":ircserv 401 " + cli.nickName +" :Recipient not found\r\n";
			cli.write(message);
		}
	}
}