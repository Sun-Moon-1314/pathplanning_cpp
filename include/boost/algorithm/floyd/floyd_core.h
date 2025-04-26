#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <stdexcept> // 用于异常处理

namespace boost {
	namespace algorithm {
		namespace floyd {
				class Floyd {
				public:
					// 输入为邻接矩阵
					Floyd(const std::vector<std::vector<int>>& directed_graph, int start, int goal);
					// 输入为邻接列表
					Floyd(const std::vector<std::vector<std::pair<int, int>>>& adjacency_list, int start, int goal);
					// Floyd搜索
					void floyd_serach();
					// 获取节点数量
					const int& get_node_num() const;
					// 打印图结构
					void PrintGraph();
					// 打印最短权重矩阵
					void PrintWeightMatrix();
					// 获取最短路径
					std::vector<int> get_shortest_path();
					// 打印路径矩阵
					void PrintPathMatrix();
					// 打印路径
					void PrintPath(std::vector<int> path, std::function<std::string(int)> callback);

					static void test_floyd();
				private:
					// 邻接矩阵
					std::vector<std::vector<int>> m_Directed_Graph;
					// 最短权重矩阵
					std::vector<std::vector<int>> m_Weight_Matrix;
					// path matrix
					std::vector<std::vector<int>> m_Path_Matrix;
					// 节点数量
					int m_NodeNums;
					// start
					int m_Start;
					// goal
					int m_Goal;
				};
		}
	}
}

