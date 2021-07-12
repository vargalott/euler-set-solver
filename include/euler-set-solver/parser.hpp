#pragma once
#ifndef __PARSER_CLI_HPP__
#define __PARSER_CLI_HPP__

/*
 *	Global includes, cli dll exports
 */
#pragma region GIE
#pragma managed

#include <euler-set-solver/converter.hpp>
#include <euler-set-solver/expression.hpp>
#include <euler-set-solver/set-op.hpp>
#include <euler-set-solver/set.hpp>

#pragma unmanaged
#pragma endregion

#pragma managed

namespace ess::clr {
  ref class set;

  using set_operand = System::Collections::Generic::List<System::String^>^;
  using set_dict = System::Collections::Generic::Dictionary<System::String^, ess::clr::set_inner^>^;

  /*
   *	Implements main class which
   *	parse the expression to evaluating
   */
  private ref class parser {
  public:
    explicit parser(System::String^ expr);

    property ess::clr::set_dict sets { ess::clr::set_dict get(void); };
    property System::String^ current_operation { System::String^ get(void); };

    ess::clr::set_dict dict(void);
    ess::clr::set_inner^ resolve(void);

  private:
    ess::clr::set_dict _sets;
    System::String^ _expr;
    ess::clr::set_operand _tokens;

    int _iterator;
    int _current_operation;

    int _get_priority(System::String^ token);
    System::String^ _parse_token(void);
    ess::clr::expression^ _parse_be(int min_p);
    ess::clr::expression^ _parse(void);
    ess::clr::expression^ _parse_se(void);
    ess::clr::set_inner^ _evaluate(ess::clr::expression^ expr);
  };
}; // namespace ess::clr

#pragma unmanaged

#endif // !__PARSER_CLI_HPP__
