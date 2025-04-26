#pragma once

#include "boost/algorithm/template.h" // 包含模板基类的头文件


namespace boost {
    namespace algorithm {
        namespace a_star_core {
            // 结点
            struct Node {
                int x = 0, y = 0; // x：横坐标，y：纵坐标
                float f = 0.0, g = 0.0, h = 0.0; // f：总代价，g：start-current实际代价，h：current-goal估计代价
                int is_connect = 0; // 0：通行，1：障碍
                bool inopen = false;
                bool inclose = false;
                std::weak_ptr<Node> parent; // 父节点
                std::vector< std::shared_ptr<Node> > neighbors; // 直接存储邻居节点指针
                // 普通构造
                Node() {}
                // 拷贝构造
                Node(const std::shared_ptr<Node>& node);

                // 该处const保证与const的输入一致
                bool operator==(const std::shared_ptr<Node>& other) const;

                // 获取邻居节点
                const std::vector<std::shared_ptr<Node>>& get_neighbors() const ;

                // 允许访问私有成员，实际为全局函数
                friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Node>& ptr);

                ~Node() = default;
            };
            
            struct CompareNode {
                bool operator()(const std::shared_ptr<Node> a_ptr, const std::shared_ptr<Node> b_ptr) const;
            };

            // 假设 Graphtype 是一个二维网格地图（例如 std::vector<std::vector<int>>）
            // Nodetype 是一个表示坐标的结构体（例如 std::pair<int, int>）
            class AStar : public PlanAlgorithm<std::vector<std::vector<std::shared_ptr<Node>>>, std::shared_ptr<Node>, Node> {
            protected:
                // 开放列表 优先级队列
                std::priority_queue < std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNode > priority_queue;
            public:
                AStar(const std::vector<std::vector<std::shared_ptr<Node>>>& graph,
                    const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal);

                /*AStar(std::vector<std::vector<std::shared_ptr<Node>>>&& graph, std::shared_ptr<Node>&& start, std::shared_ptr<Node>&& goal);*/

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
