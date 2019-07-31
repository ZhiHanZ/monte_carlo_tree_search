#ifndef CPP_MT_SRC_GRAPH_H_
#define CPP_MT_SRC_GRAPH_H_
#include <vector>
using std::vector;
// state of one given cell
enum State { CORN, BEAN, INIT, MATURE };
// Cell is the basic unit for one farm
// x_, y_: the coordinate of Cell
// p_day_: the day planting corps
// state: current state of Cell
class Cell {
 public:
  int x_;
  int y_;
  unsigned p_day_;
  State state_;
  Cell(int x, int y, unsigned p_day, State state)
      : x_(x), y_(y), p_day_(p_day), state_(state) {}
};
class CellProperty {
 public:
  int val_ = 0;
  unsigned p_day_ = 0;
  State state_ = State::INIT;
  CellProperty() {}
  CellProperty(int val, unsigned p_day, State state)
      : val_(val), p_day_(p_day), state_(state) {}
};
class Board {
 public:
  // current day of the farm
  unsigned curr_day_;
  vector<vector<CellProperty>> board_;
  explicit Board(int n) : curr_day_(0) {
    board_ = vector<vector<CellProperty>>(n, vector<CellProperty>(n));
  }
  Board(const Board& board) {
    curr_day_ = board.curr_day_;
    board_ = board.board_;
  }
  int GetResult() {
    if (curr_day_ < 91) return -1;
    int ret = 0;
    for (unsigned i = 0; i < board_.size(); i++) {
      for (unsigned j = 0; j < board_[0].size(); j++) {
        ret += board_[i][j].val_;
      }
    }
    return ret;
  }
  bool IsFinished() { return GetResult() != -1; }
  bool IsMoveLegal(const int& x, const int& y, const State& state) {
    const int m = board_.size();
    if (x < 0 || y < 0 || x >= m || y >= m || state != INIT) {
      return false;
    } else {
      return true;
    }
  }
  void EvalBean(const int& i, const int& j) {
    int n = board_.size();
    if (curr_day_ - board_[i][j].p_day_ >= 90 &&
        board_[i][j].state_ == State::CORN) {
      int val = 10;
      for (int ii = i - 1; ii < i + 2; ii++) {
        for (int jj = j - 1; jj < j + 2; jj++) {
          if (ii >= 0 && jj >= 0 && ii < n && jj < n &&
              board_[ii][jj].state_ == State::BEAN) {
            val++;
          }
        }
      }
      board_[i][j].val_ += val;
    }
  }
  void EvalCorn(const int& i, const int& j) {
    int n = board_.size();
    if (curr_day_ - board_[i][j].p_day_ >= 90 &&
        board_[i][j].state_ == State::BEAN) {
      int val = 10;
      for (int ii = i - 1; ii < i + 2; ii++) {
        for (int jj = j - 1; jj < j + 2; jj++) {
          if (ii >= 0 && jj >= 0 && ii < n && jj < n &&
              board_[ii][jj].state_ == State::CORN) {
            val = 15;
            break;
          }
        }
      }
      board_[i][j].val_ += val;
    }
  }
  Board Harvest() {
    Board ans(*this);
    for (unsigned i = 0; i < ans.board_.size(); i++) {
      for (unsigned j = 0; j < ans.board_[0].size(); j++) {
        if (ans.board_[i][j].state_ != State::INIT) {
          ans.EvalBean(i, j);
          ans.EvalCorn(i, j);
        }
      }
    }
    for (unsigned i = 0; i < ans.board_.size(); i++) {
      for (unsigned j = 0; j < ans.board_[0].size(); j++) {
        if (ans.board_[i][j].state_ != State::INIT) {
          ans.board_[i][j].state_ = State::INIT;
        }
      }
    }
    return ans;
  }
  Board Move() { return Board(9); }
};
#endif  // CPP_MT_SRC_GRAPH_H_
