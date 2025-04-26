#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <mutex>

namespace boost {
    namespace utils {

        // ��־������
        enum class DebugLevel {
            ERROR = 0, WARNING, INFO
        };

        // ��ö��תΪ�ַ���
        inline std::string EnumToString(DebugLevel level) {
            switch (level) {
            case DebugLevel::ERROR: return "ERROR";
            case DebugLevel::WARNING: return "WARNING";
            case DebugLevel::INFO: return "INFO";
            default: return "UNKNOWN";
            }
        }

        // ��־����������
        class LogOutput {
        public:
            virtual ~LogOutput() = default;
            virtual void Write(const std::string& message) = 0;
        };

        // ����̨���ʵ��
        class ConsoleOutput : public LogOutput {
        public:
            void Write(const std::string& message) override {
                std::cout << message << std::endl;
            }
        };

        // �ļ����ʵ��
        class FileOutput : public LogOutput {
        private:
            std::ofstream m_File;
        public:
            FileOutput(const std::string& filename);
            ~FileOutput();
            void Write(const std::string& message) override;
        };

        // ��־��������
        class Logger {
        private:
            LogOutput* m_Output; // ��ǰ��־���Ŀ��
            ConsoleOutput consoleOutput; // Ĭ�Ͽ���̨���
            DebugLevel m_Level;          // ��ǰ��־����
            std::mutex m_Mutex;          // �̰߳�ȫ����

            Logger(); // ˽�й��캯��������ģʽ
        public:
            Logger(const Logger& other) = delete;
            Logger& operator=(const Logger& other) = delete;

            static Logger& Get(); // ��ȡ����ʵ��

            void SetOutput(LogOutput& output); // �������Ŀ��
            void SetLevel(DebugLevel level);   // ������־����

            void Info(std::string_view message);
            void Warning(std::string_view message);
            void Error(std::string_view message);
        };

        // ȫ����־��������
        void LogInfo(const std::string& message);
        void LogWarning(const std::string& message);
        void LogError(const std::string& message);

    }
}
