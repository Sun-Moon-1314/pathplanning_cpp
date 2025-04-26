#include "pch.h"
#include "boost/algorithm/a_star/a_star.h"
#include "gtest/gtest.h"

using namespace boost::algorithm::a_star;


class AStarFunctionTest : public ::testing::Test {
protected:
    std::unique_ptr<GridGraph> graph_ptr;
    std::unique_ptr<AStar> astar_ptr;
    
    std::shared_ptr<Node> goal;

    
    void SetUp() override {
        graph_ptr = std::make_unique<GridGraph>( 5, 5 );
        const auto& graph = graph_ptr->getGraph();
        int rows = graph_ptr->getRows();
        int cols = graph_ptr->getCols();

        // 设置障碍物
        graph[1][2]->is_connect = 1; // (1, 2) 是障碍
        graph[2][2]->is_connect = 1; // (2, 2) 是障碍
        graph[3][2]->is_connect = 1; // (3, 2) 是障碍

        // 设置邻居节点
        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                if (x >= 1 && graph[x - 1][y]->is_connect == 0) {
                    graph_ptr->Add_Neighbors(graph[x][y], graph[x - 1][y]); // 上
                }
                if (x < rows - 1 && graph[x + 1][y]->is_connect == 0) {
                    graph_ptr->Add_Neighbors(graph[x][y], graph[x + 1][y]); // 下
                }
                if (y > 0 && graph[x][y - 1]->is_connect == 0) {
                    graph_ptr->Add_Neighbors(graph[x][y], graph[x][y - 1]); // 左
                }
                if (y < cols - 1 && graph[x][y + 1]->is_connect == 0) {
                    graph_ptr->Add_Neighbors(graph[x][y], graph[x][y + 1]); // 右
                }
            }
        }
        // 定义起点和终点
        const std::shared_ptr<Node>& start = graph[0][0]; // 起点 (0, 0)
        graph_ptr->SetStart(start);
        const std::shared_ptr<Node>& goal = graph[4][4];  // 终点 (4, 4)
        graph_ptr->SetGoal(goal);
        // 创建 A* 算法对象
        astar_ptr = std::make_unique<AStar>(*graph_ptr, start, goal);
        astar_ptr->PrintGraph();
    }

    void TearDown() override {

    }
};


TEST_F(AStarFunctionTest, TestIsObstacle) {
    const auto& _start = graph_ptr->getStartNode();
    const auto& _goal = graph_ptr->getGoalNode();
    LOG(INFO) << "start: " << _start << "goal: " << _goal;
    bool result1 = astar_ptr->IsObstacle(_start);
    EXPECT_EQ(result1, false);
    bool result2 = astar_ptr->IsObstacle(_start);
    EXPECT_EQ(result1, false);
}

#define GOOGLE_TEST
#ifdef GOOGLE_TEST
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    std::cin.get();
    return result;
}
#endif