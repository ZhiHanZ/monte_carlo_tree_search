#ifndef CPP_MT_SRC_MT_NODE_H_
#define CPP_MT_SRC_MT_NODE_H_
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <random>
#include "graph.h"
using std::log;
using std::sqrt;
using std::vector;
class Node {
 public:
  Board board_;
  Node* parant_ = nullptr;
  vector<Node*> childs_;
  vector<Board> untried_actions_;
  int max_score_ = 0;
  unsigned num_of_visit_ = 0;
  Node(const Board& board): board_(board) {
    untried_actions_ = board_.GetNextBoard();
  }
  Node(const Board& board, Node* parent) : board_(board), parant_(parent) {
    untried_actions_ = board_.GetNextBoard();
  }
  bool HasAction() { return untried_actions_.size() != 0; }
  vector<Board> GetActions() { return untried_actions_; }
  int GetMaxScore() { return max_score_; }
  unsigned GetNumVisit() { return num_of_visit_; }
  bool IsTerminated() { return board_.IsFinished(); }
  static double ValueOfNode(const Node* node, double c_param = 1.414) {
    return 1.0 * node->max_score_ / node->num_of_visit_ +
           1.0 * c_param *
               sqrt((2.0 * log(node->parant_->num_of_visit_) /
                     node->num_of_visit_));
  }
  static bool ValCompare(const Node* n1, const Node* n2, const double& c_param = 1.414) {
    if (n1->num_of_visit_ == 0) {
      return false;
    }
    if (n2->num_of_visit_ == 0) {
      return true;
    }
    return ValueOfNode(n1, c_param) < ValueOfNode(n2, c_param);
  }
  Node* BestChild(const double& c_param = 1.414) {
    int argMax = std::distance(
        childs_.begin(),
        std::max_element(childs_.begin(), childs_.end(), [&c_param](const Node* n1,const Node* n2) {
                                                          return ValCompare(n1, n2, c_param);}));
    return childs_[argMax];
  }
  //OK
  Node* Expand() {
    auto action = untried_actions_.back();
    untried_actions_.pop_back();
    auto child = new Node(action, this);
    childs_.push_back(child);
    return child;
  }
  //OK
  static Board RollOutPolicy(const vector<Board>& boards){
      std::vector<Board> out;
      size_t nelems = 1;
      std::sample(boards.begin(), boards.end(), std::back_inserter(out),
                nelems, std::mt19937{std::random_device{}()});
      return out[0];
  }
  //OK
  int RollOut(){
    Board board(board_);
    while(!board.IsFinished()){
      auto possible = board.GetNextBoard();
      board = RollOutPolicy(possible);
    }
    return board.GetResult();
  }
  void BackProp(const int& result){
    num_of_visit_++;
    if(result > max_score_) max_score_ = result;
    if(parant_ != nullptr){
      parant_->BackProp(result);
    }
  }
  ~Node(){
  }
};
#endif  //  CPP_MT_SRC_MT_NODE_H_
