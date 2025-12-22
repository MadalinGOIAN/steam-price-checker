#pragma once

#include <string>

class IHttpClient
{
public:
	virtual std::string get(const std::string&) const = 0;
	virtual ~IHttpClient() = default;
};
