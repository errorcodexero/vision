#include "../../include/utils/network.h"

using namespace std;

namespace net {

	void *get_in_addr(struct sockaddr *sa) {
		if (sa->sa_family == AF_INET) {
			return &(((struct sockaddr_in*)sa)->sin_addr);
		}
		return &(((struct sockaddr_in6*)sa)->sin6_addr);
	}

	int send_all(int s, char* buf, int len) {
		int total = 0;
		int bytes_left = len; //Bug Causes Segfault
		int n;
		while (total < len) {
			n = send(s, buf+total, bytes_left, 0);
			if (n == -1 ) { break; }
			total += n;
			bytes_left -= n;
		}

		len = total;

		return n ==-1?-1:0;
	}

	/**
	 * Not Needed at the moment
	 */

	/*
		void sig_child_handler(int s) {
			// waitpid() might overwrite errno, so we save and restore it:
			int saved_errno = errno;

			while(waitpid(-1, NULL, WNOHANG) > 0);

			errno = saved_errno;
	}*/

	char* sock_to_string(struct sockaddr_in sa) {
		char* szString = (char* ) malloc (sizeof (char) * 24);
		sprintf(szString, "%d.%d.%d.%d\n",
		  int(sa.sin_addr.s_addr&0xFF),
		  int((sa.sin_addr.s_addr&0xFF00)>>8),
		  int((sa.sin_addr.s_addr&0xFF0000)>>16),
		  int((sa.sin_addr.s_addr&0xFF000000)>>24));
		return szString;
	}

