#pragma once 

#include <windows.h>

namespace Browser::Platform::Windows {
	class Application {
	public:
		Application(HINSTANCE instance, int show_command);

		int Run();

	private:
		HINSTANCE m_instance;
		int m_show_command;
	};
}