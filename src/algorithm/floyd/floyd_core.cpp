#include "pch.h"
#include "boost/algorithm/BidirectionalMap.h"
#include "boost/algorithm/floyd/floyd_core.h"


namespace boost {
	namespace algorithm {
		namespace floyd {
			// adjacency matrix
			Floyd::Floyd(const std::vector<std::vector<int>>& directed_graph, int start, int goal) {
				LOG(INFO) << "\nParams initial start....";
				if (directed_graph.empty()) {
					LOG(ERROR) << "Input vector is empty!";
					throw std::invalid_argument("The graph is empty!");
					return;
				}
				m_Directed_Graph = directed_graph;
				m_NodeNums = directed_graph.size();
				// check if start and goal effect?
				if (start < 0 || start >= m_NodeNums || goal < 0 || goal >= m_NodeNums) {
					LOG(ERROR) << "start and goal are out of range!";
					throw std::out_of_range("Start or goal node is out of range!");
					return;
				}

				m_Weight_Matrix = std::vector<std::vector<int>>(m_NodeNums, std::vector<int>(m_NodeNums, INT_MAX));
				for (size_t i = 0;i < m_NodeNums;i++) {
					m_Weight_Matrix[i][i] = 0;
				}
				// 检查邻接矩阵是否是方阵
				size_t num_nodes = directed_graph.size();
				for (const auto& row : directed_graph) {
					if (row.size() != num_nodes) {
						LOG(ERROR) << "The graph is not a square matrix!";
						throw std::invalid_argument("The graph is not a square matrix!");
						return;
					}
				}

				// init m_Path_Matrix record
				m_Path_Matrix = std::vector<std::vector<int>>(m_NodeNums, std::vector<int>(m_NodeNums, -1));
				try {
					for (size_t i = 0;i < m_NodeNums;i++) {
						for (size_t j = 0;j < m_NodeNums;j++) {
							if (m_Directed_Graph[i][j] != INT_MAX)
								m_Path_Matrix[i][j] = i;
						}
					}
				}
				catch (const std::exception& e) {
					LOG(ERROR) << "assign has error!" << e.what();
					throw;
				}
				LOG(INFO) << "\nfloyd search over";
				m_Start = start;
				m_Goal = goal;
				LOG(INFO) << "\nParams initial end.";
			}

			// adjacency list
			Floyd::Floyd(const std::vector<std::vector<std::pair<int, int>>>& adjacency_list, int start, int goal) {
				LOG(INFO) << "\n------Adjacency_List Init------";
				m_NodeNums = adjacency_list.size();
				// check if start and goal effect?
				if (start < 0 || start >= m_NodeNums || goal < 0 || goal >= m_NodeNums) {
					LOG(ERROR) << "start and goal are out of range!";
					throw std::out_of_range("Start or goal node is out of range!");
					return;
				}
				// value = 0 if i == j
				m_Weight_Matrix = std::vector<std::vector<int>>(m_NodeNums, std::vector<int>(m_NodeNums, INT_MAX));
				for (size_t i = 0;i < m_NodeNums;i++) {
					m_Weight_Matrix[i][i] = 0;
				}

				m_Directed_Graph = std::vector<std::vector<int>>(m_NodeNums, std::vector<int>(m_NodeNums, INT_MAX));

				m_Path_Matrix = std::vector<std::vector<int>>(m_NodeNums, std::vector<int>(m_NodeNums, INT_MAX));
				for (size_t i = 0; i < m_NodeNums;i++) {
					m_Directed_Graph[i][i] = 0;
					for (const auto& [u, v] : adjacency_list[i]) {
						m_Directed_Graph[i][u] = v;
					}
				}
				for (size_t i = 0;i < m_NodeNums;i++) {
					for (size_t j = 0;j < m_NodeNums;j++) {
						if (m_Directed_Graph[i][j] != INT_MAX)
							m_Path_Matrix[i][j] = i;
					}
				}

				m_Start = start;
				m_Goal = goal;
				LOG(INFO) << "\n------Adjacency_List Over------";
			}

			// core search
			void Floyd::floyd_serach() {
				LOG(INFO) << "\n------floyd search start------";
				try{
					for (size_t k = 0;k < m_NodeNums;k++) {
						for (size_t i = 0;i < m_NodeNums;i++) {
							for (size_t j = 0;j < m_NodeNums;j++) {
								if (m_Directed_Graph[i][k]!=INT_MAX && m_Directed_Graph[k][j]!=INT_MAX){
									if (m_Directed_Graph[i][k] + m_Directed_Graph[k][j] < m_Directed_Graph[i][j]) {
										m_Weight_Matrix[i][j] = m_Directed_Graph[i][k] + m_Directed_Graph[k][j];
										m_Path_Matrix[i][j] = k;
									}
									else {
										m_Weight_Matrix[i][j] = m_Directed_Graph[i][j];
									}
								}
					
							}
						}
					}
				}
				catch (const std::exception& e) {
					LOG(ERROR) << "search faild." << e.what();
					throw;
				}
				LOG(INFO) << "\n------floyd search over------";
	
			}

			// get node number
			const int& Floyd::get_node_num() const {
				//LOG(INFO) << "\n------get_node_num------";
				return m_NodeNums;
			}

			void Floyd::PrintWeightMatrix() {
	LOG(INFO) << "\n------PrintWeightMatrix------";
	for (size_t i = 0; i < m_NodeNums;i++) {
		std::cout << "[";
		for (size_t j = 0; j < m_NodeNums;j++) {
			std::cout << m_Weight_Matrix[i][j];
			if (j <= m_NodeNums - 1)
				std::cout << ", ";
		}
		std::cout << "]";
		std::cout << "\n";
	}
}

