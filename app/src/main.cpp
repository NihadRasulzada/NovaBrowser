#include <iostream>
#include <vector>
#include "../../modules/url/include/url/Url.hpp"
#include "../../modules/url/include/url/UrlParser.hpp"
#include <optional>

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
}

int main() {
	const std::vector<std::string> testUrls = {
		"http://example.com",
		"https://example.com",
		"https://www.example.com",
		"http://example.com/",
		"https://example.org/path",
		"https://example.net/path/to/resource",
		"https://example.com/path?query=value",
		"https://example.com/path#section",
		"https://example.com/path?query=value#section",
		"https://example.com/index.html",
		"http://example.com/a/b/c/d/e",
		"https://example.com/path/",
		"https://example.com/PATH/CaseSensitive",
		"https://example.com/path.with.dots",
		"https://example.com/path-with-dashes_and_underscores",
		"https://user:pass@example.com:8080/secure?x=1#top",
	};

	int failures = 0;

	for (const std::string& raw : testUrls) {
		std::cout << "INPUT : " << raw << "\n";

		std::optional<Url> parsed = UrlParser::Parse(raw);
		if (!parsed) {
			std::cout << "  -> PARSE FAILED\n\n";
			++failures;
			continue;
		}

		const Url& url = *parsed;
		std::cout << "  scheme   : " << SchemeToString(url.GetScheme()) << "\n";
		std::cout << "  username : " << url.GetUsername() << "\n";
		std::cout << "  password : " << url.GetPassword() << "\n";
		std::cout << "  host     : " << url.GetHost() << "\n";
		std::cout << "  port     : " << (url.HasPort() ? std::to_string(url.GetPort()) : "-") << "\n";
		std::cout << "  path     : " << url.GetPath() << "\n";
		std::cout << "  query    : " << url.GetQuery() << "\n";
		std::cout << "  fragment : " << url.GetFragment() << "\n";
		std::cout << "  ToString : " << url.ToString() << "\n";

		const bool roundTripOk = (url.ToString() == raw);
		std::cout << "  ROUND-TRIP MATCH: " << (roundTripOk ? "yes" : "NO (fərqli, amma sema-tik cəhətdən düz ola bilər)") << "\n\n";
	}

	std::cout << (failures == 0 ? "Hamısı parse olundu.\n" : (std::to_string(failures) + " ədəd parse alınmadı.\n"));
	return failures == 0 ? 0 : 1;
}