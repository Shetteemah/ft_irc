#include "irc.hpp"

void removeClient(std::vector<int>& users_sockets, int clientSocket)
{
	std::vector<int>::iterator it = std::find(users_sockets.begin(), users_sockets.end(), clientSocket);
	if (it != users_sockets.end()) {
		users_sockets.erase(it);
	}
}

void removeAdmin(Channel *channels, Client *clients, int client_index, int channel_index)
{
	for (int i = 0 ; i < channels[channel_index].admin_users.size(); i++)
	{
		if (strcmp(channels[channel_index].admin_users[i].c_str(), clients[client_index].username.c_str()) == 0)
		{
			channels[channel_index].admin_users.erase(channels[channel_index].admin_users.begin() + i);
		}
	}
}


void kickUser(Channel *channels, Client *clients, std::string channelname, std::string user, const int i)
{
	int ch_ind = searchBychannelname(channelname, channels, MAX_CHANNELS);////////////i don't know why this Fuc****g Function return -1 in this case
	int cl_ind = searchByUsername(user, clients, MAX_CLIENTS);
	if (ch_ind == -1)
		errorUser(channelname + ": CHANNEL NOT FOUND", clients[i].socket);
	else if (cl_ind == -1)
		errorUser(user + ": USER NOT FOUND", clients[i].socket);
	else if (isAdmin(channels[ch_ind].admin_users, clients[i].username))
	{
		std::string msgPrompt;
		if (user == clients[i].username)
			msgPrompt = "You Quit " + channels[ch_ind].name;
		else{
			msgPrompt = "You've been Kicked OUT by " + clients[i].username + " From " + channels[ch_ind].name;

		}
		sendUser(msgPrompt, clients[cl_ind].socket, clients[cl_ind].nickname);
		if(isAdmin(channels[ch_ind].admin_users, clients[cl_ind].username))
			removeAdmin(channels, clients, cl_ind, ch_ind);
		removeClient(channels[ch_ind].users_sockets, clients[cl_ind].socket);
	}
	else
	{
		sendUser("You're not Allowed to do this Action", clients[i].socket, clients[i].nickname);
	}
}

void PartUser(Channel *channels, Client *clients, std::string channelname, std::string user, const int i)
{
	int ch_ind = searchBychannelname(channelname, channels, MAX_CHANNELS);////////////i don't know why this Fuc****g Function return -1 in this case
	int cl_ind = searchByUsername(user, clients, MAX_CLIENTS);
	if (ch_ind == -1)
		errorUser(channelname + ": CHANNEL NOT FOUND", clients[i].socket);
	else if (cl_ind == -1)
		errorUser(user + ": USER NOT FOUND", clients[i].socket);
	else if (searchIfExist(channels[ch_ind].users_sockets, clients[cl_ind].socket))
	{
		std::string msgPrompt;
		if (user == clients[i].username)
			msgPrompt = "You Quit " + channels[ch_ind].name;
		else{
			msgPrompt = "You've been Kicked OUT by " + clients[i].username + " From " + channels[ch_ind].name;

		}
		sendUser(msgPrompt, clients[cl_ind].socket, clients[cl_ind].nickname);
		if(isAdmin(channels[ch_ind].admin_users, clients[cl_ind].username))
			removeAdmin(channels, clients, cl_ind, ch_ind);
		removeClient(channels[ch_ind].users_sockets, clients[cl_ind].socket);
	}
	else
	{
		sendUser("You're not Allowed to do this Action", clients[i].socket, clients[i].nickname);
	}
}
