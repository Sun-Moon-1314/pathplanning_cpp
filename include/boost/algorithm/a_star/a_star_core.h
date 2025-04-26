#pragma once

#include "boost/algorithm/template.h" // ����ģ������ͷ�ļ�


namespace boost {
    namespace algorithm {
        namespace a_star_core {
            // ���
            struct Node {
                int x = 0, y = 0; // x�������꣬y��������
                float f = 0.0, g = 0.0, h = 0.0; // f���ܴ��ۣ�g��start-currentʵ�ʴ��ۣ�h��current-goal���ƴ���
                int is_connect = 0; // 0��ͨ�У�1���ϰ�
                bool inopen = false;
                bool inclose = false;
                std::weak_ptr<Node> parent; // ���ڵ�
                std::vector< std::shared_ptr<Node> > neighbors; // ֱ�Ӵ洢�ھӽڵ�ָ��
                // ��ͨ����
                Node() {}
                // ��������
                Node(const std::shared_ptr<Node>& node);

                // �ô�const��֤��const������һ��
                bool operator==(const std::shared_ptr<Node>& other) const;

                // ��ȡ�ھӽڵ�
                const std::vector<std::shared_ptr<Node>>& get_neighbors() const ;

                // �������˽�г�Ա��ʵ��Ϊȫ�ֺ���
                friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Node>& ptr);

                ~Node() = default;
            };
            
            struct CompareNode {
                bool operator()(const std::shared_ptr<Node> a_ptr, const std::shared_ptr<Node> b_ptr) const;
            };

            // ���� Graphtype ��һ����ά�����ͼ������ std::vector<std::vector<int>>��
            // Nodetype ��һ����ʾ����Ľṹ�壨���� std::pair<int, int>��
            class AStar : public PlanAlgorithm<std::vector<std::vector<std::shared_ptr<Node>>>, std::shared_ptr<Node>, Node> {
            protected:
                // �����б� ���ȼ�����
                std::priority_queue < std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNode > priority_queue;
            public:
                AStar(const std::vector<std::vector<std::shared_ptr<Node>>>& graph,
                    const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal);

                /*AStar(std::vector<std::vector<std::shared_ptr<Node>>>&& graph, std::shared_ptr<Node>&& start, std::shared_ptr<Node>&& goal);*/

                void PrintGraph();

                bool operator==(const std::shared_ptr<Node>& other);

                // ʵ�ֻ���Ĵ��麯��
                bool isValidPoint(const std::shared_ptr<Node>& point) const override;

                // �Ƿ���ײ��
                bool IsObstacle(const std::shared_ptr<Node>& node);

                // ��ӡ·����
                void PrintPath();

                // ��ȡ��ǰ�ڵ㵽�ھӽڵ�ľ���
                float get_cost(const std::shared_ptr<Node>& current_ptr, const std::shared_ptr<Node>& neighbor_ptr);

                // ŷ����þ���
                //float get_heuristic(const std::shared_ptr<Node>& neighbor_node, const std::shared_ptr<Node>& goal);
                static double euclideanDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal);
                // �����پ���
                static double manhattanDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal);
                // �ԽǾ���
                static double diagonalDistance(const std::shared_ptr<Node>& start, const std::shared_ptr<Node>& goal);
                // ʵ��·�������㷨������򵥵��������������
                
                bool PathSearch(std::function<double(const std::shared_ptr<Node>&, const std::shared_ptr<Node>&)>) override;

                // ����<<
                //std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Node>& ptr);

                static void run_astar_test();
            };
            
        }
    }
}
