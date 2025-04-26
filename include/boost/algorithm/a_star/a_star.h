#pragma once
#include "boost/algorithm/template.h" // 包含模板基类的头文件
#include "boost/common/graph.h"
#include "boost/common/node.h"
#include "boost/common/GridGraph.h"
using namespace boost::common;
using namespace boost::algorithm;

namespace boost {
	namespace algorithm {
		namespace a_star {

            struct CompareNode {
                bool operator()(const std::shared_ptr<Node> a_ptr, const std::shared_ptr<Node> b_ptr) const;
            };
            // 自定义哈希函数
            struct PairHash {
                template <typename T1, typename T2>
                std::size_t operator()(const std::pair<T1, T2>& pair) const;
            };
            // 假设 Graphtype 是一个二维网格地图（例如 std::vector<std::vector<int>>）
            // Nodetype 是一个表示坐标的结构体（例如 std::pair<int, int>）
            class AStar : public PlanAlgorithm<GridGraph, std::shared_ptr<Node>, Node> {
            protected:
                // 开放列表 优先级队列
                std::priority_queue < std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNode > priority_queue;
                std::vector < std::vector<std::shared_ptr<Node>> > a_Graph;
                std::shared_ptr<Node> a_start;
                std::shared_ptr<Node> a_goal;
                int a_Rows, a_Cols;
                //std::vector<std::shared_ptr<Node>> a_OpenList;
                std::unordered_map<std::pair<int, int>, std::shared_ptr<Node>, PairHash> a_OpenList;
                std::unordered_map<std::pair<int, int>, std::shared_ptr<Node>, PairHash> a_ClosedList;

            public:
                AStar(const GridGraph& graph,
                    const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal);

                void PrintGraph();

                bool operator==(const std::shared_ptr<Node>& other);

                // 实现基类的纯虚函数
                bool isValidPoint(const std::shared_ptr<Node>& point) const override;

                // 是否碰撞点
                bool IsObstacle(const std::shared_ptr<Node>& node);

                // 打印路径点
                void PrintPath();

                // 获取当前节点到邻居节点的距离
                float get_cost(const std::shared_ptr<Node>& current_ptr, const std::shared_ptr<Node>& neighbor_ptr);

                // 欧几里得距离
                //float get_heuristic(const std::shared_ptr<Node>& neighbor_node, const std::shared_ptr<Node>& goal);
                static double euclideanDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal);
                // 曼哈顿距离
                static double manhattanDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal);
                // 对角距离
                static double diagonalDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal);
                // 实现路径搜索算法（例如简单的深度优先搜索）

                bool PathSearch(std::function<double(const std::shared_ptr<Node>&, const std::shared_ptr<Node>&)>) override;

                // 重载<<
                //std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Node>& ptr);

                static void run_astar_test();
            };

		}
	}
}