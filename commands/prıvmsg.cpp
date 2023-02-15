#include "Command.hpp"

string Command::privmsg(vector<string>& words, Server &serv, Client &cli) {
	vector<Channel*> allChannels;
	string massage; //mesaj mergelanacak
	Server::client_iterator it;
	Server::channel_iterator ct;
	map<int, Client *> clients = serv.getClients();

	allChannels = serv.getChannel();
	if (words[1].empty()) {
		massage = ":ircserv 411 " + cli.nickName +" :Recipient not given\r\n";
		cli.write(massage);
	}
	if (words[1].find('#') == 0) {
		
		for(ct = allChannels.begin(); ct != allChannels.end(); ct++) {
			if ((*ct)->channelName == words[1]) {
				for(unsigned long  i = 0; i < cli.channels.size(); i++) {
					if (words[1] == cli.channels[i]) {
						for(unsigned long  i = 0; i < (*ct)->users.size() - 1; i++) {
							massage = ":" + cli.nickName + "!~" + cli.nickName + "@localhost" + " PRIVMSG " + words[1] + " :" + words[2] + "\r\n";
							if (cli.nickName != (*ct)->users[i]->nickName)
								(*ct)->users[i]->write(massage);
						}
						return (words[0]);
					}
				}
				cli.write(":ircserv 404 " + cli.nickName + " " + words[1] + " :User not in the channel!\r\n");
			}
		}
		if (ct == allChannels.end()) {
			massage = ":ircserv 411 " + cli.nickName +" :Recipient not found\r\n";
			cli.write(massage);
		}
	} else if (words[1].find('#') != 0) {
		
	} else {
		for (it = clients.begin(); it != clients.end(); it++) {
				//MESAJIN İLK KISMI GİDİYOR WHİLE İLE YAPILACAK
			if (it->second->nickName == words[1]) {
				massage = ":" + cli.nickName + "!~" + cli.nickName + "@localhost" + " PRIVMSG " + words[1] + " :" + words[2] + "\r\n";
				it->second->write(massage);
				break;
			}
		}
		if (it == clients.end()) {
			massage = ":ircserv 411 " + cli.nickName +" :Recipient not found\r\n";
			cli.write(massage);
		}
	}
	return "Sa";
}