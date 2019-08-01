#include "mt_node.h"
#include "mt_search.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "graph.h"
using std::cout;
using std::endl;
TEST(test, eval) {
  Board board(4);
  ASSERT_EQ(false, board.IsFinished());
  Node* node = new Node(board);
  MTSearch* tree = new MTSearch(node); 
  auto BestChild = tree->BestAction(1000);
  cout << BestChild->max_score_ << endl;
  cout << BestChild->board_.toString() << endl;
}
// test whether we can add elements (if key exists, do nothing)
int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
