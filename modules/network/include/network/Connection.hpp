namespace Browser::Network {
	class Connection
	{
	public:
		void Connect(const std::string& host, uint16_t port);
		void Disconnect();
		std::size_t Send(std::span<const std::byte>);
		std::size_t Receive(std::span<std::byte>);

	private:
		TcpSocket m_socket;
		DnsResolver m_dns;
	};
}