#include "graph.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
// test whether test can be inited successfully
TEST(test, init) {
  Board board(2);
  ASSERT_EQ(2, board.board_.size());
  ASSERT_EQ(2, board.board_[0].size());
  for (int i = 0; i < board.board_.size(); i++) {
    for (int j = 0; j < board.board_.size(); j++) {
      ASSERT_EQ(State::INIT, board.board_[i][j].state_);
      ASSERT_EQ(0, board.board_[i][j].val_);
      ASSERT_EQ(0, board.board_[i][j].p_day_);
    }
  }

  Board board2(100);
  ASSERT_EQ(100, board2.board_.size());
  ASSERT_EQ(100, board2.board_[0].size());
  for (int i = 0; i < board2.board_.size(); i++) {
    for (int j = 0; j < board2.board_.size(); j++) {
      ASSERT_EQ(State::INIT, board2.board_[i][j].state_);
      ASSERT_EQ(0, board2.board_[i][j].val_);
      ASSERT_EQ(0, board2.board_[i][j].p_day_);
      board2.board_[i][j].val_ = 10;
      board2.board_[i][j].state_ = State::BEAN;
      board2.board_[i][j].p_day_ = 101;
    }
  }
  Board board3(board2);
  for (int i = 0; i < board3.board_.size(); i++) {
    for (int j = 0; j < board3.board_.size(); j++) {
      ASSERT_EQ(State::BEAN, board3.board_[i][j].state_);
      ASSERT_EQ(10, board3.board_[i][j].val_);
      ASSERT_EQ(101, board3.board_[i][j].p_day_);
      board3.board_[i][j].val_ = 0;
    }
  }
  for (int i = 0; i < board2.board_.size(); i++) {
    for (int j = 0; j < board2.board_.size(); j++) {
      ASSERT_EQ(10, board2.board_[i][j].val_);
    }
  }
}
TEST(test, eval) { 
  Board board(2);
  ASSERT_EQ(false, board.IsFinished());
  board.curr_day_ = 100;
  ASSERT_EQ(0, board.GetResult());
  ASSERT_EQ(true, board.IsFinished());
  for (int i = 0; i < board.board_.size(); i++) {
    for (int j = 0; j < board.board_.size(); j++) {
      board.board_[i][j].val_ = 10;
    }
  }
  ASSERT_EQ(40, board.GetResult());
  ASSERT_EQ(true, board.IsFinished());
}
TEST(test, eval2){
  Board board(2);
  board.curr_day_ = 100;
  ASSERT_EQ(0, board.GetResult());
  ASSERT_EQ(true, board.IsFinished());
  for (int i = 0; i < board.board_.size(); i++) {
    for (int j = 0; j < board.board_.size(); j++) {
      board.board_[i][j].state_ = State::BEAN;
    }
  }
  Board ans = board.Harvest();
  ASSERT_EQ(40, ans.GetResult());
  ASSERT_EQ(true, ans.IsFinished());
  board.board_[0][0].state_ = State::CORN;
  ans = board.Harvest();
  ASSERT_EQ(58, ans.GetResult());
  ASSERT_EQ(true, ans.IsFinished());
  board.board_[1][1].state_ = State::CORN;
  ans = board.Harvest();
  ASSERT_EQ(54, ans.GetResult());
  ASSERT_EQ(true, ans.IsFinished());
}
// test whether we can add elements (if key exists, do nothing)
int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
