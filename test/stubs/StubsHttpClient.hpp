#pragma once

#include "itf/IHttpClient.hpp"

class StubCorrectHttpClient : public IHttpClient
{
public:
    std::string get(const std::string&) const override
    {
        return R"(
        {
          "specials": {
            "items": [
              {
                "name": "Hollow Knight: Silksong",
                "original_price": 5999,
                "final_price": 2999,
                "discount_percent": 50,
                "currency": "EUR"
              },
              {
                "name": "Game B",
                "original_price": 4000,
                "final_price": 2000,
                "discount_percent": 50,
                "currency": "EUR"
              }
            ]
          }
        })";
    }
};

class StubDiscardedDataHttpClient : public IHttpClient
{
public:
    std::string get(const std::string&) const override
    {
        return "";
    }
};

class StubWithoutSpecialFieldHttpClient : public IHttpClient
{
public:
    std::string get(const std::string&) const override
    {
        return R"(
        {
          "items": [
            {
                "name": "Hollow Knight: Silksong",
                "original_price": 5999,
                "final_price": 2999,
                "discount_percent": 50,
                "currency": "EUR"
            }
          ]
        })";
    }
};

class StubWithoutItemsFieldHttpClient : public IHttpClient
{
public:
    std::string get(const std::string&) const override
    {
        return R"(
        {
          "specials": {
            "name": "Hollow Knight: Silksong",
            "original_price": 5999,
            "final_price": 2999,
            "discount_percent": 50,
            "currency": "EUR"
          }
        })";
    }
};