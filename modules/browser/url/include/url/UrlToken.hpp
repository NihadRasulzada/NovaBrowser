#pragma once
#include <string>

namespace Browser::Url {
	enum class UrlTokenType {
		Scheme,
		Username,
		Password,
		Host,
		Port,
		Path,
		Query,
		Fragment,
		End
	};

	struct UrlToken {
		UrlTokenType Type;
		std::string Value;
		//std::size_t Start;
		//std::size_t Length;
	};
}