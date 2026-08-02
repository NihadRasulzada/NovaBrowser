#include <iostream>
#include <string>
#include <optional>

#include "../../modules/url/include/url/Url.hpp"
#include "../../modules/url/include/url/UrlLexer.hpp"
#include "../../modules/url/include/url/UrlParser.hpp"

using namespace Browser::Url;

namespace {

    std::string SchemeToString(Scheme s) {
        switch (s) {
        case Scheme::Http:  return "http";
        case Scheme::Https: return "https";
        case Scheme::File:  return "file";
        case Scheme::Ftp:   return "ftp";
        case Scheme::Ws:    return "ws";
        case Scheme::Wss:   return "wss";
        default:            return "unknown";
        }
    }

    std::string TokenTypeToString(UrlTokenType type) {
        switch (type) {
        case UrlTokenType::Scheme:    return "Scheme";
        case UrlTokenType::Username:  return "Username";
        case UrlTokenType::Password:  return "Password";
        case UrlTokenType::Host:      return "Host";
        case UrlTokenType::Port:      return "Port";
        case UrlTokenType::Path:      return "Path";
        case UrlTokenType::Query:     return "Query";
        case UrlTokenType::Fragment:  return "Fragment";
        case UrlTokenType::End:       return "End";
        default:                      return "Unknown";
        }
    }

}

int main() {
    while (true) {
        std::string input;

        std::cout << "\nURL (exit yaz cixmaq ucun): ";
        std::getline(std::cin, input);

        if (input == "exit")
            break;

        std::cout << "\n========== LEXER ==========\n";

        UrlLexer lexer(input);
        auto tokens = lexer.Tokenize();

        for (const auto& token : tokens) {
            std::cout
                << TokenTypeToString(token.Type)
                << " -> \"" << token.Value << "\"\n";
        }

        std::cout << "\n========== PARSER ==========\n";

        std::optional<Url> parsed = UrlParser::Parse(tokens);

        if (!parsed) {
            std::cout << "Parse FAILED\n";
            continue;
        }

        const Url& url = *parsed;

        std::cout << "Scheme   : " << SchemeToString(url.GetScheme()) << '\n';
        std::cout << "Username : " << url.GetUsername() << '\n';
        std::cout << "Password : " << url.GetPassword() << '\n';
        std::cout << "Host     : " << url.GetHost() << '\n';

        if (url.HasPort())
            std::cout << "Port     : " << url.GetPort() << '\n';
        else
            std::cout << "Port     : -\n";

        std::cout << "Path     : " << url.GetPath() << '\n';
        std::cout << "Query    : " << url.GetQuery() << '\n';
        std::cout << "Fragment : " << url.GetFragment() << '\n';

        std::cout << "\nToString : " << url.ToString() << '\n';
    }

    return 0;
}