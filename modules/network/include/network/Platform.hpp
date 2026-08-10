#pragma once

#if defined(_WIN32)
#define BROWSER_PLATFORM_WINDOWS 1
#elif defined(__linux__)
#define BROWSER_PLATFORM_LINUX 1
#else
#error "Unsupported platform"
#endif