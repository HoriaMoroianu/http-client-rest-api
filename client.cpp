// Copyright (c) 2024 Horia-Valentin MOROIANU

#include <bits/stdc++.h>
#include <string>
#include <iostream>

#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>

#include "helpers.h"
#include "requests.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

#define STATUS_CREATED 201

const string server_host = "34.246.184.49";
const uint16_t server_port = 8080;

string fetch_server_response(string &message);
void register_handle(void);
int extract_status_code(string &response);

int main(void)
{
	while (true) {
		string user_input;
		getline(cin, user_input);

		if (user_input == "register") {
			register_handle();
			continue;
		}


		if (user_input == "exit")
			break;
	}

	return 0;
}

string fetch_server_response(string &message)
{
	int sockfd = open_connection(server_host.data(), server_port, 
								 AF_INET, SOCK_STREAM, 0);

	send_to_server(sockfd, message.data());
	char *recv = receive_from_server(sockfd);
	close_connection(sockfd);

	string response = recv;
	free(recv);
	return response;
}

int extract_status_code(string &response)
{
	string header = "HTTP/1.1 ";
	int header_pos = response.find(header);
	return stoi(response.substr(header_pos + header.length(), 3));
}

void register_handle(void)
{
	cout << "username=";
	string username;
	getline(cin, username);

	if (username.find(' ') != username.npos) {
		cout << "Error: No spaces allowed in usernames.\n";
		return;
	}

	cout << "password=";
	string password;
	getline(cin, password);

	if (password.find(' ') != password.npos) {
		cout << "Error: No spaces allowed in passwords.\n";
		return;
	}

	json data = {
		{ "username", username },
		{ "password", password }
	};

	string message = compute_post_request(server_host,
										  "/api/v1/tema/auth/register",
										  data.dump(4),
										  vector<string>());

	string response = fetch_server_response(message);
	int status_code = extract_status_code(response);

	if (status_code != STATUS_CREATED) {
		cout << "Server Error: Username already taken.\n";
		return;
	}
	cout << "Success: Registration complete.\n";
}
