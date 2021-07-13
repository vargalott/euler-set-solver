#pragma warning(push)
#pragma warning(disable: 4267)
#pragma warning(disable: 4506)
#pragma warning(disable: 4677)
#pragma warning(disable: 4715)

#include <euler-set-solver/set.hpp>

#pragma managed
namespace ess::clr {

ess::clr::set::set(void) : _set_instance(nullptr), _name("") {};
ess::clr::set::set(ess::clr::set_operand set, System::String^ name) : _name(name) {
  if (set == nullptr) {
    return;
  }

  this->_set_instance = gcnew System::Collections::Generic::List<System::String^>();
  for each (auto elem in set) {
    if (elem) {
      this->_set_instance->Add(elem);
    }
  }
};

ess::clr::set::operator System::String^ (void) {
  if (this->_set_instance) {
    return ess::clr::converter::cli_list_to_cli_str(this->_set_instance);
  } else {
    return "{}";
  }
};

System::String^ ess::clr::set::name::get(void) {
  return this->_name;
};
ess::clr::set_operand ess::clr::set::set_instance::get(void) {
  return this->_set_instance;
};
void ess::clr::set::set_instance::set(ess::clr::set_operand _set_instance) {
  this->_set_instance = _set_instance;
};

ess::clr::set^ ess::clr::set::uni0n(ess::clr::set^ operand) {
  ess::clr::set^ ret = gcnew ess::clr::set();
  ret->_name = this->_name + "u" + operand->name;
  this->_set_instance != nullptr
    ? ret->set_instance = ess::clr::set_operator::uni0n(this->_set_instance, operand->set_instance)
    : ret->set_instance = ess::clr::set_operator::uni0n(operand->set_instance, operand->set_instance);
  return ret;
};
ess::clr::set^ ess::clr::set::intersect(ess::clr::set^ operand) {
  ess::clr::set^ ret = gcnew ess::clr::set();
  ret->_name = this->_name + "n" + operand->name;
  this->_set_instance != nullptr
    ? ret->set_instance = ess::clr::set_operator::intersect(this->_set_instance, operand->set_instance)
    : ret->set_instance = ess::clr::set_operator::intersect(operand->set_instance, operand->set_instance);
  return ret;
};
ess::clr::set^ ess::clr::set::substract(ess::clr::set^ operand) {
  ess::clr::set^ ret = gcnew ess::clr::set();
  ret->_name = this->_name + "\\" + operand->name;
  this->_set_instance != nullptr
    ? ret->set_instance = ess::clr::set_operator::substract(this->_set_instance, operand->set_instance)
    : ret->set_instance = ess::clr::set_operator::substract(operand->set_instance, operand->set_instance);
  return ret;
};
ess::clr::set^ ess::clr::set::sdiff(ess::clr::set^ operand) {
  ess::clr::set^ ret = gcnew ess::clr::set();
  ret->_name = this->_name + "+" + operand->name;
  this->_set_instance != nullptr
    ? ret->set_instance = ess::clr::set_operator::sdiff(this->_set_instance, operand->set_instance)
    : ret->set_instance = ess::clr::set_operator::sdiff(operand->set_instance, operand->set_instance);
  return ret;
};
// TODO: implement
[[maybe_unused]] ess::clr::set^ ess::clr::set::complement(ess::clr::set^ operand) {
  //ess::clr::set^ ret = gcnew ess::clr::set();
  //ret->_name = this->_name + "X" + operand->name;
  //this->_set_instance != nullptr
  //  ? ret->set_instance = ess::clr::set_operator::X(this->_set_instance, operand->set_instance)
  //  : ret->set_instance = ess::clr::set_operator::X(operand->set_instance, operand->set_instance);
  return nullptr;
};

}; // namespace ess::clr

#pragma warning(pop)
