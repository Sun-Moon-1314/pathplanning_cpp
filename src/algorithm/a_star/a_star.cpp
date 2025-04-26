#include "pch.h"
#include "boost/algorithm/a_star/a_star.h"
#include "boost/utils/Timer.h"

using namespace boost::utils;

namespace boost {
	namespace algorithm {
		namespace a_star {

            bool CompareNode::operator()(const std::shared_ptr<Node> a_ptr, const std::shared_ptr<Node> b_ptr) const {
                return a_ptr->f > b_ptr->f;
            }
            // 自定义哈希函数
            
            template <typename T1, typename T2>
            std::size_t PairHash::operator()(const std::pair<T1, T2>& pair) const {
                return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
            }
            

            AStar::AStar(const GridGraph& graph,
                const std::shared_ptr<Node>& start,
                const std::shared_ptr<Node>& goal) : PlanAlgorithm(graph, start, goal) {

                a_Graph = graph.getGraph();
                a_start = graph.getStartNode();
                a_goal = graph.getGoalNode();
                a_Rows = graph.getRows();
                a_Cols = graph.getCols();
                
                for (int x = 0; x < a_Rows; ++x) {
                    for (int y = 0; y < a_Cols; ++y) {
                        a_Graph[x][y] = std::make_shared<Node>(Node(x, y));
                    }
                }
                LOG(INFO) << "\nAStar Init!";
            }

            bool AStar::operator==(const std::shared_ptr<Node>& other) {
                return a_start == other;
            }

            // 重写基类的虚函数
            bool AStar::isValidPoint(const std::shared_ptr<Node>& point) const {
                // 示例实现：判断点是否在图的范围内
                if (point->x < 0 || point->x >= a_Rows ||
                    point->y < 0 || point->y >= a_Cols) {
                    return false;
                }
                else
                {
                    return true;
                }
            }

            // 是否碰撞点
            bool AStar::IsObstacle(const std::shared_ptr<Node>& node) {
                if (node->is_connect == 0) {
                    return false;
                }
                else {
                    std::cout << node << "is obstacle\n";
                    return true;
                }
            }

            // 打印路径点
            void AStar::PrintPath() {
                m_Path.push_back(a_goal);
                auto& temp = a_goal;
                while (auto sharedParent = temp->parent.lock()) {
                    m_Path.insert(m_Path.begin(), sharedParent);
                    temp = sharedParent;
                }
                for (const auto& ptr : m_Path) {
                    std::cout << "(" << ptr->x << ", " << ptr->y << ")";
                    if (ptr != m_Path.back()) {
                        std::cout << "->";
                    }
                }
            }

            // 打印地图
            void AStar::PrintGraph() {
                LOG(INFO) << "\n-------Graph:-------";
                for (size_t i = 0; i < a_Rows;i++) {
                    for (size_t j = 0; j < a_Cols;j++) {
                        std::cout << a_Graph[i][j] << " ";
                    }
                    std::cout << "\n";
                }
            }

            // 获取当前节点到邻居节点的距离
            float AStar::get_cost(const std::shared_ptr<Node>& current_ptr, const std::shared_ptr<Node>& neighbor_ptr) {
                return std::sqrt((current_ptr->x - neighbor_ptr->x) * (current_ptr->x - neighbor_ptr->x) +
                    (current_ptr->y - neighbor_ptr->y) * (current_ptr->y - neighbor_ptr->y));
            }

            // 欧几里得距离
            double AStar::euclideanDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal) {
                return std::sqrt(std::pow(start->x - goal->x, 2) + std::pow(start->y - goal->y, 2));
            }

            // 曼哈顿距离
            double AStar::manhattanDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal) {
                return std::abs(start->x - goal->x) + std::abs(start->y - goal->y);
            }

