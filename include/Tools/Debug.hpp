#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#ifdef NDEBUG
#define DEBUG_LOG(text) 
#define DEBUG_TIMER_START()
#define DEBUG_TIMER_STOP(message)
#else
#define DEBUG_LOG(text) Debug::Log(text)
#define DEBUG_TIMER_START() Debug::Timer::Start()
#define DEBUG_TIMER_STOP(message) Debug::Timer::Stop(message)
#endif


namespace Debug {

namespace Timer {
void Start();
void Stop(const std::string& message);
}

void LogTime();
void Log(const std::string& message);
}
