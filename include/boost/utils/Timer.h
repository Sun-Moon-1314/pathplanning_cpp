#pragma once
#include "pch.h"
#include <chrono>

namespace boost {
    namespace utils {
        class TimerRecorder {
        private:
            std::string m_Name;
            std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
        public:
            TimerRecorder(std::string name) : m_Name(std::move(name)) {
                m_StartTime = std::chrono::high_resolution_clock::now();
            }

            ~TimerRecorder() {
                stop();
            }
            void stop() {
                auto m_EndTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(m_EndTime - m_StartTime);
                std::cout << m_Name;
                std::cout << " takes time: " << (duration).count() * 0.001 << "ms" << "\n";
            }
        };

#define PROFILE 1
#if PROFILE
#define PROFILE_SCOPE(name) TimerRecorder timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_SCOPE(name)
#endif

        class InstrumentationTimer {
        private:
            const char* m_Name; // 函数名称
            std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
            bool m_Stopped;
        public:
            InstrumentationTimer(const char* name) : m_Name(name), m_Stopped(false) { m_StartTimepoint = std::chrono::high_resolution_clock::now(); }
            ~InstrumentationTimer() {
                if (!m_Stopped)
                    Stop();
            }
            void Stop() {
                auto endTimepoint = std::chrono::high_resolution_clock::now();
                auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
                auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
                auto duration = end - start;
                double ms = duration * 0.001;

                // 将当前的线程ID转换为哈希值，返回一个无符号整数，可在不同平台上使用并保持唯一性
                uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

                std::cout << m_Name << ": " << ms << "ms\n";

                m_Stopped = true;
            }
        };

    }
}

