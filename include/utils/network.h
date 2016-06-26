#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdarg.h>

#include <map>
#include <vector>
#include <iostream>
/**
 *	A List of all socket statuses
 */
#define SOCK_CLOSED -1

#include "utils.h"

namespace net {

	int send_all(int _iS, char* in_buf, int* _iLen);

	void sig_child_handler(int s);

	void *get_in_addr(struct sockaddr *sa);

	char* sock_to_string(struct sockaddr_in sa);

	class socket {

	public:

		socket(char* in_port, int sock_type, bool is_server, char* in_delimiter);
		virtual ~socket();

		int get_sock_status();

		void close();
		void restart(char* in_port, int in_sock_type, bool is_server);

		int get_sock();
		int get_numbytes();

		char* get_delimiter();

		struct addrinfo* get_serv_info();

		void set_sock(int new_sockfd);
		void set_numbytes(int new_numbytes);
		void set_serv_info(struct addrinfo* new_serv_info);

	protected:

		int sockfd;
		int number_of_bytes;
		int rv;
		int yes;

		char* delimiter;
		char* buf;
		const char* port;

		struct addrinfo hints;
		struct addrinfo* serv_info;
		struct addrinfo* p;

	private:
		int sock_status;

	};

	class tcp_server {

	public:

		tcp_server(char* in_port, int in_max_backlog, int in_max_clients);
		virtual ~tcp_server();

		void try_recieve();

		void send_to_all(char* in_buf);
		void send_to(char* buf, int sockfd); //Use the Map located below to find IPs

		void accept_clients(uint32 number_of_clients);

		void kick_addr(char* szIP);
		void kick_all();

		char* get_buffer();

		std::vector<char* > ip_list;
		std::map<char*, int> ip_map;

	protected:

	private:

		int max_backlog;
		int max_clients;
		int new_fd;
		int fd_max;

		fd_set master;
		fd_set readfds;

		char cli_addr[INET6_ADDRSTRLEN];
		char* input_buffer;
		char* output_buffer;

		socket sock;

		socklen_t addr_len, sin_size;

		struct sigaction sa;

		struct sockaddr_storage saCliAddr;


	};

	class tcp_client {

	public:

		virtual ~tcp_client();

		void recieve();
		void send(char* in_buf);

		void change_server(char* in_ip);

	protected:

	private:

		char* ip;
		socket sock;
	};

	class udp_server : socket {

	public:

		udp_server(char* in_port) :
			net::socket(in_port, SOCK_DGRAM, true, (char *) '\n') {};
		~udp_server();

		bool listen();
	protected:

	private:

	};

	class udp_client : socket {

	public:

		udp_client(char* in_ip, char* in_port) :
			net::socket(in_port, SOCK_DGRAM, false, (char *) '\n') {};
		~udp_client();

		bool talk(char* in_buf);
	protected:

	private:

	};
};
#endif
