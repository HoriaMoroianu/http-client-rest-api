// Copyright (c) 2024 Horia-Valentin MOROIANU

#include <bits/stdc++.h>
#include "requests.h"
using namespace std;

string compute_get_request(const string &host, const string &url,
						   const string &access_token, const string &cookie)
{
	string message = "";
	message += "GET " + url + " HTTP/1.1\r\n";
	message += "Host: " + host + "\r\n";

	if (!access_token.empty())
		message += "Authorization: Bearer " + access_token + "\r\n";

	if (!cookie.empty())
		message += "Cookie: " + cookie + "\r\n";

	message += "\r\n";
	return message;
}

string compute_post_request(const string &host, const string &url,
							const string &access_token,
							const string &body_data)
{
	string message = "";
	message += "POST " + url + " HTTP/1.1\r\n";
	message += "Host: " + host + "\r\n";

	if (!access_token.empty())
		message += "Authorization: Bearer " + access_token + "\r\n";

	message += "Content-Type: application/json\r\n";
	message += "Content-Length: " + to_string(body_data.length()) + "\r\n";
	message += "\r\n" + body_data + "\r\n";

	return message;
}

string compute_delete_request(const string &host, const string &url,
							  const string &access_token)
{
	string message = "";
	message += "DELETE " + url + " HTTP/1.1\r\n";
	message += "Host: " + host + "\r\n";
	message += "Authorization: Bearer " + access_token + "\r\n";
	message += "\r\n";

	return message;
}
