#pragma once
#include "boost/algorithm/template.h" // ����ģ������ͷ�ļ�
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
            // �Զ����ϣ����
            struct PairHash {
                template <typename T1, typename T2>
                std::size_t operator()(const std::pair<T1, T2>& pair) const;
            };
            // ���� Graphtype ��һ����ά�����ͼ������ std::vector<std::vector<int>>��
            // Nodetype ��һ����ʾ����Ľṹ�壨���� std::pair<int, int>��
            class AStar : public PlanAlgorithm<GridGraph, std::shared_ptr<Node>, Node> {
            protected:
                // �����б� ���ȼ�����
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