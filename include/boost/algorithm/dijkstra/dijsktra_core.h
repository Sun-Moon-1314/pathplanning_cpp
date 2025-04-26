#pragma once

namespace boost {
	namespace algorithm {
		namespace dijkstra {
			// 函数对象
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
				// 核心算法
				std::vector<std::string> dijsktra_search();

				// 设置地图
				void SetMap(std::unordered_map <std::string, std::unordered_map <std::string, int>>&& set_map);
				// 设置障碍物
				void SetObstacles();
				// 设置起点
				void SetStart(std::string&& start);
				// 设置目标点
				void SetGoal(std::string&& goal);
				// 获取最短距离表
				std::unordered_map <std::string, int> Distances();
				// 打印地图
				void PrintMap();
				// 打印距离记录表
				void PrintDistance();
				// 打印前驱节点记录表
				void PrintPath(const std::vector<std::string>& path);

				static void run_dijkstra();

			public:
				// 地图邻居节点
				std::unordered_map <std::string, std::unordered_map <std::string, int>> neighbor_map;
				// 最短距离记录表
				std::unordered_map <std::string, int> distances;
				//// 前驱节点记录表
				std::unordered_map <std::string, std::string> previous_node;
				//// 优先级队列，获取最小值
				std::priority_queue <std::pair<std::string, int>,
					std::vector<std::pair<std::string, int>>,
					GetMinCompare> priority_queue;
				//// 起点
				std::string m_Start;
				//// 目标点
				std::string m_Goal;
			};
		}
		
	}
}

