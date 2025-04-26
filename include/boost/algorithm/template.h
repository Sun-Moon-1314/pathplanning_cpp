#pragma once
#include "pch.h"

namespace boost {
	namespace algorithm {
		// �㷨����ģ��
		template <typename Graphtype, typename Nodetype, typename T>
		class PlanAlgorithm {
		protected:
			Graphtype m_Graph;
			std::vector<Nodetype> m_Path;
			Nodetype m_start;
			Nodetype m_goal;
		public:
			// ����
			PlanAlgorithm(const Graphtype& graph, const Nodetype& start, const Nodetype& goal) :
				m_Graph(graph),
				m_start(start),
				m_goal(goal) {
			}
			// �ƶ�����
			PlanAlgorithm(Graphtype&& graph, Nodetype&& start, Nodetype&& goal) :
				m_Graph(std::move(graph)),
				m_start(std::move(start)),
				m_goal(std::move(goal)) {
			}

			virtual ~PlanAlgorithm() = default;
			// ��ȡ��ͼ
			Graphtype& GetGraph() {
				return m_Graph;
			}
			const Graphtype& GetGraph() const {
				return m_Graph;
			}
			// ��ȡ·�����
			const auto& GetPath() const {
				return m_Path;
			}
			// �������ڵ��Ƿ�Ϊ��Ч�㣨�ڵ�ͼ��Χ���ҿ�ͨ�У�
			virtual bool isValidPoint(const Nodetype& node) const = 0;

			// ����·���滮�㷨
			// ����ֵ��true ��ʾ�ɹ��ҵ�·����false ��ʾ·������ʧ�ܡ�
			// ·������洢�ڳ�Ա���� m_Path �С�
			
			virtual bool PathSearch(std::function<double(const std::shared_ptr<T>&, const std::shared_ptr<T>&)>) = 0;

		};
		

	}
}

