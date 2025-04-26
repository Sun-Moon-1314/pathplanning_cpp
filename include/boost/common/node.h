#pragma once
#include "pch.h"

namespace boost {
    namespace common {
        struct Node {
            int x = 0, y = 0; // x�������꣬y��������
            float f = 0.0, g = 0.0, h = 0.0; // f���ܴ��ۣ�g��start-currentʵ�ʴ��ۣ�h��current-goal���ƴ���
            int is_connect = 0; // 0��ͨ�У�1���ϰ�
            std::weak_ptr<Node> parent; // ���ڵ�
            std::vector< std::shared_ptr<Node> > neighbors; // ֱ�Ӵ洢�ھӽڵ�ָ��
            // ��ͨ����
            Node(int in_x, int in_y);
            // ��������
            Node(const std::shared_ptr<Node>& node);

            // �ô�const��֤��const������һ��
            bool operator==(const std::shared_ptr<Node>& other) const;

            // ��ȡ�ھӽڵ�
            const std::vector<std::shared_ptr<Node>>& get_neighbors() const;

            // �������˽�г�Ա��ʵ��Ϊȫ�ֺ���
            friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Node>& ptr);

            ~Node() = default;
        };
    }
}
