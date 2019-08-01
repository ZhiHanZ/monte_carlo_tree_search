#include "mt_node.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "graph.h"
using std::cout;
using std::endl;
TEST(test, eval) {
  Board board(2);
  ASSERT_EQ(false, board.IsFinished());
  Node* node = new Node(board);
 // std::cout << node->RollOutPolicy(node->GetActions()).toString() << std::endl;
    auto child = node->Expand();
    ASSERT_EQ(node, child->parant_);
    int result = child->RollOut();
    int max = child->max_score_;
    std::cout << max << std::endl;
    child->BackProp(result);
    max = child->max_score_;
    std::cout << result << std::endl;
    std::cout << max << std::endl;
    std::cout << child->parant_->max_score_ << std::endl;
}
// test whether we can add elements (if key exists, do nothing)
int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
