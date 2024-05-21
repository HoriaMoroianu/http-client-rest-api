// Copyright (c) 2024 Horia-Valentin MOROIANU

#ifndef _REQUESTS_
#define _REQUESTS_

#include <bits/stdc++.h>
using namespace std;

// Computes and returns a GET request string
string compute_get_request(const string &host, const string &url,
						   const string &query_params,
						   const string &access_token,
						   const vector<string> &cookies);

// Computes and returns a POST request string
string compute_post_request(const string &host, const string &url,
							const string &access_token,
							const string &body_data,
							const vector<string> &cookies);

// Computes and returns a DELETE request string
string compute_delete_request(const string &host, const string &url,
							  const string &access_token);

#endif
