#include "Command.hpp"


string merge(vector<string>& words) {
	int i;
	std::string result;

	i = 0;
    for (std::vector<std::string>::const_iterator it = words.begin(); it != words.end(); ++it) {
        if (it != words.end() && i > 0) {
            result += words[i];
			if (it != words.end() - 1)
				result += " ";
        }
		i++;
    }
    return result;
}

void Command::quit(int soc, Server &serv, vector<string> &words) {
    Client *cli;
    vector<string> usrChnls;
    vector<Channel*> allChannels;
    string cmd;
    Server::poll_iterator it;
    Server::channel_iterator ct;
    Server::client_iterator cit;
    Channel::chnlUsersit tic;

    cli = (serv.getClients())[soc];
    if (cli != NULL) {
        usrChnls = cli->getChannels();
        allChannels = serv.getChannel();
        for(it = serv.getPoll().begin(); it != serv.getPoll().end(); it++) {
            if (it->fd == soc)
                break;
        }
        if (it != serv.getPoll().end()) {
            serv.getPoll().erase(it);
            cmd = merge(words);
            for(ct = allChannels.begin(); ct != allChannels.end(); ct++) {
                if (std::find(usrChnls.begin(), usrChnls.end(), (*ct)->channelName) != usrChnls.end()) {
                    serv.notifyAll((*ct), *cli, cmd);
                    for(tic = (*ct)->users.begin(); tic != (*ct)->users.end(); tic++) {
                        if (cli->nickName == (*tic).first->nickName)
                            (*ct)->users.erase(tic);
                            return;
                    }
                }
            }
            close(cli->soc_fd);
        }
    }
}