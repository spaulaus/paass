/** \file poll2_socket.h
  * 
  * \brief Provides network connectivity for poll2
  * 
  * \author Cory R. Thornsberry
  * 
  * \date April 20th, 2015
  * 
  * This file contains classes used by poll2 in order to send packets over the
  * network. These packets are sent by poll using the Server class and may be
  * read by any program using the Client class or operating a socket on the
  * same port.
*/

#ifndef POLL2_SOCKET_H
#define POLL2_SOCKET_H

#include <netinet/in.h>

class Server{
  private:
	int sock, length, n;
	socklen_t fromlen;
	struct sockaddr_in serv;
	struct sockaddr_in from;
	bool init;

  public:
	Server(){ init = false; }
  
	~Server(){ Close(); }

	/** Initialize the serv object and open a specified port. Returns false if the 
	  * socket fails to open or the socket fails to bind and returns true otherwise. */
	bool Init(int port_);

	/** Receive a message from the socket. Returns the number of bytes received. Returns
	  * -1 if the receive fails or if the object was not initialized. */
	int RecvMessage(char *message_, size_t length_);

	/** Send a message to the socket. Returns the number of bytes sent. Returns
	  * -1 if the send fails or if the object was not initialized. */
	int SendMessage(char *message_, size_t length_);

	/// Close the socket.
	void Close();
};

class Client{
  private:
	int sock, n;
	unsigned int length;
	struct sockaddr_in serv, from;
	struct hostent *hp;
	bool init;

  public:
	Client(){ init = false; }
	
	~Client(){ Close(); }
  	
	/** Initialize the client object and open a specified address and port. Returns false 
	  * if the socket fails to open or the address is unresolved and returns true otherwise. */
	bool Init(const char *address_, int port_);

	/** Receive a message from the socket. Returns the number of bytes received. Returns
	  * -1 if the receive fails or if the object was not initialized. */
	int RecvMessage(char *message_, size_t length_);

	/** Send a message to the socket. Returns the number of bytes sent. Returns
	  * -1 if the send fails or if the object was not initialized. */
	int SendMessage(char *message_, size_t length_);
	
	/// Close the socket.
	void Close();
};

#endif
