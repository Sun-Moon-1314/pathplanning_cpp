#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include "dijsktra_core.h"
#include "Log.h"
#include "export.h"
#include "config.h"
#include "glog/logging.h"

int main(int argc, char* argv[]) {
	// 初始化 glog
	google::InitGoogleLogging(argv[0]);
	// 设置日志输出到控制台
	FLAGS_logtostderr = true;  // 所有日志输出到标准错误流（stderr）
	// 设置日志文件输出路径
	google::SetLogDestination(google::INFO, "./logs/info_");
	google::SetLogDestination(google::WARNING, "./logs/warning_");
	google::SetLogDestination(google::ERROR, "./logs/error_");
	// 打印日志
	LOG(INFO) << "This is an informational message.";
	LOG(WARNING) << "This is a warning message.";
	LOG(ERROR) << "This is an error message.";
	// 使用检查宏
	int a = 5, b = 10;
	CHECK(a < b) << "a is not less than b!";
	// 清理 glog
	google::ShutdownGoogleLogging();
	//// 确保 logs 文件夹存在
	//std::filesystem::create_directories("./logs");
	//// 设置日志输出到文件
	//FileOutput fileOutput("./logs/log.txt");
	//Logger::Get().SetOutput(fileOutput);
	//std::cout << "Logging to file: " << std::filesystem::absolute("./logs/log.txt") << std::endl;

	//Logger::Get().SetLevel(DebugLevel::INFO);
	//std::cout << "Current log level: " << EnumToString(DebugLevel::INFO) << "\n";
	//LogWarning("Dijkstra initial successful.");

	/*int choice;
	std::cout << "Choose a algorithm:\n";
	std::cout << "1: Dijkstra" << "\n";
	std::cout << "2: Floyd" << "\n";
	std::cout << "Please input: ";
	std::cin >> choice;
	switch (choice)
	{
	case 1: run_dijkstra();
	case 2: 
	default:
		std::cin.get();
	}*/
	
	//PROFILE_FUNCTION();
	std::cin.get();
	return 0;
}