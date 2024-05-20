// Copyright (c) 2024 Horia-Valentin MOROIANU

#include <bits/stdc++.h>
#include "requests.h"

using namespace std;

string compute_get_request(const string &host, const string &url,
						   const string &query_params,
						   const vector<string> &cookies)
{
	string message = "";

	if (!query_params.empty())
		message += "GET " + url + "?" + query_params + " HTTP/1.1\r\n";
	else
		message += "GET " + url + " HTTP/1.1\r\n";

	message += "Host: " + host + "\r\n";

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
							const string &content_type,
							const vector<string> &body_data,
							const vector<string> &cookies)
{
	string message = "";
	string data = "";

	message += "POST " + url + " HTTP/1.1\r\n";
	message += "Host: " + host + "\r\n";
	message += "Content-Type: " + content_type + "\r\n";

	if (!body_data.empty()) {
		for (size_t i = 0; i < body_data.size(); i++) {
			data += body_data[i];
			if (i < body_data.size() - 1)
				data += "&";
		}
	}
	message += "Content-Length: " + to_string(data.length()) + "\r\n";

	if (!cookies.empty()) {
		message += "Cookie: ";
		for (size_t i = 0; i < cookies.size(); i++) {
			if (i < cookies.size() - 1)
				message += cookies[i] + "; ";
			else
				message += cookies[i] + "\r\n";
		}
	}

	message += "\r\n" + data + "\r\n";
	return message;
}
