#pragma once

#include "itf/IHttpClient.hpp"

class HttpClient : public IHttpClient
{
public:
	std::string get(const std::string&) const override;
};
