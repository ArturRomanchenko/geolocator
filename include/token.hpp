#ifndef TOKEN_HPP
#define TOKEN_HPP

#pragma once 

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <json.hpp>

class TokenConfig {
public:
    static TokenConfig& getInstance() {
        static TokenConfig instance;
        return instance;
    }

    const nlohmann::json& getJsonData() const {
        return json_data;
    }

private:
    nlohmann::json json_data;

    TokenConfig() {
        std::ifstream file("../telegram_token.json");
        if (!file.is_open()) {
            throw std::runtime_error("Could not open the file!");
        }

        try {
            file >> json_data;  // Parsing JSON data from a file
        } catch (const nlohmann::json::parse_error& ex) {
            throw std::runtime_error("Parse error: " + std::string(ex.what()));
        }
    }

    TokenConfig(const TokenConfig&) = delete;
    TokenConfig& operator=(const TokenConfig&) = delete;
};

#endif // TOKEN_HPP