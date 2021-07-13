#pragma once
#ifndef __EXPRESSION_CLI_HPP__
#define __EXPRESSION_CLI_HPP__

#pragma managed
namespace ess::clr {

/**
 * Store expression with its args
 *
 * ...
 *
 * Implements expression storing functionality
 */
private ref class expression {
public:
  /**
   * Class construnctor
   * Permorm construnction of the intance of the expression
   *
   * @param[in] token Token to be processed
   */
  explicit expression(System::String^ token);
  /**
   * Class construnctor
   * Permorm construnction of the intance of the expression
   *
   * @param[in] token Token to be processed
   * @param[in] expr Another expression(binary)
   */
  explicit expression(System::String^ token, ess::clr::expression^ expr);
  /**
   * Class construnctor
   * Permorm construnction of the intance of the expression
   *
   * @param[in] token Token to be processed
   * @param[in] lhs Another expression(left-hand operand)
   * @param[in] rhs Another expression(right-hand operand)
   */
  explicit expression(System::String^ token, ess::clr::expression^ lhs, ess::clr::expression^ rhs);

  /**
   * Class field property: args
   */
  property System::Collections::Generic::List<ess::clr::expression^>^ args {
    /**
     * Get the current arguments of the expression
     */
    System::Collections::Generic::List<ess::clr::expression^>^ get(void);
  };
  /**
   * Class field property: token
   */
  property System::String^ token {
    /**
     * Get the current token of the expression
     */
    System::String^ get(void);
  };

private:
  System::String^ _token;
  System::Collections::Generic::List<ess::clr::expression^>^ _args;
};

}; // namespace ess::clr

#endif // !__EXPRESSION_CLI_HPP__
