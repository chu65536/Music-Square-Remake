#include "Tools/Debug.hpp"


namespace Debug {

namespace Timer {
std::chrono::time_point<std::chrono::system_clock> m_timerStart;
std::chrono::time_point<std::chrono::system_clock> m_timerEnd;
void Start() {
    m_timerStart = std::chrono::system_clock::now();
}

void Stop(const std::string& message) {
    Debug::LogTime();
    m_timerEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = m_timerEnd - m_timerStart;
    std::cout << message << " (time taken: " << elapsedTime.count() << ")" << std::endl;
}
}

void LogTime() {
    std::time_t t = std::time(0); 
    std::tm* now = std::localtime(&t);
    std::cout << "[" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "] ";
}

void Log(const std::string& message) {
    LogTime();
    std::cout << message << std::endl;
}

}
