#include "url/UrlParser.hpp"
#include "url/UrlLexer.hpp"
#include <algorithm>
#include <cctype>
#include <charconv>
#include <url/Url.hpp>

namespace Browser::Url {

	Scheme UrlParser::SchemeFromString(std::string scheme) {
		std::transform(scheme.begin(), scheme.end(), scheme.begin(),
			[](unsigned char c) { return static_cast<char>(std::tolower(c)); });

		if (scheme == "http")  return Scheme::Http;
		if (scheme == "https") return Scheme::Https;
		if (scheme == "file")  return Scheme::File;
		if (scheme == "ftp")   return Scheme::Ftp;
		if (scheme == "ws")    return Scheme::Ws;
		if (scheme == "wss")   return Scheme::Wss;
		return Scheme::Unknown;
	}

	std::optional<Url> UrlParser::Parse(const std::string& input) {
		UrlLexer lexer(input);
		const std::vector<UrlToken> tokens = lexer.Tokenize();

		Url url;

		for (const UrlToken& token : tokens) {
			switch (token.Type) {
			case UrlTokenType::Scheme: {
				const Scheme scheme = SchemeFromString(token.Value);
				if (scheme == Scheme::Unknown) {
					return std::nullopt; 
				}
				url.SetScheme(scheme);
				break;
			}
			case UrlTokenType::Username:
				url.SetUsername(token.Value);
				break;

			case UrlTokenType::Password:
				url.SetPassword(token.Value);
				break;

			case UrlTokenType::Host:
				if (token.Value.empty()) {
					return std::nullopt; 
				}
				url.SetHost(token.Value);
				break;

			case UrlTokenType::Port: {
				uint16_t port = 0;
				const char* begin = token.Value.data();
				const char* end = token.Value.data() + token.Value.size();
				const auto result = std::from_chars(begin, end, port);
				if (result.ec != std::errc() || result.ptr != end) {
					return std::nullopt; 
				}
				url.SetPort(port);
				break;
			}

			case UrlTokenType::Path:
				url.SetPath(token.Value.empty() ? "/" : token.Value);
				break;

			case UrlTokenType::Query:
				url.SetQuery(token.Value);
				break;

			case UrlTokenType::Fragment:
				url.SetFragment(token.Value);
				break;

			case UrlTokenType::End:
				break;
			}
		}

		if (url.GetHost().empty()) {
			return std::nullopt; 
		}

		return url;
	}
}