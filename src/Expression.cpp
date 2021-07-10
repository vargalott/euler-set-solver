#pragma warning(push)
#pragma warning(disable : 4677)
#pragma warning(disable : 4267)
#pragma warning(disable : 4506)

#include <euler-set-solver/expression.hpp>

#pragma managed

__InvokingCLR::Expression::Expression(System::String ^ token) : token(token){};
__InvokingCLR::Expression::Expression(System::String ^ token, Expression ^ expr)
    : token(token) {
  this->arguments = gcnew System::Collections::Generic::List<Expression ^>();
  this->arguments->Add(expr);
};
__InvokingCLR::Expression::Expression(System::String ^ token,
                                      Expression ^ expr_l, Expression ^ expr_r)
    : token(token) {
  this->arguments = gcnew System::Collections::Generic::List<Expression ^>();
  this->arguments->Add(expr_l);
  this->arguments->Add(expr_r);
};

System::Collections::Generic::List<__InvokingCLR::Expression ^> ^
    __InvokingCLR::Expression::Arguments::get(void) {
  return this->arguments;
};
System::String ^ __InvokingCLR::Expression::Token::get(void) {
  return this->token;
};

#pragma unmanaged
#pragma warning(pop)
