
#include "pch.h"
#include "boost/common/GridGraph.h"
#include "boost/common/node.h"


namespace boost {
	namespace common {
		// init
		GridGraph::GridGraph(int rows, int cols) :
			m_Graph(rows, std::vector<std::shared_ptr<Node>>(cols)), m_Rows(rows), m_Cols(cols) {
			//std::vector < std::vector<std::shared_ptr<Node>> > m_Graph(rows, std::vector<std::shared_ptr<Node>>(cols));
			// 初始化网格图中的节点
			for (int x = 0; x < rows; ++x) {
				for (int y = 0; y < cols; ++y) {
					m_Graph[x][y] = std::make_shared<Node>(Node(x, y));
					m_Graph[x][y]->x = x;
					m_Graph[x][y]->y = y;
					m_Graph[x][y]->is_connect = 0; // 默认通行
					LOG(INFO) << "\n赋值元素初始化检测: (" << m_Graph[x][y]->x << ", " << m_Graph[x][y]->y << ")";
				}
			}
		}

		GridGraph::GridGraph(const GridGraph& other) {

		}
		GridGraph::GridGraph(GridGraph&& other) {

		}

		// get Graph
		const std::vector < std::vector<std::shared_ptr<Node>> >& GridGraph::getGraph() const {
			return m_Graph;
		}
		// get rows
		const int& GridGraph::getRows() const {
			return m_Rows;
		}
		// get cols
		const int& GridGraph::getCols() const {
			return m_Cols;
		}

		// set node
		void GridGraph::SetNode(int x, int y, const std::shared_ptr<Node>& node) {
			m_Graph[x][y] = node;
		}
		// set start
		void GridGraph::SetStart(const std::shared_ptr<Node>& node) {
			m_Start = node;
		}
		std::shared_ptr<Node> GridGraph::getStartNode() const {
			if (!m_Start) {
				std::cerr << "Start node is not initialized!" << std::endl;
				return nullptr;
			}
			return m_Start;
		}
		// set goal
		void GridGraph::SetGoal(const std::shared_ptr<Node>& node) {
			m_Goal = node;
		}
		// get goal
		std::shared_ptr<Node> GridGraph::getGoalNode() const {
			if (!m_Goal) {
				std::cerr << "Goal node is not initialized!" << std::endl;
				return nullptr;
			}
			return m_Goal;
		}
		// set obstacle
		void GridGraph::SetObstacle(const std::shared_ptr<Node>& node) {
			node->is_connect = 1;
		}
		// add neighbor
		void GridGraph::Add_Neighbors(const std::shared_ptr<Node>& node, const std::shared_ptr<Node>& other) {
			node->neighbors.push_back(other);
		}
		// get Neighborhoods
		const std::vector<std::shared_ptr<Node>>& GridGraph::getNeighborhoods(const std::shared_ptr<Node>& node) const {
			return node->get_neighbors();
		}
		// judge obstacle
		bool GridGraph::isobstacle(const std::shared_ptr<Node>& node) const {
			return node->is_connect;
		}
		/*const std::vector < std::vector<std::shared_ptr<Node>> >& GridGraph::operator=(const GridGraph& other) const {
			return other.getGraph();
		}*/
	}
}