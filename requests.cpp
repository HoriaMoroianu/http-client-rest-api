// Copyright (c) 2024 Horia-Valentin MOROIANU

#include <bits/stdc++.h>
#include "requests.h"

using namespace std;

string compute_get_request(const string &host, const string &url,
						   const string &query_params,
						   const string &access_token,
						   const vector<string> &cookies)
{
	string message = "";

	if (!query_params.empty())
		message += "GET " + url + "?" + query_params + " HTTP/1.1\r\n";
	else
		message += "GET " + url + " HTTP/1.1\r\n";

	message += "Host: " + host + "\r\n";

	if (!access_token.empty())
		message += "Authorization: Bearer " + access_token + "\r\n";

	if (!cookies.empty()) {
		message += "Cookie: ";
		for (size_t i = 0; i < cookies.size(); i++) {
			if (i < cookies.size() - 1)
				message += cookies[i] + "; ";
			else
				message += cookies[i] + "\r\n";
		}
	}

	message += "\r\n";
	return message;
}

string compute_post_request(const string &host, const string &url,
							const string &access_token,
							const string &body_data,
							const vector<string> &cookies)
{
	string message = "";
	message += "POST " + url + " HTTP/1.1\r\n";
	message += "Host: " + host + "\r\n";

	if (!access_token.empty())
		message += "Authorization: Bearer " + access_token + "\r\n";

	message += "Content-Type: application/json\r\n";
	message += "Content-Length: " + to_string(body_data.length()) + "\r\n";

	if (!cookies.empty()) {
		message += "Cookie: ";
		for (size_t i = 0; i < cookies.size(); i++) {
			if (i < cookies.size() - 1)
				message += cookies[i] + "; ";
			else
				message += cookies[i] + "\r\n";
		}
	}

	message += "\r\n" + body_data + "\r\n";
	return message;
}