			void Floyd::PrintGraph() {
	LOG(INFO) << "\n------PrintGraph------";
	for (size_t i = 0; i < m_NodeNums;i++) {
		std::cout << "[";
		for (size_t j = 0; j < m_NodeNums;j++) {
			std::cout << m_Directed_Graph[i][j];
			if (j != m_NodeNums-1)
				std::cout << ", ";
		}
		std::cout << "]";
		std::cout << "\n";
	}
}

			// get string path
			std::vector<int> Floyd::get_shortest_path() {
				LOG(INFO) << "\n------Get Shortest Path------";
				std::vector<int> path;
				path.push_back(m_Goal);
				try{
					while (m_Path_Matrix[m_Start][m_Goal] != m_Start) {
						path.push_back(m_Path_Matrix[m_Start][m_Goal]);
						m_Goal = m_Path_Matrix[m_Start][m_Goal];
						LOG(INFO) << m_Goal << "\n";
					}
					LOG(INFO) << "\nInner find path over.";
					path.push_back(m_Start);
				}
				catch (const std::exception& e) {
					LOG(ERROR) << "Get Path Wrong!" << e.what();
					throw;
				}
				LOG(INFO) << "\n------Get Path Over------";
				// reverse order
				std::reverse(path.begin(), path.end());
				return path;
			}

			void Floyd::PrintPathMatrix() {
	LOG(INFO) << "\n------PrintPathMatrix------";
	for (size_t i = 0; i < m_NodeNums;i++) {
		std::cout << "[";
		for (size_t j = 0; j < m_NodeNums;j++) {
			std::cout << m_Path_Matrix[i][j];
			if (j != m_NodeNums - 1)
				std::cout << ", ";
		}
		std::cout << "]";
		std::cout << "\n";
	}
}

			// callback function make int to string.
			void Floyd::PrintPath(std::vector<int> path, std::function<std::string(int)> callback) {
				LOG(INFO) << "\n------Path------";
				for (size_t index = 0;index < path.size();index++) {
					std::cout << callback(path[index]);
					if (index < path.size() - 1) {
						std::cout << "->";
					}
				}
				std::cout << "\n";
			}

			void create_graph() {

				//BidirectionalMap map;
				//map.AddMapping(1, "P1");
				//map.AddMapping(2, "P2");
				//map.AddMapping(3, "P3");
				//map.AddMapping(4, "P4");

				//// 查询映射
				//std::cout << "Index 1 maps to name: " << map.GetName(1) << std::endl;
				//std::cout << "Name 'P1' maps to index: " << map.GetIndex("P1") << std::endl;

				//// 检查映射是否存在
				//std::cout << "Does index 2 exist? " << (map.IndexExists(2) ? "Yes" : "No") << std::endl;
				//std::cout << "Does name 'P2' exist? " << (map.NameExists("P2") ? "Yes" : "No") << std::endl;

				//// 删除映射
				//map.RemoveByIndex(1);
				//std::cout << "After removing index 1:" << std::endl;
				//map.PrintMappings();

			}

			std::unique_ptr<BidirectionalMap> mapinit() {
				std::unique_ptr<BidirectionalMap> map = std::make_unique<BidirectionalMap>();
				map->AddMapping(0, "P0");
				map->AddMapping(1, "P1");
				map->AddMapping(2, "P2");
				map->AddMapping(3, "P3");
				map->AddMapping(4, "P4");
				map->AddMapping(5, "P5");
				map->PrintMappings();
				return map;
			}

			void Floyd::test_floyd() {
	auto map= mapinit();
	// test group1
	/*const std::vector<std::vector<int>>& directed_graph1 = {
		{0, 2, INT_MAX, INT_MAX},
		{INT_MAX, 0, INT_MAX, 4},
		{INT_MAX, INT_MAX, 0, 3},
		{INT_MAX, INT_MAX, INT_MAX, 0}
	};*/
	// test group2
	const std::vector<std::vector<int>> directed_graph2 = {
	{0,       10,      15,      INT_MAX, 20,      INT_MAX},  // 从节点 0 出发的路径
	{INT_MAX, 0,       35,      25,      INT_MAX, INT_MAX},  // 从节点 1 出发的路径
	{INT_MAX, INT_MAX, 0,       30,      INT_MAX, 10},       // 从节点 2 出发的路径
	{INT_MAX, INT_MAX, INT_MAX, 0,       5,       INT_MAX},  // 从节点 3 出发的路径
	{INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0,       15},       // 从节点 4 出发的路径
	{INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0}         // 从节点 5 出发的路径
	};

	// test adjandency list
	std::vector<std::vector<std::pair<int, int>>> adjacency_list = {
		{{1, 4}, {2, 1}}, // 节点 0 的邻接列表
		{{3, 1}},         // 节点 1 的邻接列表
		{{1, 2}, {3, 5}}, // 节点 2 的邻接列表
		{},               // 节点 3 的邻接列表
		{}                // 节点 4 的邻接列表（孤立节点）
	};

    LOG(INFO) << "\ndirected_graph created.";
    
	Floyd f(adjacency_list, 0, 3);
	
	//std::cout << f.get_node_num() << "\n";
	
	//f.PrintGraph();

	f.floyd_serach();
	f.PrintWeightMatrix();
	const std::vector<int>& path = f.get_shortest_path();
	f.PrintPathMatrix();
	auto lambda = [&map](int index) {
		return map->GetName(index);
	};
	f.PrintPath(path, lambda);
}
		}
	}
}