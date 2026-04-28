//AI
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>
#include "curl/curl.h"


size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
std::string post(const std::string& url, const std::string& jsonBody);
std::string get(const std::string& url);