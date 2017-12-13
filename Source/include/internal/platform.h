#ifndef PLATFORM_H
#define PLATFORM_H

#define USE_SDL

#ifdef _WIN32
  #define USE_WINAPI 1
#endif

#include <memory>

#define shared std::shared_ptr
#define weak std::weak_ptr

using namespace std;

#endif
