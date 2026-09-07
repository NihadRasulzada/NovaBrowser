#pragma once
#include "Url.hpp"
#include "UrlToken.hpp"

#include <optional>
#include <string>
#include <vector>

namespace Browser::Url {

	class UrlParser {
	public:
		static std::optional<Url> Parse(const std::vector<UrlToken>& tokens);

	private:
		static Scheme SchemeFromString(std::string scheme);
	};
}