# ifndef IRC_HPP
# define IRC_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/select.h>

const int MAX_BUFFER_SIZE = 1024;
const int MAX_CLIENTS = FD_SETSIZE - 1;
const int MAX_CHANNELS = 1023;

class Client {
public:
	int socket;
	int indice;
	int temp_pass;
	std::string nickname;
	std::string username;
};

class Channel {
public:
	int index;
	int limit;
	int invite_only;
	int topic_mode;
	int key_mode;
	int limit_mode;
	std::vector<int> users_sockets;
	std::vector<std::string> admin_users;
	std::string name;
	std::string topic;
	std::string PRVIMSG_Index;
	std::string password;
};

int channelExist(const int clientSocket,Channel *channels,const Client *clients, std::string channel, const int i);
void channelNotExist(const int clientSocket,Channel *channels,const Client *clients, std::string channel, const int i, int *channel_index);
void kickUser(Channel *channels,Client *clients, std::string channelname, std::string user, const int i);
void modeOptions(Channel *channels, Client *clients, std::string channel,std::string args,std::string msg, const int i);
void modeNoOptions(Channel *channels, Client *clients, std::string channel,std::string args, const int i);
void inviteUser(const int clientSocket,Channel *channels,const Client *clients, std::string channel, const int i);
void PartUser(Channel *channels, Client *clients, std::string channelname, std::string user, const int i);

void removeClient(std::vector<int>& users_sockets, int clientSocket);
bool searchIfExist(const std::vector<int>& sockets, const int& clientSocket);
int isAdmin(const std::vector<std::string>& admin_users, const std::string& user);
int searchBySocket(const int &socket, const Client* clients, int numClients);
int searchByUsername(const std::string& target, const Client* clients, int numClients);
int searchBychannelname(const std::string& target, const Channel* channels, int numChannels);
int checkArg(const std::string str,int clientSocket);
void errorUser(const std::string& msg,int  clientSocket);
void sendUser(const std::string& msg, int clientSocket, std::string name);
void error(const std::string& msg);
int numOfAdmins(Channel *channels, Client *clients, int ch_in);
void listChannels(Channel *channels, Client *clients, int ind);
void removeAdmin(Channel *channels, Client *clients, int client_index, int channel_index);
int checkUserChannel(Channel *channels,const Client *clients, std::string user, std::string channel, int clientSocket);
int ifWord(const std::string str);
void erase_spaces(std::string &str);
std::vector<std::string> split_str(std::string str, char delim);
std::string getMsg(std::string& str);
void user_channels(Channel *channels, Client *clients, int cl_in, int clientSocket);
void sendToAdmins(Channel *channels, Client *clients, int ch_in, std::string msg);

#endif