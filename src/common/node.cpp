#include "pch.h"
#include "boost/common/node.h"

namespace boost {
    namespace common {
        // �ô�const��֤��const������һ��
        bool Node::operator==(const std::shared_ptr<Node>& other) const {
            return this->x == other->x && this->y == other->y;
        }

        // ��ȡ�ھӽڵ�
        const std::vector<std::shared_ptr<Node>>& Node::get_neighbors() const {
            return neighbors;
        }

        std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Node>& node_ptr) {
            if (node_ptr == nullptr) {
                return os << "(nullptr)";
            }
            return os << "(" << node_ptr->x << ", " << node_ptr->y << ")";
        }
        // ��ʼ��
        Node::Node(int in_x, int in_y) : x(in_x), y(in_y) { }
        // ��������(��vector��Ҫʹ������ȥ���п������°빦��)
        Node::Node(const std::shared_ptr<Node>& other) {
            //LOG(INFO) << "���ÿ�������!";
            this->x = other->x;
            this->y = other->y;
            this->f = other->f;
            this->g = other->g;
            this->h = other->h;
            this->is_connect = other->is_connect;
            this->parent = other;
            this->neighbors.clear();
            
            for (const auto& neighbor : other->neighbors) {
                if (neighbor != nullptr) {
                    this->neighbors.push_back(neighbor);
                }
                else {
                    this->neighbors.push_back(nullptr);
                }
            }
        }
    }
}