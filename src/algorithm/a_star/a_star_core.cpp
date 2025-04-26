
#include "pch.h"
#include "boost/utils/Timer.h"
#include "boost/algorithm/a_star/a_star_core.h"
using boost::utils::TimerRecorder;
//#define LOG(x) while (false) std::cout


namespace boost {
    namespace algorithm {
        namespace a_star_core {
            // �ô�const��֤��const������һ��
            bool Node::operator==(const std::shared_ptr<Node>& other) const {
                return this->x == other->x && this->y == other->y;
            }

            // ��ȡ�ھӽڵ�
            const std::vector<std::shared_ptr<Node>>& Node::get_neighbors() const {
                return neighbors;
            }
            // ��������(��vector��Ҫʹ������ȥ���п������°빦��)
            Node::Node(const std::shared_ptr<Node>& other) {
                this->x = other->x;
                this->y = other->y;
                this->f = other->f;
                this->g = other->g;
                this->h = other->h;
                this->is_connect = other->is_connect;
                this->inclose = other->inclose;
                this->inopen = other->inopen;
                this->parent = other;
                this->neighbors.clear();
                //LOG(INFO) << "$$$$$$$$$$$���ÿ�������$$$$$$$$$";
                for (const auto& neighbor : other->neighbors) {
                    if (neighbor != nullptr) {
                        this->neighbors.push_back(neighbor);
                    }
                    else {
                        this->neighbors.push_back(nullptr);
                    }
                }
            }

            std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Node>& node_ptr) {
                return os << "(" << node_ptr->x << ", " << node_ptr->y << ")";
            }

            bool CompareNode::operator()(const std::shared_ptr<Node> a_ptr, const std::shared_ptr<Node> b_ptr) const {
                return a_ptr->f > b_ptr->f;
            }
            

            AStar::AStar(const std::vector<std::vector<std::shared_ptr<Node>>>& graph,
                const std::shared_ptr<Node>& start,
                const std::shared_ptr<Node>& goal) : PlanAlgorithm(graph, start, goal) { 
                for (int x = 0; x < graph.size(); ++x) {
                    for (int y = 0; y < graph[x].size(); ++y) {
                        m_Graph[x][y] = graph[x][y];
                    }
                }
                LOG(INFO) << "\nAStar Init!"; 
            }

            bool AStar::operator==(const std::shared_ptr<Node>& other) {
                return m_start == other;
            }

            // ��д������麯��
            bool AStar::isValidPoint(const std::shared_ptr<Node>& point) const {
                // ʾ��ʵ�֣��жϵ��Ƿ���ͼ�ķ�Χ��
                if (point->x < 0 || point->x >= m_Graph.size() ||
                    point->y < 0 || point->y >= m_Graph[0].size()) {
                    return false;
                }
                else
                {
                    return true;
                }
            }

            // �Ƿ���ײ��
            bool AStar::IsObstacle(const std::shared_ptr<Node>& node) {
                if (node->is_connect == 0) {
                    return false;
                }
                else {
                    std::cout << node << "is obstacle\n";
                    return true;
                }
            }

            // ��ӡ·����
            void AStar::PrintPath() {
                m_Path.push_back(m_goal);
                auto& temp = m_goal;
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

            // ��ӡ��ͼ
            void AStar::PrintGraph() {
                LOG(INFO) << "\n-------Graph:-------";
                for (size_t i = 0; i < m_Graph.size();i++) {
                    for (size_t j = 0; j < m_Graph[i].size();j++) {
                        std::cout << m_Graph[i][j] << " ";
                    }
                    std::cout << "\n";
                }
            }

            // ��ȡ��ǰ�ڵ㵽�ھӽڵ�ľ���
            float AStar::get_cost(const std::shared_ptr<Node>& current_ptr, const std::shared_ptr<Node>& neighbor_ptr) {
                return std::sqrt((current_ptr->x - neighbor_ptr->x) * (current_ptr->x - neighbor_ptr->x) +
                    (current_ptr->y - neighbor_ptr->y) * (current_ptr->y - neighbor_ptr->y));
            }

            // ŷ����þ���
            double AStar::euclideanDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal) {
                return std::sqrt(std::pow(start->x - goal->x, 2) + std::pow(start->y - goal->y, 2));
            }

            // �����پ���
            double AStar::manhattanDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal) {
                return std::abs(start->x - goal->x) + std::abs(start->y - goal->y);
            }

