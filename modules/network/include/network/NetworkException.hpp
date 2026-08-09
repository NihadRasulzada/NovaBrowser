namespace Browser::Network {
	class NetworkException : public std::runtime_error
	{
	public:
		using runtime_error::runtime_error;
	};
}