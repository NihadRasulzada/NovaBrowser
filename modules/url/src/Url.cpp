#include "url/Url.hpp"

#include <sstream>
#include <utility>

namespace Browser::Url
{
	Scheme Url::GetScheme() const noexcept { return m_scheme; }
	const std::string& Url::GetHost() const noexcept { return m_host; }
	uint16_t Url::GetPort() const noexcept { return m_port; }
	const std::string& Url::GetPath() const noexcept { return m_path; }
	const std::string& Url::GetQuery() const noexcept { return m_query; }
	const std::string& Url::GetFragment() const noexcept { return m_fragment; }
	const std::string& Url::GetUsername() const noexcept { return m_username; }
	const std::string& Url::GetPassword() const noexcept { return m_password; }

	void Url::SetScheme(Scheme scheme) { m_scheme = scheme; }
	void Url::SetHost(std::string host) { m_host = std::move(host); }
	void Url::SetPort(uint16_t port) { m_port = port; }
	void Url::SetPath(std::string path) { m_path = std::move(path); }
	void Url::SetQuery(std::string query) { m_query = std::move(query); }
	void Url::SetFragment(std::string fragment) { m_fragment = std::move(fragment); }
	void Url::SetUsername(std::string username) { m_username = std::move(username); }
	void Url::SetPassword(std::string password) { m_password = std::move(password); }

	bool Url::IsSecure() const noexcept {
		return m_scheme == Scheme::Https || m_scheme == Scheme::Wss;
	}

	bool Url::HasPort() const noexcept { return m_port != 0; }
	bool Url::HasQuery() const noexcept { return !m_query.empty(); }
	bool Url::HasFragment() const noexcept { return !m_fragment.empty(); }
	bool Url::HasAuthentication() const noexcept { return !m_username.empty(); }

	std::string Url::ToString() const {
		std::ostringstream out;

		switch (m_scheme) {
		case Scheme::Http:  out << "http";  break;
		case Scheme::Https: out << "https"; break;
		case Scheme::File:  out << "file";  break;
		case Scheme::Ftp:   out << "ftp";   break;
		case Scheme::Ws:    out << "ws";    break;
		case Scheme::Wss:   out << "wss";   break;
		case Scheme::Unknown: default: break;
		}
		out << "://";

		if (HasAuthentication()) {
			out << m_username;
			if (!m_password.empty()) {
				out << ':' << m_password;
			}
			out << '@';
		}

		out << m_host;

		if (HasPort()) {
			out << ':' << m_port;
		}

		out << m_path;

		if (HasQuery()) {
			out << '?' << m_query;
		}

		if (HasFragment()) {
			out << '#' << m_fragment;
		}

		return out.str();
	}

	void Url::Clear() {
		m_scheme = Scheme::Unknown;
		m_host.clear();
		m_port = 0;
		m_path = "/";
		m_query.clear();
		m_fragment.clear();
		m_username.clear();
		m_password.clear();
	}
}