#pragma once

namespace boost {
	namespace algorithm {
		namespace dijkstra {
			// ��������
			struct GetMinCompare {
				bool operator()(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) const;
			};

			class Dijsktra {
			public:
				Dijsktra();
				Dijsktra(
					const std::unordered_map <std::string, std::unordered_map <std::string, int>>& set_map,
					std::string start,
					std::string goal
				);
				// �����㷨
				std::vector<std::string> dijsktra_search();

				// ���õ�ͼ
				void SetMap(std::unordered_map <std::string, std::unordered_map <std::string, int>>&& set_map);
				// �����ϰ���
				void SetObstacles();
				// �������
				void SetStart(std::string&& start);
				// ����Ŀ���
				void SetGoal(std::string&& goal);
				// ��ȡ��̾����
				std::unordered_map <std::string, int> Distances();
				// ��ӡ��ͼ
				void PrintMap();
				// ��ӡ�����¼��
				void PrintDistance();
				// ��ӡǰ���ڵ��¼��
				void PrintPath(const std::vector<std::string>& path);

				static void run_dijkstra();

			public:
				// ��ͼ�ھӽڵ�
				std::unordered_map <std::string, std::unordered_map <std::string, int>> neighbor_map;
				// ��̾����¼��
				std::unordered_map <std::string, int> distances;
				//// ǰ���ڵ��¼��
				std::unordered_map <std::string, std::string> previous_node;
				//// ���ȼ����У���ȡ��Сֵ
				std::priority_queue <std::pair<std::string, int>,
					std::vector<std::pair<std::string, int>>,
					GetMinCompare> priority_queue;
				//// ���
				std::string m_Start;
				//// Ŀ���
				std::string m_Goal;
			};
		}
		
	}
}

