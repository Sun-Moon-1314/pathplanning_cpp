#pragma once
#include "pch.h"
#include "graph.h"
namespace boost {
	namespace common {
		class GridGraph : public boost::common::Graph {
		private:
			std::vector < std::vector<std::shared_ptr<Node>> > m_Graph;
			std::shared_ptr <Node> m_Start;
			std::shared_ptr <Node> m_Goal;
			int m_Rows;
			int m_Cols;
		public:
			GridGraph(int rows, int cols);
			GridGraph(const GridGraph& other);
			GridGraph(GridGraph&& other);

			// get Graph
			virtual const std::vector < std::vector<std::shared_ptr<Node>> >& getGraph() const override;
			// get rows
			virtual const int& getRows() const;
			// get cols
			virtual const int& getCols() const;
			// set node
			void SetNode(int x, int y, const std::shared_ptr<Node>& node);
			// set start
			void SetStart(const std::shared_ptr<Node>& node);
			// get Start
			virtual std::shared_ptr<Node> getStartNode() const override;
			// set goal
			void SetGoal(const std::shared_ptr<Node>& node);
			// get goal
			virtual std::shared_ptr<Node> getGoalNode() const override;
			// set obstacle
			void SetObstacle(const std::shared_ptr<Node>& node);
			// add neighbor
			void Add_Neighbors(const std::shared_ptr<Node>& node, const std::shared_ptr<Node>& other);
			// get Neighborhoods
			virtual const std::vector<std::shared_ptr<Node>>& getNeighborhoods(const std::shared_ptr<Node>& node) const override;
			// judge obstacle
			virtual bool isobstacle(const std::shared_ptr<Node>& node) const override;

			/*const std::vector < std::vector<std::shared_ptr<Node>> >& operator=(const GridGraph& other) const;
		*/
		};
	}
}