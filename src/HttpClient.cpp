#include <curl/curl.h>
#include <iostream>
#include "HttpClient.hpp"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t totalSize = size * nmemb;
    static_cast<std::string*>(userp)->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string HttpClient::get(const std::string& url) const
{
    std::string response{};
    CURL* curl = curl_easy_init();

    if (!curl)
    {
        std::cerr << "Failed to initialize curl\n";
        return response;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (result != CURLE_OK)
    {
        std::cerr << "Steam API request failed\n";
    }

    return response;
}