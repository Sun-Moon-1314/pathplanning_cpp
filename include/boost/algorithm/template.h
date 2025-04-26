#pragma once
#include "pch.h"

namespace boost {
	namespace algorithm {
		// 算法父类模版
		template <typename Graphtype, typename Nodetype, typename T>
		class PlanAlgorithm {
		protected:
			Graphtype m_Graph;
			std::vector<Nodetype> m_Path;
			Nodetype m_start;
			Nodetype m_goal;
		public:
			// 构造
			PlanAlgorithm(const Graphtype& graph, const Nodetype& start, const Nodetype& goal) :
				m_Graph(graph),
				m_start(start),
				m_goal(goal) {
			}
			// 移动语义
			PlanAlgorithm(Graphtype&& graph, Nodetype&& start, Nodetype&& goal) :
				m_Graph(std::move(graph)),
				m_start(std::move(start)),
				m_goal(std::move(goal)) {
			}

			virtual ~PlanAlgorithm() = default;
			// 获取地图
			Graphtype& GetGraph() {
				return m_Graph;
			}
			const Graphtype& GetGraph() const {
				return m_Graph;
			}
			// 获取路径结果
			const auto& GetPath() const {
				return m_Path;
			}
			// 检查给定节点是否为有效点（在地图范围内且可通行）
			virtual bool isValidPoint(const Nodetype& node) const = 0;

			// 核心路径规划算法
			// 返回值：true 表示成功找到路径，false 表示路径搜索失败。
			// 路径结果存储在成员变量 m_Path 中。
			
			virtual bool PathSearch(std::function<double(const std::shared_ptr<T>&, const std::shared_ptr<T>&)>) = 0;

		};
		

	}
}

