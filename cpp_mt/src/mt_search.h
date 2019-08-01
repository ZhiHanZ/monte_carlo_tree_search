#ifndef CPP_MT_SRC_MT_SEARCH_H_
#define  CPP_MT_SRC_MT_SEARCH_H_
#include "mt_node.h"
class MTSearch{
 public:
   Node* root_;
   MTSearch(Node* root): root_(root){}
   auto TreePolicy(){
    auto curr = root_;
    while(!curr->IsTerminated()){
      if(curr->HasAction()){
        return curr->Expand();
      }else {
        curr = curr->BestChild();
      }
    }
    return curr;
   }
   auto BestAction(int sim_num){
    for(int i = 0; i < sim_num; i++){
       auto curr = TreePolicy(); 
       auto result = curr->RollOut();
       curr->BackProp(result);
    }
    return root_->BestChild(0.0);
   }

};
#endif  //  CPP_MT_SRC_MT_SEARCH_H_
