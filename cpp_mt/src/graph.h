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
  unsigned nearest_harvest_day_ = ENDDAY_;
  vector<vector<CellProperty>> board_;
  int corn_output_ = 0;
  int bean_output_ = 0;
  int total_ = 0;
  explicit Board(int n) : curr_day_(0) {
    board_ = vector<vector<CellProperty>>(n, vector<CellProperty>(n));
    empty_cell_ = n*n;
  }
  Board(const Board& board) {
    curr_day_ = board.curr_day_;
    board_ = board.board_;
    empty_cell_ = board.empty_cell_;
    nearest_harvest_day_ = board.nearest_harvest_day_;
    corn_output_ = board.corn_output_;
    bean_output_ = board.bean_output_;
    total_ = board.total_;
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
    if (curr_day_ < ENDDAY_) return -1;
    if(CanHarvest()){
      return Harvest().total_;
    }
    return total_;
  }
  bool IsFinished() { return GetResult() != -1; }
  bool IsPlantable() {return empty_cell_ > 0;}
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
    if (curr_day_ - board_[i][j].p_day_ >= CORNDAY_ &&
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
      corn_output_ += val;
      board_[i][j].val_ += val;
    }
  }
  void EvalCorn(const int& i, const int& j) {
    int n = board_.size();
    if (curr_day_ - board_[i][j].p_day_ >= BEANDAY_ &&
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
      bean_output_ += val;
      board_[i][j].val_ += val;
    }
  }
  Board Harvest() {
    Board ans(*this);
    int n = board_.size();
    for (unsigned i = 0; i < ans.board_.size(); i++) {
      for (unsigned j = 0; j < ans.board_[0].size(); j++) {
        if (ans.board_[i][j].state_ != State::INIT) {
          ans.EvalBean(i, j);
          ans.EvalCorn(i, j);
        }
      }
    }
    ans.total_ = ans.corn_output_ + ans.bean_output_;
    for (unsigned i = 0; i < ans.board_.size(); i++) {
      for (unsigned j = 0; j < ans.board_[0].size(); j++) {
          if (i >= 0 && j >= 0 && i < n && j < n &&
              board_[i][j].state_ == State::BEAN) {
            ans.board_[i][j].state_ = State::INIT;
            ans.empty_cell_++;
          }
          if (i >= 0 && j >= 0 && i < n && j < n &&
              board_[i][j].state_ == State::CORN) {
            ans.board_[i][j].state_ = State::INIT;
            ans.empty_cell_++;
          }
      }
    }
    ans.nearest_harvest_day_ = ENDDAY_ + 1; //MAXIMUN
    return ans;
  }
  bool Move(const int& i, const int& j, const unsigned& p_day, const State& state) { 
 //   if(!IsMoveLegal(i, j)){return false;}
    if(board_[i][j].state_ == state) {return true;}
    board_[i][j].state_ = state;
    board_[i][j].p_day_ = p_day;
    if(state != State::INIT){
      empty_cell_--;
    }else {
      empty_cell_++;
    }
    if(state == State::CORN && p_day + CORNDAY_ < nearest_harvest_day_){
      nearest_harvest_day_ = p_day + CORNDAY_;
    }
    if(state == State::BEAN && p_day + BEANDAY_ < nearest_harvest_day_){
      nearest_harvest_day_ = p_day + BEANDAY_;
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
    Board path(*this);
    auto steps = path.GetNextStep();
    if(steps.size() == 0 || !IsPlantable()){
      path.curr_day_ = path.nearest_harvest_day_;
    }
    if(CanHarvest()){
      path = Harvest();
    }
    vector<Board> ans;
    dfs(ans, 0, steps, path);
    return ans;
  }
  void dfs(vector<Board>& ans, const int& level, 
           const vector<Cell>& next_step, Board& path){
    path.curr_day_++;
    ans.push_back(path);
    path.curr_day_--;
    int n = next_step.size();
    for(int i = level; i < n; i++){
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
 private:
  const static int ENDDAY_ =  91;
  const static int CORNDAY_ = 90;
  const static int BEANDAY_ = 90;
};
#endif  // CPP_MT_SRC_GRAPH_H_
