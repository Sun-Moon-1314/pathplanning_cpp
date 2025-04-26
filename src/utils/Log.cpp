#include "pch.h"
#include "boost/utils/Log.h"

using boost::utils::FileOutput;
using boost::utils::Logger;

// ʵ�� FileOutput ���캯��
FileOutput::FileOutput(const std::string& filename) {
    m_File.open(filename, std::ios::app); // ��׷��ģʽ���ļ�
    if (!m_File.is_open()) {
        //std::cerr << "[ERROR] Failed to open log file: " << filename << std::endl;
    }
    else {
        //std::cout << "[DEBUG] Log file opened successfully: " << filename << std::endl;
    }
}


// ʵ�� FileOutput ��������
FileOutput::~FileOutput() {
    if (m_File.is_open()) {
        m_File.close();
    }
}

// ʵ�� FileOutput д�뺯��
void FileOutput::Write(const std::string& message) {
    if (m_File.is_open()) {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);

        m_File << "[" << (1900 + localTime->tm_year) << "-"
            << (1 + localTime->tm_mon) << "-"
            << localTime->tm_mday << " "
            << localTime->tm_hour << ":"
            << localTime->tm_min << ":"
            << localTime->tm_sec << "] "
            << message << std::endl;

        m_File.flush();
    }
}



// Logger ����ģʽʵ��
Logger& Logger::Get() {
    static Logger log;
    return log;
}

// Logger ���캯��
Logger::Logger() : m_Output(&consoleOutput), m_Level(DebugLevel::INFO) {}

// �������Ŀ��
void Logger::SetOutput(LogOutput& output) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Output = &output;
}

// ������־����
void Logger::SetLevel(DebugLevel level) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Level = level;
    std::cout << "Debug level set to " << EnumToString(m_Level) << "\n";
}

// ��־��ӡ����
void Logger::Info(std::string_view message) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (m_Level <= DebugLevel::INFO) {
        m_Output->Write("[INFO] " + std::string(message));
    }
}

void Logger::Warning(std::string_view message) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (m_Level <= DebugLevel::WARNING) {
        m_Output->Write("[WARNING] " + std::string(message));
    }
}

void Logger::Error(std::string_view message) {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (m_Level <= DebugLevel::ERROR) {
        m_Output->Write("[ERROR] " + std::string(message));
    }
}

// ȫ����־����ʵ��
Logger& logger = Logger::Get();

void boost::utils::LogInfo(const std::string& message) {
    std::cout<< "[INFO] " << message << std::endl;
    Logger::Get().Info(message);
}


void boost::utils::LogWarning(const std::string& message) {
    logger.Warning(message);
}

void boost::utils::LogError(const std::string& message) {
    logger.Error(message);
}
