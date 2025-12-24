#include <windows.h>
#include <winhttp.h>
#include <iostream>
#include <vector>
#include "HttpClient.hpp"

#pragma comment(lib, "winhttp.lib")

std::string HttpClient::get(const std::string& url) const
{
    std::string response;

    URL_COMPONENTS urlComp{};
    urlComp.dwStructSize = sizeof(urlComp);

    wchar_t host[256]{};
    wchar_t path[1024]{};
    urlComp.lpszHostName = host;
    urlComp.dwHostNameLength = sizeof(host) / sizeof(host[0]);
    urlComp.lpszUrlPath = path;
    urlComp.dwUrlPathLength = sizeof(path) / sizeof(path[0]);

    std::wstring urlW(url.begin(), url.end());
    if (!WinHttpCrackUrl(urlW.c_str(), urlW.length(), 0, &urlComp)) {
        std::cerr << "Failed to parse URL\n";
        return response;
    }

    HINTERNET hSession = WinHttpOpen(L"SteamPriceChecker/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
        std::cerr << "WinHttpOpen failed\n";
        return response;
    }

    HINTERNET hConnect = WinHttpConnect(hSession, host,
        urlComp.nPort, 0);
    if (!hConnect) {
        std::cerr << "WinHttpConnect failed\n";
        WinHttpCloseHandle(hSession);
        return response;
    }

    DWORD flags = (urlComp.nScheme == INTERNET_SCHEME_HTTPS) ? WINHTTP_FLAG_SECURE : 0;
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET",
        path,
        NULL, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        flags);
    if (!hRequest) {
        std::cerr << "WinHttpOpenRequest failed\n";
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return response;
    }

    // Send request
    if (!WinHttpSendRequest(hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        WINHTTP_NO_REQUEST_DATA, 0,
        0, 0) ||
        !WinHttpReceiveResponse(hRequest, NULL)) {
        std::cerr << "Steam API request failed\n";
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return response;
    }

    // Read response
    DWORD bytesAvailable = 0;
    while (WinHttpQueryDataAvailable(hRequest, &bytesAvailable) && bytesAvailable > 0) {
        std::vector<char> buffer(bytesAvailable);
        DWORD bytesRead = 0;
        if (WinHttpReadData(hRequest, buffer.data(), bytesAvailable, &bytesRead)) {
            response.append(buffer.data(), bytesRead);
        }
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return response;
}