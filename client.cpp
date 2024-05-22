// Copyright (c) 2024 Horia-Valentin MOROIANU

#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "helpers.h"
#include "requests.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

#define STATUS_OK 200
#define STATUS_CREATED 201
#define STATUS_NOT_FOUND 404
#define STATUS_FORBIDDEN 403

const string server_host = "34.246.184.49";
const uint16_t server_port = 8080;

string fetch_server_response(string &message);
int get_user_credentials(string &username, string &password);
int get_book_info(json &book_info);

int extract_status_code(string &response);
json extract_json_data(string &response);
string extract_cookie(string &response);

void register_command(void);
void login_command(string &login_cookie, string &library_access_token);
void enter_library_command(string &login_cookie, string &library_access_token);
void get_books_command(string &library_access_token);
void get_book_command(string &library_access_token);
void add_book_command(string &library_access_token);
void delete_book_command(string &library_access_token);
void logout_command(string &login_cookie, string &library_access_token);

int main(void)
{
	string user_input, login_cookie, library_access_token;
	while (true) {
		getline(cin, user_input);

		if (user_input == "register") {
			register_command();
			continue;
		}
		if (user_input == "login") {
			login_command(login_cookie, library_access_token);
			continue;
		}
		if (user_input == "enter_library") {
			enter_library_command(login_cookie, library_access_token);
			continue;
		}
		if (user_input == "get_books") {
			get_books_command(library_access_token);
			continue;
		}
		if (user_input == "get_book") {
			get_book_command(library_access_token);
			continue;
		}
		if (user_input == "add_book") {
			add_book_command(library_access_token);
			continue;
		}
		if (user_input == "delete_book") {
			delete_book_command(library_access_token);
			continue;
		}
		if (user_input == "logout") {
			logout_command(login_cookie, library_access_token);
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
	size_t header_pos = response.find(header);
	return stoi(response.substr(header_pos + header.length(), 3));
}

json extract_json_data(string &response)
{
	size_t data_pos = response.find("[");
	if (data_pos == string::npos)
		data_pos = response.find("{\"");

	if (data_pos == string::npos)
		return json({});

	return json::parse(response.substr(data_pos));
}

string extract_cookie(string &response)
{
	int start_pos = response.find("connect.sid");
	int end_pos = response.substr(start_pos).find(';');
	return response.substr(start_pos, end_pos);
}

int get_user_credentials(string &username, string &password)
{
	cout << "username=";
	getline(cin, username);

	cout << "password=";
	getline(cin, password);

	if (username.empty() || username.find(' ') != username.npos) {
		cout << "Error: Invalid username!\n";
		return 1;
	}

	if (password.empty() || password.find(' ') != password.npos) {
		cout << "Error: Invalid password!\n";
		return 1;
	}
	return 0;
}

int get_book_info(json &book_info)
{
	string title;
	cout << "title=";
	getline(cin, title);

	string author;
	cout << "author=";
	getline(cin, author);

	string genre;
	cout << "genre=";
	getline(cin, genre);

	string publisher;
	cout << "publisher=";
	getline(cin, publisher);

	string page_count;
	cout << "page_count=";
	getline(cin, page_count);

	if (title.empty()) {
		cout << "Error: Invalid title!\n";
		return 1;
	}
	if (author.empty()) {
		cout << "Error: Invalid author!\n";
		return 1;
	}
	if (genre.empty()) {
		cout << "Error: Invalid genre!\n";
		return 1;
	}
	if (publisher.empty()) {
		cout << "Error: Invalid publisher!\n";
		return 1;
	}
	if (page_count.empty() || 
		!all_of(page_count.begin(), page_count.end(), ::isdigit)) {
		cout << "Error: Invalid page_count!\n";
		return 1;
	}

	book_info = {
		{ "title", title },
		{ "author", author },
		{ "genre", genre },
		{ "publisher", publisher },
		{ "page_count", stoi(page_count) }
	};
	return 0;
}

void register_command(void)
{
	string username, password;
	if (get_user_credentials(username, password))
		return;

	json data = {
		{ "username", username },
		{ "password", password }
	};

	string message = compute_post_request(server_host,
										  "/api/v1/tema/auth/register",
										  "",
										  data.dump());

	string response = fetch_server_response(message);
	int status_code = extract_status_code(response);

	if (status_code == STATUS_CREATED) {
		cout << "Success: Registration complete.\n";
		return;
	}

	string error_message = extract_json_data(response)["error"].get<string>();
	cout << "Server Error: " << error_message << "\n";
}

void login_command(string &login_cookie, string &library_access_token)
{
	string username, password;
	if (get_user_credentials(username, password))
		return;
	
	json data = {
		{ "username", username },
		{ "password", password }
	};

	string message = compute_post_request(server_host, 
										  "/api/v1/tema/auth/login",
										  "",
										  data.dump());

	string response = fetch_server_response(message);
	int status_code = extract_status_code(response);

	if (status_code == STATUS_OK) {
		login_cookie = extract_cookie(response);
		library_access_token = "";
		cout << "Success: Logged in successfully.\n";
		return;
	}

	string error_message = extract_json_data(response)["error"].get<string>();
	cout << "Server Error: " << error_message << "\n";
}

void enter_library_command(string &login_cookie, string &library_access_token)
{
	string message = compute_get_request(server_host,
										 "/api/v1/tema/library/access",
										 "",
										 login_cookie);

	string response = fetch_server_response(message);
	int status_code = extract_status_code(response);
	json response_data = extract_json_data(response);

	if (status_code == STATUS_OK) {
		library_access_token = response_data["token"].get<string>();
		cout << "Success: Library access granted.\n";
		return;
	}

	cout << "Server Error: " << response_data["error"].get<string>() << "\n";
}

void get_books_command(string &library_access_token)
{
	string message = compute_get_request(server_host,
										 "/api/v1/tema/library/books",
										 library_access_token,
										 "");

	string response = fetch_server_response(message);
	int status_code = extract_status_code(response);

	if (status_code == STATUS_OK) {
		cout << extract_json_data(response).dump(4) << "\n";
		return;
	}

	cout << "Server Error: Library access denied!\n";
}

void get_book_command(string &library_access_token)
{
	string book_id;
	cout << "id=";
	getline(cin, book_id);

	if (book_id.empty() || 
		!all_of(book_id.begin(), book_id.end(), ::isdigit)) {
		cout << "Error: Invalid book id!\n";
		return;
	}

	string url = "/api/v1/tema/library/books/" + book_id;
	string message = compute_get_request(server_host,
										 url,
										 library_access_token,
										 "");

	string response = fetch_server_response(message);
	int status_code = extract_status_code(response);

	if (status_code == STATUS_OK) {
		cout << extract_json_data(response).dump(4) << "\n";
		return;
	}

	if (status_code == STATUS_NOT_FOUND) {
		cout << "Server Error: No book was found!\n";
		return;
	}
	cout << "Server Error: Library access denied!\n";
}

void add_book_command(string &library_access_token)
{
	json book_info;
	if (get_book_info(book_info))
		return;

	string message = compute_post_request(server_host,
										  "/api/v1/tema/library/books",
										  library_access_token,
										  book_info.dump());

	string response = fetch_server_response(message);
	int status_code = extract_status_code(response);

	if (status_code == STATUS_OK) {
		cout << "Success: Book added to the library.\n";
		return;
	}

	if (status_code == STATUS_FORBIDDEN) {
		cout << "Server Error: Library access denied!\n";
		return;
	}
	cout << "Server Error: Invalid book information!\n";
}

void delete_book_command(string &library_access_token)
{
	string book_id;
	cout << "id=";
	getline(cin, book_id);

	if (book_id.empty() || 
		!all_of(book_id.begin(), book_id.end(), ::isdigit)) {
		cout << "Error: Invalid book id!\n";
		return;
	}

	string url = "/api/v1/tema/library/books/" + book_id;
	string message = compute_delete_request(server_host,
											url,
											library_access_token);

	string response = fetch_server_response(message);
	int status_code = extract_status_code(response);

	if (status_code == STATUS_OK) {
		cout << "Success: Book removed from the library.\n";
		return;
	}

	if (status_code == STATUS_NOT_FOUND) {
		cout << "Server Error: No book was found!\n";
		return;
	}
	cout << "Server Error: Library access denied!\n";
}

void logout_command(string &login_cookie, string &library_access_token)
{
	string message = compute_get_request(server_host,
										 "/api/v1/tema/auth/logout",
										 "",
										 login_cookie);

	string response = fetch_server_response(message);
	int status_code = extract_status_code(response);

	if (status_code == STATUS_OK) {
		login_cookie = "";
		library_access_token = "";
		cout << "Success: User logged out.\n";
		return;
	}

	string error_message = extract_json_data(response)["error"].get<string>();
	cout << "Server Error: " << error_message << "\n";
}
