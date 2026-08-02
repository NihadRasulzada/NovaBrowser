#pragma once
#include "Url.hpp"
#include "UrlToken.hpp"

#include <optional>
#include <string>

namespace Browser::Url {

	class UrlParser {
	public:
		static std::optional<Url> Parse(const std::string& input);

	private:
		static Scheme SchemeFromString(std::string scheme);
	};
}