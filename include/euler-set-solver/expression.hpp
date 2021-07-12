#pragma once
#ifndef __EXPRESSION_CLI_HPP__
#define __EXPRESSION_CLI_HPP__

/*
 *	Global includes, cli dll exports
 */
#pragma region GIE
#pragma managed

#pragma unmanaged
#pragma endregion

#pragma managed
namespace ess::clr {

  private ref class expression {
  public:
    explicit expression(System::String^ token);
    explicit expression(System::String^ token, ess::clr::expression^ expr);
    explicit expression(System::String^ token, ess::clr::expression^ lhs, ess::clr::expression^ rhs);

    property System::Collections::Generic::List<ess::clr::expression^>^ args {
      System::Collections::Generic::List<ess::clr::expression^>^ get(void);
    };
    property System::String^ token { System::String^ get(void); };

  private:
    System::String^ _token;
    System::Collections::Generic::List<ess::clr::expression^>^ _args;
  };
}; // namespace ess::clr
#pragma unmanaged

#endif // !__EXPRESSION_CLI_HPP__
