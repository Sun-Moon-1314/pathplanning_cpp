#include "pch.h"
#include "boost/utils/Timer.h"
#include "boost/algorithm/dijkstra/dijsktra_core.h"
#include "boost/utils/Log.h"
#include <filesystem>
using boost::utils::FileOutput;
using boost::utils::DebugLevel;
using boost::utils::LogInfo;
using boost::utils::LogWarning;
using boost::utils::LogError;
using boost::utils::Logger;
using boost::utils::TimerRecorder;
namespace boost {
	namespace algorithm {
		namespace dijkstra {
			bool GetMinCompare::operator()(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) const {
				return a.second > b.second;
			}
			std::ostream& operator<<(std::ostream& ostream,
				std::unordered_map<std::string, std::unordered_map <std::string, int>> map) {
	
				ostream << "{\n";
				for (const auto& elem : map) {
					int count = 0;
					ostream << elem.first;
					ostream << ": {";
					for (auto& value : elem.second) {
						ostream << value.first << ": " << value.second;
						if (++count != elem.second.size()) {
							std::cout << ", ";
						}
					}
		
					ostream << "}";
					ostream << "\n";
				}
				ostream << "}\n";
				return ostream;
			}

			Dijsktra::Dijsktra(){}

			Dijsktra::Dijsktra(
				const std::unordered_map <std::string, std::unordered_map <std::string, int>>& set_map,
				std::string start,
				std::string end
			) : neighbor_map(set_map),
			m_Start(start),
			m_Goal(end) {
				// ��ʼ��distances
				for (auto& elem : neighbor_map) {
					distances[elem.first] = INT_MAX;
				}
				distances[m_Start] = 0;
				LogInfo("Dijkstra initial successful.");
			}


			// �����㷨
			std::vector<std::string> Dijsktra::dijsktra_search() {
				std::vector<std::string> path;
				// �������ó��ֹ�����,δ��std::pair<std::string, int>
				priority_queue.push(std::make_pair(m_Start, 0));
				// ѭ��
				while (!priority_queue.empty()) {
					std::pair<std::string, int> priority_node = priority_queue.top();
					std::string current_node = priority_node.first;
					int min_dis = priority_node.second;
					//std::cout << "Poping: (" << current_node << ", " << min_dis << ")\n";
					priority_queue.pop();
					// �ж��Ƿ񵽴�Ŀ���
					if (current_node == m_Goal) {
						std::string current = m_Goal;

						while (current != m_Start) {
							path.push_back(current);
							// find����end��ʾ�ܷ��ҵ�
							if (previous_node.find(current) == previous_node.end()) {
								std::cout << "Can not find path." << "\n";
								return {};
							}
							// ���߽���ķ���
							current = previous_node.at(current);
						}
						path.push_back(m_Start);
						// ����
						std::reverse(path.begin(), path.end());

						return path;
					}
					// �ж�min_dis�Ƿ�С��distances�е���С����
					if (min_dis > distances[current_node]) continue;

					// ѭ�������ھӽڵ�
					if (neighbor_map.find(current_node) == neighbor_map.end()) {
						std::cerr << "Error: current_node (" << current_node << ") not found in neighbor_map.\n";
						continue;
					}
					for (auto& elem : neighbor_map[current_node]) {
						std::string neighbor_node = elem.first;
						int weight = elem.second;
						int neighbor_dis = weight + min_dis;
						if (neighbor_dis < distances[neighbor_node]) {
							distances[neighbor_node] = neighbor_dis;
							previous_node[neighbor_node] = current_node;
							//std::cout << "Pushing: (" << neighbor_node << ", " << neighbor_dis << ")\n";
							priority_queue.push(std::make_pair(neighbor_node, neighbor_dis));
						}
					}

				}

				return path;
			}

			// TODO: �����ϰ��� 
			void Dijsktra::SetObstacles() {

			}
			// ��ȡ��̾����
			std::unordered_map <std::string, int> Dijsktra::Distances() {
				return distances;
			}

			// ���õ�ͼ
			void Dijsktra::SetMap(std::unordered_map <std::string, std::unordered_map <std::string, int>>&& set_map) {
				neighbor_map = std::move(set_map);
			}

			// �������
			void Dijsktra::SetStart(std::string&& start) {
				m_Start = std::move(start);
			}

			// ����Ŀ���
			void Dijsktra::SetGoal(std::string&& goal) {
				m_Goal = std::move(goal);
			}

			// ��ӡ��ͼ
			void Dijsktra::PrintMap() {
				std::cout << neighbor_map << " " << "\n";
			}
			// ��ӡ�����¼��
			void Dijsktra::PrintDistance() {
				size_t count = 0;
				size_t size = distances.size();
				std::cout << "Distances: ";
				std::cout << "{";
				for (auto& dis : distances) {
					std::cout << dis.first << ": " << dis.second;
					if (++count < size) {
						std::cout << " ";
					}
				}
				std::cout << "}\n";
			}

			// ��ӡǰ���ڵ��¼��
			void Dijsktra::PrintPath(const std::vector<std::string>& path) {
		if (path.empty()) std::cout << "path is empty." << "\n";
		// ��ӡ·��
		else
		{
			std::cout << "Dijsktra Path: ";
			for (size_t i = 0; i < path.size(); i++) {
					std::cout << path[i];
					if (i != path.size() - 1) {
						std::cout << "->";
					}
				}
				std::cout << "\n";
		}
	
	}

			std::string GenerateLogFileName() {
		std::time_t now = std::time(nullptr);
		std::tm localTime;
		// ʹ�� localtime_s ���� localtime
		localtime_s(&localTime, &now);

		std::ostringstream oss;
		oss << "./logs/log_" << (1900 + localTime.tm_year) << "_"
			<< (1 + localTime.tm_mon) << "_"
			<< localTime.tm_mday << "_"
			<< localTime.tm_hour << "_"
			<< localTime.tm_min << "_"
			<< localTime.tm_sec << ".txt";

		return oss.str();
	}

			void Dijsktra::run_dijkstra() {
					//std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
					// ȷ�� logs �ļ��д���
					std::filesystem::create_directories("./logs");
					// ������־������ļ�
					FileOutput fileOutput(GenerateLogFileName());
					Logger::Get().SetOutput(fileOutput);

					//std::cout << "Logging to file: " << std::filesystem::absolute("./logs/logs.txt") << std::endl;

					Logger::Get().SetLevel(DebugLevel::INFO);

					std::cout << "Current log level: " << EnumToString(DebugLevel::INFO) << "\n";
					bool success;

					std::unordered_map <std::string, std::unordered_map <std::string, int>> neighbor_map;
					neighbor_map[std::string("P1")] = { {std::string("P2"), 3}, {std::string("P3"), 2} };
					neighbor_map[std::string("P2")] = { {std::string("P4"), 1}, {std::string("P5"), 5} };
					neighbor_map[std::string("P3")] = { {std::string("P4"), 2}, {std::string("P5"), 4} };
					neighbor_map[std::string("P4")] = { {std::string("P5"), 7} };
					neighbor_map[std::string("P5")] = { };

					Dijsktra dijsltra(neighbor_map, std::string("P1"), std::string("P4"));

					{
						PROFILE_SCOPE("main");
						dijsltra.PrintMap();
						dijsltra.PrintDistance();
						std::vector<std::string> path = dijsltra.dijsktra_search();

						dijsltra.PrintPath(path);
						dijsltra.PrintDistance();
						success = true;
						if (success) {
							LogInfo("Algorithm runs successfully!");
						}
					}
	
				}
			}
	}
}