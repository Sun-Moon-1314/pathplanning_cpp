#pragma once

#include "node.h"

namespace boost {
	namespace common {
		class Graph {
		public:
			virtual ~Graph() = default;
			// get Graph
			virtual const std::vector < std::vector<std::shared_ptr<Node>> >& getGraph() const = 0;
			// get rows
			virtual const int& getRows() const = 0;
			// get cols
			virtual const int& getCols() const = 0;
			// get Start
			virtual std::shared_ptr<Node> getStartNode() const = 0;
			// get goal
			virtual std::shared_ptr<Node> getGoalNode() const = 0;
			// get Neighborhoods
			virtual const std::vector<std::shared_ptr<Node>>& getNeighborhoods(const std::shared_ptr<Node>& node) const = 0;
			// judge obstacle
			virtual bool isobstacle(const std::shared_ptr<Node>& node) const = 0;
		};
	}
}