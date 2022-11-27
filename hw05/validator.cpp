#include "validator.h"

#include <variant>
#include <vector>

#include "token.h"


namespace sql {



State SqlValidator::getValue() const{
  return state_;
}

bool SqlValidator::is_valid() const {
  /// TODO: Implement this


  if (std::holds_alternative<state::Invalid>(state_)){
    return false;
  }
  return true; 

}

struct P{

  void operator()(state::AllColumns,token::Comma) const {state::Invalid{};}
  void operator()(state::FromClause,token::Asterisks) const {state::Invalid{};}
};

struct Wrapper{

  
  State operator()(state::Start) const {return transition(state::Start{},token);}
  State operator()(state::SelectStmt) const {return transition(state::SelectStmt{},token);}
  State operator()(state::AllColumns) const {return transition(state::AllColumns{},token);}
  State operator()(state::FromClause) const {return transition(state::FromClause{},token);}
  State operator()(state::MoreColumns) const {return transition(state::MoreColumns{},token);}
  State operator()(state::NamedColumn) const {return transition(state::NamedColumn{},token);}
  State operator()(state::TableName) const {return transition(state::TableName{},token);}
  State operator()(state::Valid) const {return transition(state::Valid{},token);}
  State operator()(state::Invalid) const {return transition(state::Invalid{},token);}

  Token token; 

  Wrapper(Token &t):token{t}{};

  // State operator()(state::Valid b,auto & a) const {return state::Invalid{};}
};


void SqlValidator::handle(Token token) {
  /// TODO: Implement this

  Wrapper W{token};

  state_ = std::visit(W,state_); 


}



bool is_valid_sql_query(std::vector<Token> tokens){

  SqlValidator validator; 

  for(auto & token:tokens){

    if (validator.is_valid()){

        validator.handle(token);

    }else{
      return false;
    }  
  }
  if(std::holds_alternative<state::Valid>(validator.getValue())){
    return true;
  }
  return false; 
}

struct TransitionFromStartVisitor {
  /// Only the `Select` token advances the FSM from the `Start` state
  /// TODO: Correct the behaviour
  State operator()(token::Select) const { return state::SelectStmt{};}

  /// All the other tokens, put it in the invalid state
  State operator()(token::From) const { return state::Invalid{};}
  State operator()(token::Comma) const { return state::Invalid{};}
  State operator()(token::Asterisks) const { return state::Invalid{};}
  State operator()(token::Semicolon) const { return state::Invalid{};}
  State operator()(token::Identifier) const { return state::Invalid{};}
};

struct TransitionFromSelectStmtVisitor {
  /// Only the `Select` token advances the FSM from the `Start` state
  /// TODO: Correct the behaviouur
  State operator()(token::Select) const { return state::Invalid{};}
  State operator()(token::From) const { return state::Invalid{};}
  State operator()(token::Comma) const { return state::Invalid{};}
  State operator()(token::Asterisks) const { return state::AllColumns{};}
  State operator()(token::Semicolon) const { return state::Invalid{};}
  State operator()(token::Identifier) const { return state::NamedColumn{};}
};

struct TransitionFromAllVisitor {
  /// Only the `Select` token advances the FAll the `Start` state
  /// TODO: Correct the behaviouur
  State operator()(token::Select) const { return state::Invalid{};}
  State operator()(token::From) const { return state::FromClause{};}
  State operator()(token::Comma) const { return state::Invalid{};}
  State operator()(token::Asterisks) const { return state::Invalid{};}
  State operator()(token::Semicolon) const { return state::Invalid{};}
  State operator()(token::Identifier) const { return state::Invalid{};}
};


struct TransitionFromNamedVisitor {
  /// Only the `Select` token advances the FSM from the `Start` state
  /// TODO: Correct the behaviouur
  State operator()(token::Select) const { return state::Invalid{};}
  State operator()(token::From) const { return state::FromClause{};}
  State operator()(token::Comma) const { return state::MoreColumns{};}
  State operator()(token::Asterisks) const { return state::Invalid{};}
  State operator()(token::Semicolon) const { return state::Invalid{};}
  State operator()(token::Identifier) const { return state::Invalid{};}
};



struct TransitionFromMoreVisitor {
  /// Only the `Select` token advances the FSM from the `Start` state
  /// TODO: Correct the behaviouur
  State operator()(token::Select) const { return state::Invalid{};}
  State operator()(token::From) const { return state::Invalid{};}
  State operator()(token::Comma) const { return state::Invalid{};}
  State operator()(token::Asterisks) const { return state::Invalid{};}
  State operator()(token::Semicolon) const { return state::Invalid{};}
  State operator()(token::Identifier) const { return state::NamedColumn{};}
};

struct TransitionFromFromVisitor{

  State operator()(token::Select) const { return state::Invalid{};}
  State operator()(token::From) const { return state::Invalid{};}
  State operator()(token::Comma) const { return state::Invalid{};}
  State operator()(token::Asterisks) const { return state::Invalid{};}
  State operator()(token::Semicolon) const { return state::Invalid{};}
  State operator()(token::Identifier) const { return state::TableName{};}

};

struct TransitionFromTableVisitor{


  /// valid state
  State operator()(token::Semicolon) const { return state::Valid{};}

  /// Invalid states
  State operator()(token::Select) const { return state::Invalid{};}
  State operator()(token::From) const { return state::Invalid{};}
  State operator()(token::Comma) const { return state::Invalid{};}
  State operator()(token::Asterisks) const { return state::Invalid{};}
  State operator()(token::Identifier) const { return state::Invalid{};}

};



State transition(state::Start, Token token) {
  return std::visit(TransitionFromStartVisitor{},token.value());
}

State transition(state::Valid, Token token) {
  // TODO: Implement


  return state::Valid{};
}

State transition(state::Invalid, Token token) {
  // TODO: Implement
  return state::Invalid{};
}

State transition(state::FromClause, Token token){
  return std::visit(TransitionFromFromVisitor{}, token.value());
}
State transition(state::SelectStmt, Token token){

  return std::visit(TransitionFromSelectStmtVisitor{},token.value());
}
State transition(state::AllColumns, Token token){

  
  return std::visit(TransitionFromAllVisitor{},token.value());
}
State transition(state::NamedColumn, Token token){
  return std::visit(TransitionFromNamedVisitor{},token.value());
}

State transition(state::MoreColumns, Token token){
  return std::visit(TransitionFromMoreVisitor{},token.value());
}
State transition(state::TableName, Token token){
  return std::visit(TransitionFromTableVisitor{},token.value());
}

} // namespace sql
