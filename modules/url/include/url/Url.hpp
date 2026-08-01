#include <string>

namespace Browser::Url {
	enum class Scheme : uint8_t {
		Unknown,
		Http,
		Https,
		File,
		Ftp,
		Ws,
		Wss
	};

	class Url {
	public:
		Url() = default;

		Scheme GetScheme() const noexcept;
		const std::string& GetHost() const noexcept;
		uint16_t GetPort() const noexcept;
		const std::string& GetPath() const noexcept;
		const std::string& GetQuery() const noexcept;
		const std::string& GetFragment() const noexcept;
		const std::string& GetUsername() const noexcept;
		const std::string& GetPassword() const noexcept;

		void SetScheme(Scheme scheme);
		void SetHost(std::string host);
		void SetPort(uint16_t port);
		void SetPath(std::string path);
		void SetQuery(std::string query);
		void SetFragment(std::string fragment);
		void SetUsername(std::string username);
		void SetPassword(std::string password);

		bool IsSecure() const noexcept;
		bool HasPort() const noexcept;
		bool HasQuery() const noexcept;
		bool HasFragment() const noexcept;
		bool HasAuthentication() const noexcept;
		std::string ToString() const;
		void Clear();

	private:
		Scheme m_scheme = Scheme::Unknown;
		std::string m_host;
		uint16_t m_port = 0;
		std::string m_path = "/";
		std::string m_query;
		std::string m_fragment;
		std::string m_username;
		std::string m_password;
	};
}