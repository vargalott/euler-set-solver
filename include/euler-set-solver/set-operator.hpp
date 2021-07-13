#pragma once
#ifndef __SET_OP_CLI_HPP__
#define __SET_OP_CLI_HPP__

#pragma managed
#include <euler-set-solver/converter.hpp>


#pragma managed
namespace ess::clr {

using set_operand = System::Collections::Generic::List<System::String^>^;

/**
 * Basic set binary operators
 *
 * ...
 *
 * Implements basic set operators: union, intersection,
 * substraction, symmetric difference
 */
private ref class set_operator {
public:
  /**
   * Perform union for a given instances of sets
   *
   * @param[in] lhs left-hand set operand
   * @param[in] rhs right-hand set operand
   */
  static ess::clr::set_operand uni0n(
    ess::clr::set_operand lhs, ess::clr::set_operand rhs
  );
  /**
   * Perform intersection for a given instances of sets
   *
   * @param[in] lhs left-hand set operand
   * @param[in] rhs right-hand set operand
   */
  static ess::clr::set_operand intersect(
    ess::clr::set_operand lhs, ess::clr::set_operand rhs
  );
  /**
   * Perform substraction for a given instances of sets
   *
   * @param[in] lhs left-hand set operand
   * @param[in] rhs right-hand set operand
   */
  static ess::clr::set_operand substract(
    ess::clr::set_operand lhs, ess::clr::set_operand rhs
  );
  /**
   * Perform symmetric difference for a given instances of sets
   *
   * @param[in] lhs left-hand set operand
   * @param[in] rhs right-hand set operand
   */
  static ess::clr::set_operand sdiff(
    ess::clr::set_operand lhs, ess::clr::set_operand rhs
  );
};

}; // namespace ess::clr

#endif // !__SET_OP_CLI_HPP__
