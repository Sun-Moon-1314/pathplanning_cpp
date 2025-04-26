#pragma once
#include "pch.h"

namespace boost {
    namespace common {
        struct Node {
            int x = 0, y = 0; // x：横坐标，y：纵坐标
            float f = 0.0, g = 0.0, h = 0.0; // f：总代价，g：start-current实际代价，h：current-goal估计代价
            int is_connect = 0; // 0：通行，1：障碍
            std::weak_ptr<Node> parent; // 父节点
            std::vector< std::shared_ptr<Node> > neighbors; // 直接存储邻居节点指针
            // 普通构造
            Node(int in_x, int in_y);
            // 拷贝构造
            Node(const std::shared_ptr<Node>& node);

            // 该处const保证与const的输入一致
            bool operator==(const std::shared_ptr<Node>& other) const;

            // 获取邻居节点
            const std::vector<std::shared_ptr<Node>>& get_neighbors() const;

            // 允许访问私有成员，实际为全局函数
            friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Node>& ptr);

            ~Node() = default;
        };
    }
}