            // 对角距离
            double AStar::diagonalDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal) {
                int dx = std::abs(start->x - goal->x);
                int dy = std::abs(start->y - goal->y);
                return std::max(dx, dy);
            }

            // 实现路径搜索算法（例如简单的深度优先搜索）
            bool AStar::PathSearch(std::function<double(const std::shared_ptr<Node>&, const std::shared_ptr<Node>&)> get_heuristic) {
                PROFILE_SCOPE("PathSearch");
                // 假设实现一个简单的深度优先搜索算法
                LOG(INFO) << "\nAStar PathSearch";
                if (a_start)
                const std::shared_ptr<Node>& goal_ptr = a_goal;
                const std::shared_ptr<Node>& start_ptr = a_start;
                if (a_start == a_goal) {
                    //m_Path.push_back(a_start);
                    LOG(INFO) << "\nAStar Successful";
                    return true;
                }

                // 放入起点
                priority_queue.push(start_ptr);
                a_OpenList[std::make_pair(start_ptr->x, start_ptr->y)] = start_ptr;
                int step = 1;
                // 执行搜索逻辑（伪代码）
                while (!priority_queue.empty()) {
                    LOG(INFO) << "\n*************第" << step << "轮*************";

                    LOG(INFO) << "\npriority_queue element number is " << priority_queue.size();
                    LOG(INFO) << "\ntop element is " << priority_queue.top();

                    std::shared_ptr<Node> current_ptr = priority_queue.top();
                    priority_queue.pop();

                    a_ClosedList[std::make_pair(current_ptr->x, current_ptr->y)] = current_ptr;
                    if (a_ClosedList.find(std::make_pair(current_ptr->x, current_ptr->y)) != a_ClosedList.end()) {
                        LOG(INFO) << "\n" << "current_ptr:" << current_ptr << " inclose is set to " << a_ClosedList[std::make_pair(current_ptr->x, current_ptr->y)];
                    }
                    else {
                        LOG(WARNING) << "\nNot found.";
                    }
                    

                    a_OpenList[std::make_pair(current_ptr->x, current_ptr->y)] = current_ptr;
                    // 检查是否存在
                    if (a_OpenList.find({ current_ptr->x, current_ptr->y }) != a_OpenList.end()) {
                        LOG(INFO) << "\nFound in open list: "
                            << a_OpenList[{current_ptr->x, current_ptr->y}];
                    }
                    else {
                        LOG(ERROR) << "\nNot found in open list";
                    }

                    // 找到目标
                    if (current_ptr == a_goal) {
                        //PrintPath();
                        LOG(INFO) << "\nAStar Find Goal!";
                        return true;
                    }

                    for (const auto& neighbor_ptr : current_ptr->get_neighbors()) {
                        // 是障碍物
                        if (IsObstacle(neighbor_ptr)) {
                            continue;
                        }
                       
                        // 没在关闭列表
                        if (a_ClosedList.find(std::make_pair(neighbor_ptr->x, neighbor_ptr->y)) == a_ClosedList.end()) {
                            LOG(INFO) << "\n--------------";
                            neighbor_ptr->g = current_ptr->g + get_cost(current_ptr, neighbor_ptr);
                            LOG(INFO) << "\n" << "current_ptr: " << current_ptr
                                << " to neighbor_ptr: " << (neighbor_ptr) <<
                                " g = " << neighbor_ptr->g;
                            neighbor_ptr->h = get_heuristic(neighbor_ptr, m_goal);
                            LOG(INFO) << "\n" << "neighbor_ptr:" << (neighbor_ptr) << " to " <<
                                "m_goal: " << m_goal <<
                                " h = " << neighbor_ptr->h;
                            // 没在开放列表，新的节点
                            //LOG(INFO) << "current_ptr: " << current_ptr->x << ", " << current_ptr->y;
                            if (a_OpenList.find(std::make_pair(neighbor_ptr->x, neighbor_ptr->y)) == a_OpenList.end()) {
                                // 更新f,g,h，并把点push进priority_queue
                                neighbor_ptr->f = neighbor_ptr->g + neighbor_ptr->h;
                                priority_queue.push(neighbor_ptr);
                                LOG(INFO) << "\n" << neighbor_ptr << " push into priority_queue\n";
                                //LOG(INFO) << "current_ptr: " << current_ptr->x << ", " << current_ptr->y;
                                a_OpenList[std::make_pair(neighbor_ptr->x, neighbor_ptr->y)] = neighbor_ptr;

                                neighbor_ptr->parent = current_ptr;
                                LOG(INFO) << "\n" << neighbor_ptr << " Parent is " << neighbor_ptr->parent.lock();
                                LOG(INFO) << "\n";
                            }
                            // 在开放列表
                            else
                            {
                                if ((neighbor_ptr->g + neighbor_ptr->h) < neighbor_ptr->f) {
                                    neighbor_ptr->f = neighbor_ptr->g + neighbor_ptr->h;
                                }
                                LOG(INFO) << "\n";
                            }
                        }
                        else
                        {
                            LOG(INFO) << "\n--------------";
                            LOG(INFO) << "\n" << neighbor_ptr << " is in closelist!";
                            LOG(INFO) << "\n";
                            continue;
                        }
                    }
                    step++;
                }
                LOG(INFO) << "\nAStar Fall!";
                // 假设搜索失败
                return false;
            }


            // 读取文件是否存在
            bool fileExist(const std::string& filename) {
                std::ifstream infine(filename);
                return infine.good();
            }

            // 运行测试
            void AStar::run_astar_test() {
                // define a 5 * 5 grid graph
                GridGraph Graph(5, 5);
                
                const auto& graph = Graph.getGraph();
                int rows = Graph.getRows();
                int cols = Graph.getCols();
                

                // 设置障碍物
                graph[1][2]->is_connect = 1; // (1, 2) 是障碍
                graph[2][2]->is_connect = 1; // (2, 2) 是障碍
                graph[3][2]->is_connect = 1; // (3, 2) 是障碍

                // 设置邻居节点
                for (int x = 0; x < rows; ++x) {
                    for (int y = 0; y < cols; ++y) {
                        if (x >= 1 && graph[x - 1][y]->is_connect == 0) {
                            Graph.Add_Neighbors(graph[x][y], graph[x - 1][y]); // 上
                        }
                        if (x < rows - 1 && graph[x + 1][y]->is_connect == 0) {
                            Graph.Add_Neighbors(graph[x][y], graph[x + 1][y]); // 下
                        }
                        if (y > 0 && graph[x][y - 1]->is_connect == 0) {
                            Graph.Add_Neighbors(graph[x][y], graph[x][y - 1]); // 左
                        }
                        if (y < cols - 1 && graph[x][y + 1]->is_connect == 0) {
                            Graph.Add_Neighbors(graph[x][y], graph[x][y + 1]); // 右
                        }
                    }
                }

                // 定义起点和终点
                const std::shared_ptr<Node>& start = graph[0][0]; // 起点 (0, 0)
                Graph.SetStart(start);
                const std::shared_ptr<Node>& goal = graph[4][4];  // 终点 (4, 4)
                Graph.SetGoal(goal);

                const auto& _start = Graph.getStartNode();
                const auto& _goal = Graph.getGoalNode();
                LOG(INFO) << "start: " << _start << "goal: " << _goal;
                // 创建 A* 算法对象
                AStar astar(Graph, start, goal);

                astar.PrintGraph();

                int choice;
                std::cout << "----Choose a algorithm:----\n";
                std::cout << "1: 欧几里得距离\n";
                std::cout << "2: 曼哈顿距离\n";
                std::cout << "3: 对角距离\n";
                std::cout << "4: 读取文件配置\n";

                std::cout << "Please input: ";
                std::cin >> choice;
                std::cout << "------Output------\n";
                std::function<double(const std::shared_ptr<Node>&, const std::shared_ptr<Node>&)> get_heuristic;
                if (!fileExist("config/heuristic.json")) {
                    LOG(INFO) << "\nFile is not exist, please check again!";
                }

                std::ifstream read_config("config/heuristic.json");
                switch (choice)
                {
                case 1:
                    std::cout << "choose euclideanDistance.\n";
                    get_heuristic = AStar::euclideanDistance;
                    break;
                case 2:
                    std::cout << "choose manhattanDistance.\n";
                    get_heuristic = AStar::manhattanDistance;
                    break;
                case 3:
                    std::cout << "choose diagonalDistance.\n";
                    get_heuristic = AStar::diagonalDistance;
                    break;
                case 4:
                    std::cout << "-----Read JSON-----\n";
                    if (read_config.is_open()) {
                        try {
                            nlohmann::json json_data;
                            read_config >> json_data;

                            if (json_data.contains("algorithm")) {
                                std::string name = json_data["algorithm"];
                                LOG(INFO) << "algorithm: " << name << "\n";
                            }

                            if (json_data.contains("get_heuristic")) {
                                std::string heuristic = json_data["get_heuristic"];
                                std::cout << "get_heuristic: " << heuristic << std::endl;
                                if (heuristic == "euclideanDistance") {
                                    get_heuristic = AStar::euclideanDistance;
                                    std::cout << "Function set to AStar::euclideanDistance\n";
                                }
                            }


                        }
                        catch (const nlohmann::json::parse_error& e) {
                            std::cerr << "JSON parse error: " << e.what() << "\n";
                        }
                        read_config.close();
                    }
                    else
                    {
                        std::cerr << "Open failed!\n";
                    }
                    break;
                default:
                    break;
                }

                // 执行路径搜索
                if (astar.PathSearch(get_heuristic)) {
                    std::cout << "\n路径搜索成功！路径如下：" << std::endl;
                    astar.PrintPath();
                }
                else {
                    std::cout << "\n路径搜索失败！" << std::endl;
                }
            }

		}
	}
}