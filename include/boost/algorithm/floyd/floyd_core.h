#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <stdexcept> // �����쳣����

namespace boost {
	namespace algorithm {
		namespace floyd {
				class Floyd {
				public:
					// ����Ϊ�ڽӾ���
					Floyd(const std::vector<std::vector<int>>& directed_graph, int start, int goal);
					// ����Ϊ�ڽ��б�
					Floyd(const std::vector<std::vector<std::pair<int, int>>>& adjacency_list, int start, int goal);
					// Floyd����
					void floyd_serach();
					// ��ȡ�ڵ�����
					const int& get_node_num() const;
					// ��ӡͼ�ṹ
					void PrintGraph();
					// ��ӡ���Ȩ�ؾ���
					void PrintWeightMatrix();
					// ��ȡ���·��
					std::vector<int> get_shortest_path();
					// ��ӡ·������
					void PrintPathMatrix();
					// ��ӡ·��
					void PrintPath(std::vector<int> path, std::function<std::string(int)> callback);

					static void test_floyd();
				private:
					// �ڽӾ���
					std::vector<std::vector<int>> m_Directed_Graph;
					// ���Ȩ�ؾ���
					std::vector<std::vector<int>> m_Weight_Matrix;
					// path matrix
					std::vector<std::vector<int>> m_Path_Matrix;
					// �ڵ�����
					int m_NodeNums;
					// start
					int m_Start;
					// goal
					int m_Goal;
				};
		}
	}
}

