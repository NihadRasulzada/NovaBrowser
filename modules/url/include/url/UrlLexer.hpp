#include <string>
#include <vector>

#include "UrlToken.hpp"

namespace Browser::Url {
	class UrlLexer {
	public:
		explicit UrlLexer(std::string input);
		std::vector<UrlToken> Tokenize();

	private:
		std::string m_input;
		std::size_t m_pos = 0;
		std::vector<UrlToken> m_tokens;

		bool IsEof() const noexcept;
		char Peek() const noexcept;

		std::string_view ReadUntil(std::string_view stopChars) noexcept;

		void LexScheme();
		void LexAuthority();
		void LexPath();
		void LexQuery();
		void LexFragment();

		void EmitAuthorityTokens(std::string_view authority);
	};
}