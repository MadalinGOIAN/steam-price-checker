#pragma once

#include <gmock/gmock.h>
#include "itf/IHttpClient.hpp"

class MockHttpClient : public IHttpClient
{
public:
	MOCK_METHOD(std::string, get, (const std::string&), (const, override));
};
