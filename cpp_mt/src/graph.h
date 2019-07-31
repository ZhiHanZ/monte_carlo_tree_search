#ifndef CPP_MT_SRC_GRAPH_H_
#define CPP_MT_SRC_GRAPH_H_
#include <vector>
#include <string>
using std::string;
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
  Cell(int x, int y, unsigned p_day)
      : x_(x), y_(y), p_day_(p_day){}
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
  // All cells are in the board_
  unsigned empty_cell_ = 0;
  unsigned nearest_harvest_day_ = 91;
  vector<vector<CellProperty>> board_;
  explicit Board(int n) : curr_day_(0) {
    board_ = vector<vector<CellProperty>>(n, vector<CellProperty>(n));
    empty_cell_ = n;
  }
  Board(const Board& board) {
    curr_day_ = board.curr_day_;
    board_ = board.board_;
    empty_cell_ = board.empty_cell_;
    nearest_harvest_day_ = board.nearest_harvest_day_;
  }
  string toString(){
    string curr;
    int n = board_.size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        curr.push_back('|');
        switch (board_[i][j].state_){
        case State::INIT:
          curr.push_back('0');
          break;
        case State::CORN:
          curr.push_back('1');
          break;
        case State::BEAN:
          curr.push_back('2');
          break;
        default:
          break;
        }
        curr.push_back('|');
      }
      curr.push_back('\n');
    }
    return curr;
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
  bool IsPlantable() {return empty_cell_ < board_.size();}
  bool CanHarvest() {return curr_day_ >= nearest_harvest_day_;}
  bool IsMoveLegal(const int& x, const int& y) {
    const int m = board_.size();
    if (x < 0 || y < 0 || x >= m || y >= m || board_[x][y].state_ != INIT) {
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
    ans.nearest_harvest_day_ += 90;
    return ans;
  }
  bool Move(const int& i, const int& j, const unsigned& p_day, const State& state) { 
 //   if(!IsMoveLegal(i, j)){return false;}
    board_[i][j].state_ = state;
    board_[i][j].p_day_ = p_day;
    if(p_day + 90 < nearest_harvest_day_){
      nearest_harvest_day_ = p_day + 90;
    }
    return true;
  }
  vector<Cell> GetNextStep(){
    vector<Cell> vec;
    int n = board_.size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (board_[i][j].state_ == State::INIT) {
          vec.push_back({i, j, curr_day_});
        }
      }
    }
    return vec;
  }
  //next possible node in the next day
  vector<Board> GetNextBoard(){
    vector<Board> ans;
    //Helper(ans, 0, 0, 0);
    Board path(*this);
    auto steps = GetNextStep();
    dfs(ans, 0, steps, path);
    return ans;
  }
  void dfs(vector<Board>& ans, const int& level, 
           const vector<Cell>& next_step, Board& path){
    ans.push_back(path);
    for(int i = level; i < next_step.size(); i++){
      int ii = next_step[i].x_;
      int jj = next_step[i].y_;
      auto state = path.board_[ii][jj].state_;
      auto p_day = path.board_[ii][jj].p_day_;
      path.Move(next_step[i].x_, next_step[i].y_, next_step[i].p_day_, State::CORN);
      dfs(ans, i + 1, next_step, path);
      path.Move(ii, jj, p_day, state);
      path.Move(next_step[i].x_, next_step[i].y_, next_step[i].p_day_, State::BEAN);
      dfs(ans, i + 1, next_step, path);
      path.Move(ii, jj, p_day, state);
    }
  }
  void dfs(vector<Board>& ans, const int& level, Board& path){
    int n = path.board_.size();
    if(level == n*n){
      ans.push_back({path});
      return;
    }
    for(int i = level; i < n*n; i++){
      int ii =  i%n;
      int jj =  i/n;
      auto state = path.board_[ii][jj].state_;
      auto p_day = path.board_[ii][jj].p_day_;
      if(path.IsMoveLegal(ii, jj)){
        path.Move(ii, jj, path.curr_day_, State::CORN);
        dfs(ans, level + 1, path);
        path.Move(ii, jj, p_day, state);
        path.Move(ii, jj, path.curr_day_, State::BEAN);
        dfs(ans, level + 1, path);
        path.Move(ii, jj, p_day, state);
        dfs(ans, level + 1, path);
      }
    }
  }
  void Helper(vector<Board>& ans, const int& i, const int& j, 
              const int& step){
    int n = board_.size();
    if(step == n*n){
      ans.push_back({*this});
    }
    if(IsMoveLegal(i, j)){
      auto state = board_[i][j].state_;
      auto p_day = board_[i][j].p_day_;
      vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
      Move(i, j, p_day, State::INIT);
      for(auto dir: dirs){
        auto ii = i + dir[0];
        auto jj = j + dir[1];
        Helper(ans, ii, jj, step + 1);
      }
      Move(i, j,curr_day_, State::CORN);
      for(auto dir: dirs){
        auto ii = i + dir[0];
        auto jj = j + dir[1];
        Helper(ans, ii, jj, step + 1);
      }
      board_[i][j].state_ = state;
      board_[i][j].p_day_ = p_day;
      Move(i, j,curr_day_, State::BEAN);
      for(auto dir: dirs){
        auto ii = i + dir[0];
        auto jj = j + dir[1];
        Helper(ans, ii, jj, step + 1);
      }
      board_[i][j].state_ = state;
      board_[i][j].p_day_ = p_day;
    }
  }
};
#endif  // CPP_MT_SRC_GRAPH_H_
