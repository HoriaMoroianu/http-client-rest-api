// Copyright (c) 2024 Horia-Valentin MOROIANU

#ifndef _CLIENT_
#define _CLIENT_

#include <bits/stdc++.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

#define STATUS_OK 200
#define STATUS_CREATED 201
#define STATUS_NOT_FOUND 404
#define STATUS_FORBIDDEN 403

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

#endif
