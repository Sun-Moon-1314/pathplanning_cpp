#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <mutex>

namespace boost {
    namespace utils {

        // 日志级别定义
        enum class DebugLevel {
            ERROR = 0, WARNING, INFO
        };

        // 将枚举转为字符串
        inline std::string EnumToString(DebugLevel level) {
            switch (level) {
            case DebugLevel::ERROR: return "ERROR";
            case DebugLevel::WARNING: return "WARNING";
            case DebugLevel::INFO: return "INFO";
            default: return "UNKNOWN";
            }
        }

        // 日志输出抽象基类
        class LogOutput {
        public:
            virtual ~LogOutput() = default;
            virtual void Write(const std::string& message) = 0;
        };

        // 控制台输出实现
        class ConsoleOutput : public LogOutput {
        public:
            void Write(const std::string& message) override {
                std::cout << message << std::endl;
            }
        };

        // 文件输出实现
        class FileOutput : public LogOutput {
        private:
            std::ofstream m_File;
        public:
            FileOutput(const std::string& filename);
            ~FileOutput();
            void Write(const std::string& message) override;
        };

        // 日志管理器类
        class Logger {
        private:
            LogOutput* m_Output; // 当前日志输出目标
            ConsoleOutput consoleOutput; // 默认控制台输出
            DebugLevel m_Level;          // 当前日志级别
            std::mutex m_Mutex;          // 线程安全的锁

            Logger(); // 私有构造函数，单例模式
        public:
            Logger(const Logger& other) = delete;
            Logger& operator=(const Logger& other) = delete;

            static Logger& Get(); // 获取单例实例

            void SetOutput(LogOutput& output); // 设置输出目标
            void SetLevel(DebugLevel level);   // 设置日志级别

            void Info(std::string_view message);
            void Warning(std::string_view message);
            void Error(std::string_view message);
        };

        // 全局日志函数声明
        void LogInfo(const std::string& message);
        void LogWarning(const std::string& message);
        void LogError(const std::string& message);

    }
}
