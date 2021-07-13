#pragma once
#ifndef __PARSER_CLI_HPP__
#define __PARSER_CLI_HPP__

#pragma managed
#include <euler-set-solver/converter.hpp>
#include <euler-set-solver/expression.hpp>
#include <euler-set-solver/set-operator.hpp>
#include <euler-set-solver/set.hpp>


#pragma managed
namespace ess::clr {

ref class set;

using set_operand = System::Collections::Generic::List<System::String^>^;
using set_dict = System::Collections::Generic::Dictionary<System::String^, ess::clr::set^>^;

/**
 * Parsing expression class
 *
 * ...
 *
 * Implements parsing and evaluating functionality
 */
private ref class parser {
public:
  /**
   * Class construnctor
   * Permorm construnction of the intance of the parser
   *
   * @param[in] expr Expression to be processed
   */
  explicit parser(System::String^ expr);

  /**
   * Class field property: sets
   */
  property ess::clr::set_dict sets {
    /**
     * Get the processed sets
     */
    ess::clr::set_dict get(void);
  };
  /**
   * Class field property: current_operation
   */
  property System::String^ current_operation {
    /**
     * Get the current operation number
     */
    System::String^ get(void);
  };

  /**
   * Get the dictionary of the processed sub-expressions
   */
  ess::clr::set_dict dict(void);
  /**
   * Get the result of evaluating parsed expression
   */
  ess::clr::set^ resolve(void);

private:
  ess::clr::set_dict _sets;
  System::String^ _expr;
  ess::clr::set_operand _tokens;

  int _iterator;
  int _current_operation;

  /**
   * Get priority for a given token
   *
   * @param[in] token Token
   */
  int _get_priority(System::String^ token);
  /**
   * Perform expression parsing
   */
  ess::clr::expression^ _parse(void);
  /**
   * Perform token parsing
   */
  System::String^ _parse_token(void);
  /**
   * Perform parsing an unary expression
   */
  ess::clr::expression^ _parse_unary_expr(void);
  /**
   * Perform parsing a binary expression
   *
   * @param[in] min_p Minimal priority for a parsed token
   */
  ess::clr::expression^ _parse_binary_expr(int min_p);
  /**
   * Perform evaluating for a given expression
   *
   * @param[in] expr Expression for evaluating
   */
  ess::clr::set^ _evaluate(ess::clr::expression^ expr);
};

}; // namespace ess::clr

#endif // !__PARSER_CLI_HPP__
