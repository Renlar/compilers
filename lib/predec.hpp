#ifndef COMP_PREDEC
#define COMP_PREDEC

#include <map>
#include <vector>
#include <memory>
#include <utility>

class Scope;
typedef std::shared_ptr<Scope> Scope_sptr;
typedef std::weak_ptr<Scope> Scope_wptr;
typedef std::vector<Scope> ScopeList;

class Block;
typedef std::shared_ptr<Block> Block_sptr;
typedef std::weak_ptr<Block> Block_wptr;
typedef std::vector<Block> BlockList;

class Type;
typedef std::shared_ptr<Type> Type_sptr;
typedef std::weak_ptr<Type> Type_wptr;
typedef std::vector<Type> TypeList;

class Val;
typedef std::shared_ptr<Val> Val_sptr;
typedef std::weak_ptr<Val> Val_wptr;
typedef std::vector<Val> ValList;

class Expression;
typedef std::shared_ptr<Expression> Expression_sptr;
typedef std::weak_ptr<Expression> Expression_wptr;
typedef std::vector<Expression> ExpressionList;

/**
 * These are all pointers to the same val or expression when used in the valmap file.
 */
typedef std::map<Expression, Val> ExpressionValMap;
typedef std::multimap<Val, Expression>  ValExpressionMap;
typedef std::pair<Val_sptr, Expression> ValExpression;
typedef std::vector<ValExpression> ValExpressionList;


class Ast;
typedef std::shared_ptr<Ast> Ast_sptr;
typedef std::weak_ptr<Ast> Ast_wptr;

#endif
