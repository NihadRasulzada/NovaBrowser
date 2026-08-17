#pragma once

#include <windows.h>

namespace Browser::Platform::Windows {
	class Window {
	public:
		Window(HINSTANCE instance, const char* title, int width, int height);
		~Window();

		void Show(int show_command);
		HWND Handle() const;
	private:
		static LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param);

		void RegisterWindowClass();

		HINSTANCE m_instance;
		HWND m_handle;

		const char* m_title;
		int m_width;
		int m_height;
	};
}