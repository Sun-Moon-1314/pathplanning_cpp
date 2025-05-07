//#define _CRT_SECURE_NO_WARNINGS
// �������ģʽ����

#include "pch.h"
#include "boost/algorithm/dijkstra/dijsktra_core.h"
#include "boost/algorithm/floyd/floyd_core.h"
#include "boost/algorithm/a_star/a_star.h"
#include "../build/cmake/Version.h"
#include "../build/cmake/Config.h"

using namespace boost::algorithm::dijkstra;
using namespace boost::algorithm::floyd;
using namespace boost::algorithm::a_star;
// ��ӡ������Ϣ
#define INFO_MODE
// ��ӡ������Ϣ������
#define DEBUG_MODE
// ��ӡ������Ϣ������
//#define FORMAL_MODE

auto run_floyd = []() {std::cout << "Floyd." << "\n";};

std::ostream& operator<<(std::ostream& oss, std::pair<int, int>& vector) {
	oss << "(" << vector.first << ", " << vector.second << ")";
	return oss;
}

void test_nlohmann() {
	// create object
	nlohmann::json heuristic;
	heuristic["algorithm"] = "A star";
	heuristic["get_heuristic"] = "euclideanDistance";
	
	// write into file
	std::ofstream file("config/heuristic.json");
	if (file.is_open()) {
		file << heuristic.dump(4);
		file.close();
		std::cout << "Heuristic JSON created successful.\n";
	}
	else
	{
		std::cout << "Failed to create JSON file.\n";
	}
}

void test_vector() {

	std::vector<std::vector<std::pair<int, int>>> two_dim_vector;
	two_dim_vector.push_back({ {1,2},{1,3} });
	two_dim_vector.push_back({ {2,3} });


	for (size_t i = 0; i < two_dim_vector.size(); i++) {
		std::cout << "{";
		for (size_t j = 0;j < two_dim_vector[i].size();j++) {
			std::cout << two_dim_vector[i][j];
		}
		std::cout << "}";
		std::cout << "\n";
		
	}
	//std::vector<std::vector<int>> two_dim_vector;
	//two_dim_vector.push_back(one_dim_vector);
	//std::cout << two_dim_vector.size();
}

#if TEST_MAIN
int main(int argc, char* argv[]) {
	std::cout << "Version: "
		<< PROJECT_VERSION_MAJOR << "."
		<< PROJECT_VERSION_MINOR << "."
		<< PROJECT_VERSION_PATCH << std::endl;
	// ��ʼ�� glog
	google::InitGoogleLogging(argv[0]);

	// ������־���������̨
	//FLAGS_log_dir = "./logs";
	FLAGS_logtostderr = true;  // ������־�������׼��������stderr��

	// ������־�ļ����·��
	// ������־���Ŀ¼
#ifdef OUT_FILE
	google::SetLogDestination(google::INFO, "./logs/info_");
	google::SetLogDestination(google::WARNING, "./logs/warning_");
	google::SetLogDestination(google::ERROR, "./logs/error_");
#endif // OUT_FILE

	// ������־������ļ���С����
	FLAGS_max_log_size = 10;  // ÿ����־�ļ����Ϊ 10 MB 
	// ���ݵ���ģʽ������־


#ifdef INFO_MODE 
	FLAGS_minloglevel = 0;    // 0: INFO, 1: WARNING, 2: ERROR, 3: FATAL, �������õļ�������־ͻ����
	LOG(INFO) << "��ӡģʽ����ϸ��־���";
#endif
#ifdef DEBUG_MODE
	FLAGS_minloglevel = 1;    // 0: INFO, 1: WARNING, 2: ERROR, 3: FATAL, �������õļ�������־ͻ����
	LOG(INFO) << "����ģʽ����ϸ��־���";
#endif
#ifdef FORMAL_MODE
	FLAGS_minloglevel = 2; // ����� ERROR �� FATAL ��־
	LOG(INFO) << "��ʽģʽ������־�������";
#endif

	/*LOG(INFO) << "��ӡ INFO �������־";
	LOG(WARNING) << "��ӡ WARNING �������־";
	LOG(ERROR) << "��ӡ ERROR �������־";*/

	////glogtest(argv);
	int choice;
	std::cout << "----Choose a algorithm:----\n";
	std::cout << "1: Dijkstra" << "\n";
	std::cout << "2: Floyd" << "\n";
	std::cout << "3: AStar" << "\n";

	std::cout << "Please input: ->";
	std::cin >> choice;
	std::cout << "------Output------\n";

	switch (choice)
	{
	case 1:
		std::cout << "choose Dijkstra.\n";
		Dijsktra::run_dijkstra();
		break;
	case 2:
		std::cout << "choose Floyd.\n";
		Floyd::test_floyd();
		break;
	case 3:
		std::cout << "choose Astar.\n";
		AStar::run_astar_test();
		break;
	default:
		break;
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���Ի������еĶ����ַ�
	std::cin.get();
	// ���� glog
	google::ShutdownGoogleLogging();
	return 0;
}

#endif // TEST_MAIN