	socket::socket(char* in_port, int in_sock_type, bool is_server, char* in_delimiter) {
		//int temp_port;
		//sscanf(in_port, "%d", &temp_port);
		//assert(sscanf(in_port, "%d", temp_port) < 1 || (&temp_port > 65536 || &temp_port <= 0));

		port = in_port;
		buf = '\0';
		number_of_bytes = 0;
		delimiter = in_delimiter;
		yes = 1;

		//assert(_iSockType != SOCK_STREAM && _iSockType != SOCK_DGRAM);

		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = in_sock_type;
		if(is_server)
			hints.ai_flags = AI_PASSIVE;

		if ((rv = getaddrinfo(NULL, port, &hints, &serv_info)) != 0) {
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
			exit(1);
		}
		if (is_server) {
			for(p = serv_info; p != NULL; p = p->ai_next) {
				if ((sockfd = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
					perror("Server: Socket");
					continue;
				}

				if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
					perror("setsockopt");
					exit(1);
				}

				if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
					::close(sockfd);
					perror("Server: Bind");
					continue;
				}

				break;
			}
		} else {

			for(p = serv_info; p != NULL; p = p->ai_next) {
				if ((sockfd = ::socket(p->ai_family, p->ai_socktype,
						p->ai_protocol)) == -1) {
					perror("client: socket");
					continue;
				}
				if (in_sock_type == SOCK_STREAM) {
					if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
						::close(sockfd);
						perror("client: connect");
						continue;
					}
				} else if (in_sock_type == SOCK_DGRAM) {
					//Just so it finished
				} else {
					//Should never make it this far
				}
			}
		}
		if( p == NULL ) {

		}
		sock_status = sockfd;
	}

	void socket::close() {
		::close(sockfd);
		return;
	}

	void socket::restart(char* _port,int _iSockType, bool is_server) {

		//int iTmp = 0;
		//sscanf(_port, "%d", &iTmp);
		//assert(sscanf( _port, "%d", &iTmp) < 1);
		//assert(iTmp > 65535 || iTmp < 1);

		port = _port;
		buf = '\0';
		number_of_bytes = 0;
		yes = 1;
		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = _iSockType;
		if(is_server)
			hints.ai_flags = AI_PASSIVE;

		if ((rv = getaddrinfo(NULL, port, &hints, &serv_info)) != 0) {
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
			exit(1);
		}
		if (is_server) {
			for(p = serv_info; p != NULL; p = p->ai_next) {
				if ((sockfd = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
					return;
					continue;
				}

				if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
					return;
				}

				if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
					::close(sockfd);
					return;
					continue;
				}

				break;
			}
		} else {

			for(p = serv_info; p != NULL; p = p->ai_next) {
				if ((sockfd = ::socket(p->ai_family, p->ai_socktype,
						p->ai_protocol)) == -1) {
					return;
					continue;
				}
				if (_iSockType == SOCK_STREAM) {
					if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
						::close(sockfd);
						perror("client: connect");
						continue;
					}
				} else if (_iSockType == SOCK_DGRAM) {
						//Just so it finished
				} else {
						//Should never make it this far
				}
			}

		}
		sock_status = sockfd;
		return;
	}

	socket::~socket() {
		if (sockfd != -1)
			shutdown(sockfd, 2);
	}

	int socket::get_sock(){
		return sockfd;
	}
	int socket::get_numbytes(){
		return number_of_bytes;
	}

	char* socket::get_delimiter(){
		return delimiter;
	}

	struct addrinfo* socket::get_serv_info(){
		return serv_info;
	}

	void socket::set_sock(int new_sockfd){
		sockfd = new_sockfd;
	}

	void socket::set_numbytes(int new_numbytes){
		number_of_bytes = new_numbytes;
	}

	void socket::set_serv_info(struct addrinfo* new_serv_info){
		serv_info = new_serv_info;
	}

	tcp_server::tcp_server(char* in_port, int in_max_backlog, int in_max_clients)
		: sock(in_port, SOCK_STREAM, true, (char*) '\n') {
		max_backlog = in_max_backlog;
		max_clients = in_max_clients;
		output_buffer = '\0';
		input_buffer = '\0';
		sin_size = 0;
		fd_max = max_clients;
		//net::socket ;

		char* szIP;

		//clock_t start;
		//double duration;

		//start = clock();

		freeaddrinfo(sock.get_serv_info());

		if (listen(sock.get_sock(), max_clients) == -1) {

			perror("Listen");
			exit(1);
		}

		FD_SET(sock.get_sock(), &master);

		fd_max = sock.get_sock();
		readfds = master;
		if(select(fd_max+1, &readfds, NULL, NULL, NULL) == -1) {
			perror("select");
			exit(4);
		}
		//fd_max = max_clients;
		for (int i = 0; i <= fd_max; i++) {
			if (FD_ISSET(i, &readfds)) {
				if (i == sock.get_sock()) {
					cout <<"Ping!\n";
					addr_len = sizeof saCliAddr;
					new_fd = accept(sock.get_sock(), (struct sockaddr *)&saCliAddr, &addr_len);
					cout << "Que?\n";
					printf("Server: new connection from %s on socket %d\n", inet_ntop(saCliAddr.ss_family, get_in_addr((struct sockaddr *)&saCliAddr),cli_addr, INET6_ADDRSTRLEN), new_fd);
					if (new_fd == -1)
						perror("accept");
					else {
						cout << "Else\n";
						FD_SET(new_fd, &master);
						if (new_fd > fd_max) {
							fd_max = new_fd;
						}
						szIP = (char *) inet_ntop(saCliAddr.ss_family, get_in_addr((struct sockaddr*)&saCliAddr), cli_addr, INET_ADDRSTRLEN);
						ip_list.push_back(szIP);
						ip_map[szIP] = i;
	#ifdef DEBUG
						//printf("Server: new connection from % s on socket %d\n", inet_ntop(saCliAddr.ss_family, get_in_addr((struct sockaddr *)&this.saCliAddr),cli_addr, INET6_ADDRSTRLEN), new_fd);
	#endif
					}
				}
			}
		}
	}




	tcp_server::~tcp_server() {
		cout << "What double free?\n";
		//~socket();
		for (int i = 0; i <= fd_max; i++) {
			if (FD_ISSET(i, &master)) {
				if (i != new_fd && i != -1)
					shutdown(i, 2);
			}
		}

		if (new_fd != -1)
				shutdown(new_fd, 2);
	}

	void tcp_server::send_to_all(char* in_buf) {

		output_buffer = in_buf;
		for (int i = 0; i <= fd_max; i++) {
			if (FD_ISSET(i, &master)) {
				if(i != sock.get_sock()) {
					if (send_all(i, output_buffer, (int) strlen(output_buffer)) == -1) {
						perror("Server: Send");
					}
				}
			}
		}
	}

	void tcp_server::send_to(char* in_buf, int iSock) {
		//output_buffer = in_buf;
		send_all(iSock, in_buf, (int) strlen(in_buf));
	}

	void tcp_server::try_recieve() {
		char* buf = '\0';
		for (int i = 0; i <= fd_max; i++){
			do {
				sock.set_numbytes(recv(i, buf, 1, 0));
				if (sock.get_numbytes() == -1) {
					if (sock.get_numbytes() == 0) {
	#ifdef DEBUG
						printf("Server: socket %d hung up\n", i);
	#endif
					} else {
						perror("recv");
					}
					::close(i); // bye!
					FD_CLR(i, &master); // remove from master set
				}
				sprintf(input_buffer, "%s%s", input_buffer, buf);
			} while (strcmp(buf, sock.get_delimiter()) != 0);
		}
	}


	void tcp_server::accept_clients(uint32 _iMoreClients) {
		//fd_max += _iMoreClients;
		char* szIP;

		if (listen(sock.get_sock(), max_clients) == -1) {

			perror("Listen");
			exit(1);
		}

		FD_SET(sock.get_sock(), &master);

		fd_max = sock.get_sock();
		readfds = master;
		if(select(fd_max+1, &readfds, NULL, NULL, NULL) == -1) {
			perror("select");
			exit(4);
		}
		for (int i = 0; i <= fd_max; i++) {
			if (FD_ISSET(i, &readfds)) {
				if (i == sock.get_sock()) {
					addr_len = sizeof saCliAddr;
					new_fd = accept(sock.get_sock(), (struct sockaddr *)&saCliAddr, &addr_len);
					printf("Server: new connection from %s on socket %d\n", inet_ntop(saCliAddr.ss_family, get_in_addr((struct sockaddr *)&saCliAddr),cli_addr, INET6_ADDRSTRLEN), new_fd);
					if (new_fd == -1)
						perror("accept");
					else {
						FD_SET(new_fd, &master);
						if (new_fd > fd_max) {
							fd_max = new_fd;
						}
						szIP = (char *) inet_ntop(saCliAddr.ss_family, get_in_addr((struct sockaddr*)&saCliAddr), cli_addr, INET_ADDRSTRLEN);
						ip_list.push_back(szIP);
						ip_map[szIP] = i;
						//printf("Server: new connection from % s on socket %d\n", inet_ntop(saCliAddr.ss_family, get_in_addr((struct sockaddr *)&this.saCliAddr),cli_addr, INET6_ADDRSTRLEN), new_fd);
					}
				}
			}
		}
	}

	void tcp_server::kick_addr(char* _szIP) {
		int iSock = ip_map[_szIP];
		shutdown(iSock, 2);
	}

	void tcp_server::kick_all() {
		for (int i = 0; i <= fd_max; i++) {
			shutdown(i, 2);
		}
	}
};
