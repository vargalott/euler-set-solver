#pragma warning(push)
#pragma warning(disable: 4267)
#pragma warning(disable: 4506)
#pragma warning(disable: 4677)
#pragma warning(disable: 4715)

#include <euler-set-solver/expression.hpp>

#pragma managed
namespace ess::clr {

ess::clr::expression::expression(System::String^ token) : _token(token) {};
ess::clr::expression::expression(System::String^ token, ess::clr::expression^ expr) : _token(token) {
  this->_args = gcnew System::Collections::Generic::List<ess::clr::expression^>();
  this->_args->Add(expr);
};
ess::clr::expression::expression(System::String^ token, ess::clr::expression^ lhs, ess::clr::expression^ rhs) : _token(token) {
  this->_args = gcnew System::Collections::Generic::List<ess::clr::expression^>();
  this->_args->Add(lhs);
  this->_args->Add(rhs);
};

System::Collections::Generic::List<ess::clr::expression^>^ ess::clr::expression::args::get(void) {
  return this->_args;
};
System::String^ ess::clr::expression::token::get(void) {
  return this->_token;
};

}; // namespace ess::clr

#pragma warning(pop)
