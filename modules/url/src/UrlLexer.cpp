#include "url/UrlLexer.hpp"

namespace Browser::Url {
	UrlLexer::UrlLexer(std::string input)
		: m_input(std::move(input)) {
	}

	bool UrlLexer::IsEof() const noexcept {
		return m_pos >= m_input.size();
	}

	char UrlLexer::Peek() const noexcept {
		return IsEof() ? '\0' : m_input[m_pos];
	}

	std::vector<UrlToken> UrlLexer::Tokenize() {
		m_tokens.clear();
		m_pos = 0;

		LexScheme();
		LexAuthority();
		LexPath();
		LexQuery();
		LexFragment();

		m_tokens.push_back(UrlToken{ UrlTokenType::End, "" });
		return m_tokens;
	}

	std::string_view UrlLexer::ReadUntil(std::string_view stopChars) noexcept {
		const std::size_t start = m_pos;
		while (!IsEof() && stopChars.find(m_input[m_pos]) == std::string_view::npos) {
			++m_pos;
		}
		return std::string_view(m_input).substr(start, m_pos - start);
	}

	void UrlLexer::LexAuthority() {
		if (Peek() == '/' && m_pos + 1 < m_input.size() && m_input[m_pos + 1] == '/') {
			m_pos += 2; 

			std::string_view authority = ReadUntil("/?#");
			EmitAuthorityTokens(authority);
		}
	}

	void UrlLexer::EmitAuthorityTokens(std::string_view authority) {
		std::string_view userinfo;
		std::string_view hostport = authority;

		const std::size_t atPos = authority.rfind('@');
		if (atPos != std::string_view::npos) {
			userinfo = authority.substr(0, atPos);
			hostport = authority.substr(atPos + 1);
		}

		if (!userinfo.empty()) {
			const std::size_t colonPos = userinfo.find(':');
			if (colonPos != std::string_view::npos) {
				m_tokens.push_back(UrlToken{ UrlTokenType::Username, std::string(userinfo.substr(0, colonPos)) });
				m_tokens.push_back(UrlToken{ UrlTokenType::Password, std::string(userinfo.substr(colonPos + 1)) });
			}
			else {
				m_tokens.push_back(UrlToken{ UrlTokenType::Username, std::string(userinfo) });
			}
		}

		const std::size_t colonPos = hostport.find(':');
		if (colonPos != std::string_view::npos) {
			m_tokens.push_back(UrlToken{ UrlTokenType::Host, std::string(hostport.substr(0, colonPos)) });
			m_tokens.push_back(UrlToken{ UrlTokenType::Port, std::string(hostport.substr(colonPos + 1)) });
		}
		else {
			m_tokens.push_back(UrlToken{ UrlTokenType::Host, std::string(hostport) });
		}
	}

	void UrlLexer::LexScheme() {
		std::string_view scheme = ReadUntil(":");
		if (Peek() == ':') {
			++m_pos;
		}
		m_tokens.push_back(UrlToken{ UrlTokenType::Scheme, std::string(scheme) });
	}

	void UrlLexer::LexPath() {
		if (Peek() == '/') {
			std::string_view path = ReadUntil("?#");
			m_tokens.push_back(UrlToken{ UrlTokenType::Path, std::string(path) });
		}
	}

	void UrlLexer::LexQuery() {
		if (Peek() == '?') {
			++m_pos;
			std::string_view query = ReadUntil("#");
			m_tokens.push_back(UrlToken{ UrlTokenType::Query, std::string(query) });
		}
	}

	void UrlLexer::LexFragment() {
		if (Peek() == '#') {
			++m_pos;
			std::string_view fragment = std::string_view(m_input).substr(m_pos);
			m_pos = m_input.size();
			m_tokens.push_back(UrlToken{ UrlTokenType::Fragment, std::string(fragment) });
		}
	}
}