            // �ԽǾ���
            double AStar::diagonalDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal) {
                int dx = std::abs(start->x - goal->x);
                int dy = std::abs(start->y - goal->y);
                return std::max(dx, dy);
            }
            
            // ʵ��·�������㷨������򵥵��������������
            bool AStar::PathSearch(std::function<double(const std::shared_ptr<Node>&, const std::shared_ptr<Node>&)> get_heuristic) {
                PROFILE_SCOPE("PathSearch");
                // ����ʵ��һ���򵥵�������������㷨
                LOG(INFO) << "\nAStar PathSearch";
                const std::shared_ptr<Node>& goal_ptr =m_goal;
                const std::shared_ptr<Node>& start_ptr =m_start;
                if (m_start == m_goal) {
                    m_Path.push_back(m_start);
                    LOG(INFO) << "\nAStar Successful";
                    return true;
                }
                
                // �������
                priority_queue.push(start_ptr);
                int step = 1;
                // ִ�������߼���α���룩
                while (!priority_queue.empty()) {
                    LOG(INFO) << "\n*************��"<< step <<"��*************";
                    
                    LOG(INFO) << "\npriority_queue element number is " << priority_queue.size();
                    LOG(INFO) << "\ntop element is " << priority_queue.top();
                    
                    std::shared_ptr<Node> current_ptr = priority_queue.top();
                    priority_queue.pop();
                    current_ptr->inclose = true;
                    LOG(INFO) << "\n" << "current_ptr:" << current_ptr << " inclose is set to " << current_ptr->inclose;
                    //m_Graph[current_ptr->x][current_ptr->y].inclose = true;
                    LOG(INFO) << "\n" << "m_Graph:" << m_Graph[current_ptr->x][current_ptr->y] << " inclose is set to " << m_Graph[current_ptr->x][current_ptr->y]->inclose;

                    if (current_ptr->inclose != m_Graph[current_ptr->x][current_ptr->y]->inclose) {
                        LOG(ERROR) << "��ǰ�ڵ���ͼ�нڵ��inclose״̬��һ�£�";
                        LOG(ERROR) << " current_ptr: " << &current_ptr << " m_Graph: " << &m_Graph[current_ptr->x][current_ptr->y];
                    }


                    current_ptr->inopen = false;
                    LOG(INFO) << "\n" << "current_ptr:" <<current_ptr << " inopen is set to " << current_ptr->inopen;
                    //m_Graph[current_ptr->x][current_ptr->y].inopen = false;
                    LOG(INFO) << "\n" << "m_Graph:" <<m_Graph[current_ptr->x][current_ptr->y] << " inopen is set to " << m_Graph[current_ptr->x][current_ptr->y]->inopen;
                    // �ҵ�Ŀ��
                    if (current_ptr == goal_ptr) {
                        //PrintPath();
                        LOG(INFO) << "\nAStar Find Goal!";
                        return true;
                    }

                    for (const auto& neighbor_ptr : current_ptr->get_neighbors()) {
                        // ���ϰ���
                        if (IsObstacle(neighbor_ptr)) {
                            continue;
                        }
                        LOG(INFO) << "\n--------------";
                        LOG(INFO) << "\n"<<"neighbor_ptr: " << neighbor_ptr << " inopen: " << neighbor_ptr->inopen;
                        LOG(INFO) << "\n"<<"neighbor_ptr: " << neighbor_ptr << " inclose: " << neighbor_ptr->inclose;
                        LOG(INFO) << "\n--------------";
                        // û�ڹر��б�
                        if (neighbor_ptr->inclose == false) {
                            neighbor_ptr->g = current_ptr->g + get_cost(current_ptr, neighbor_ptr);
                            LOG(INFO) << "\n" << "current_ptr: " << current_ptr
                                << " to neighbor_ptr: " << (neighbor_ptr) <<
                                " g = " << neighbor_ptr->g;
                            neighbor_ptr->h = get_heuristic(neighbor_ptr, m_goal);
                            LOG(INFO) << "\n" << "neighbor_ptr:" << (neighbor_ptr) << " to " <<
                                "m_goal: " << m_goal <<
                                " h = " << neighbor_ptr->h;
                            // û�ڿ����б��µĽڵ�
                            //LOG(INFO) << "current_ptr: " << current_ptr->x << ", " << current_ptr->y;
                            if (neighbor_ptr->inopen == false) {
                                // ����f,g,h�����ѵ�push��priority_queue
                                neighbor_ptr->f = neighbor_ptr->g + neighbor_ptr->h;
                                priority_queue.push(neighbor_ptr);
                                LOG(INFO) << "\n" << neighbor_ptr << " push into priority_queue\n";
                                //LOG(INFO) << "current_ptr: " << current_ptr->x << ", " << current_ptr->y;
                                neighbor_ptr->inopen = true;
                                LOG(INFO) << "\n" << "Neighbor_ptr:" << neighbor_ptr << " InOpen is set to " << neighbor_ptr->inopen;

                                neighbor_ptr->parent = current_ptr;
                                LOG(INFO) << "\n" << neighbor_ptr << " Parent is " << neighbor_ptr->parent.lock();
                                LOG(INFO) << "\n";
                            }
                            // �ڿ����б�
                            else
                            {
                                if ((neighbor_ptr->g + neighbor_ptr->h) < neighbor_ptr->f)
                                    neighbor_ptr->f = neighbor_ptr->g + neighbor_ptr->h;
                                LOG(INFO) << "\n";
                            }
                        }
                        else
                        {
                            LOG(INFO) << "\n" << neighbor_ptr << " is in closelist!";
                            LOG(INFO) << "\n";
                            continue;
                        }
                    }
                    step++;
                }
                LOG(INFO) << "\nAStar Fall!";
                // ��������ʧ��
                return false;
            }

            // ŷ����þ���
            /*double get_heuristic(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal) {
                return std::sqrt((goal->x - start->x) * (goal->x - start->x) +
                    (goal->y - start->y) * (goal->y - start->y));
            }*/

            
            
            // ��ȡ�ļ��Ƿ����
            bool fileExist(const std::string& filename) {
                std::ifstream infine(filename);
                return infine.good();
            }

            // ���в���
            void AStar::run_astar_test() {
                
                // ����һ���򵥵� 5x5 ����ͼ��0 ��ʾͨ�У�1 ��ʾ�ϰ�
                std::vector<std::vector<std::shared_ptr<Node>>> graph(5, std::vector<std::shared_ptr<Node>>(5));

                // ��ʼ������ͼ�еĽڵ�
                for (int x = 0; x < graph.size(); ++x) {
                    for (int y = 0; y < graph[x].size(); ++y) {
                        graph[x][y] = std::make_shared<Node>(Node());
                        graph[x][y]->x = x;
                        graph[x][y]->y = y;
                        graph[x][y]->is_connect = 0; // Ĭ��ͨ��
                        LOG(INFO) << "\n��ֵԪ�س�ʼ�����: (" << graph[x][y]->x << ", " << graph[x][y]->y << ")";
                    }
                }

                // �����ϰ���
                graph[1][2]->is_connect = 1; // (1, 2) ���ϰ�
                graph[2][2]->is_connect = 1; // (2, 2) ���ϰ�
                graph[3][2]->is_connect = 1; // (3, 2) ���ϰ�

                // �����ھӽڵ�
                for (int x = 0; x < graph.size(); ++x) {
                    for (int y = 0; y < graph[x].size(); ++y) {
                        if (x > 0 && graph[x - 1][y]->is_connect == 0) {
                            graph[x][y]->neighbors.push_back(graph[x - 1][y]); // ��
                        }
                        if (x < graph.size()-1 && graph[x + 1][y]->is_connect == 0) {
                            graph[x][y]->neighbors.push_back(graph[x + 1][y]); // ��
                        }
                        if (y > 0 && graph[x][y - 1]->is_connect == 0) {
                            graph[x][y]->neighbors.push_back(graph[x][y - 1]); // ��
                        }
                        if (y < graph.size()-1 && graph[x][y + 1]->is_connect == 0) {
                            graph[x][y]->neighbors.push_back(graph[x][y + 1]); // ��
                        }
                    }
                }

                // ���������յ�
                const std::shared_ptr<Node>& start = graph[0][0]; // ��� (0, 0)
                const std::shared_ptr<Node>& goal = graph[4][4];  // �յ� (4, 4)

                // ���� A* �㷨����
                AStar astar(graph, start, goal);
                
                astar.PrintGraph();

                int choice;
                std::cout << "----Choose a algorithm:----\n";
                std::cout << "1: ŷ����þ���\n";
                std::cout << "2: �����پ���\n";
                std::cout << "3: �ԽǾ���\n";
                std::cout << "4: ��ȡ�ļ�����\n";

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

                // ִ��·������
                if (astar.PathSearch(get_heuristic)) {
                    std::cout << "\n·�������ɹ���·�����£�" << std::endl;
                    astar.PrintPath();
                }
                else {
                    std::cout << "\n·������ʧ�ܣ�" << std::endl;
                }
            }

        }
    }
}

