#include "Command.hpp"

string Command::mergeMessage(vector<string>& words)
{
	int i;
	std::string result;

	i = 0;
    for (std::vector<std::string>::const_iterator it = words.begin(); it != words.end(); ++it) {
        if (it != words.end() && i > 1) {
            result += words[i];
			if (it != words.end() - 1)
				result += " ";
        }
		i++;
    }
    return result;
}

string Command::privmsg(vector<string>& words, Server &serv, Client &cli) {
	vector<Channel*> allChannels;
	string message;
	Server::client_iterator it;
	Server::channel_iterator ct;
	Channel::chnlUsersit cit;
	map<int, Client *> clients;
	
	clients = serv.getClients();
	allChannels = serv.getChannel();
	if (words[1].empty()) {
		message = ":ircserv 411 " + cli.nickName +" :Recipient not given\r\n";
		cli.write(message);
	}
	if (words[1].find('#') == 0) {
		
		for(ct = allChannels.begin(); ct != allChannels.end(); ct++) {
			if ((*ct)->channelName == words[1]) {
				if (std::find((*ct)->bannedUsrs.begin(), (*ct)->bannedUsrs.end(), cli.nickName) != (*ct)->bannedUsrs.end()) {
					message = ":ircserv " + cli.nickName + " " + (*ct)->channelName + " :Cannot send message to channel (+b)\r\n";
					cli.write(message);
					return message;
				}
				string test;

				test = mergeMessage(words);
				for(unsigned long  i = 0; i < cli.channels.size(); i++) {
					if (words[1] == cli.channels[i]) {
						for(cit = (*ct)->users.begin(); cit != (*ct)->users.end(); cit++) {
							message = ":" + cli.nickName + "!~" + cli.nickName + "@localhost" + " PRIVMSG " + words[1] + " :" + test + "\r\n";
							if (cli.nickName != (*cit).first->nickName)
								(*cit).first->write(message);
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
				message = ":localhost NOTICE " + cli.nickName + " :Your message was delivered to the recipient.\r\n";
				cli.write(message);
				break;
			}
		}
		if (it == clients.end()) {
			message = ":ircserv 401 " + cli.nickName +" :Recipient not found\r\n";
			cli.write(message);
		}
	}
	return "Sa";
}