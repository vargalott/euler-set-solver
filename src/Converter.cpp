#pragma warning(push)
#pragma warning(disable : 4677)
#pragma warning(disable : 4267)
#pragma warning(disable : 4506)

#include <euler-set-solver/converter.hpp>

#pragma managed

// TODO: UTF-8 fix
System::String^ ess::clr::converter::std_str_to_cli_str(std::string const& str) {
  return gcnew System::String(str.c_str());
};
std::string ess::clr::converter::cli_str_to_std_str(System::String^ str) {
  return msclr::interop::marshal_as<std::string>(str);
};
ess::clr::set_operand ess::clr::converter::cli_str_to_list(System::String^ str) {
  ess::clr::set_operand list = gcnew System::Collections::Generic::List<System::String^>();
  for each (auto elem in str->Split(' ')) {
    list->Add(elem);
  }
  return list;
};
System::String^ ess::clr::converter::list_to_cli_str(ess::clr::set_operand set_operand) {
  return System::String::Join(" ", set_operand);
};
ess::clr::set_operand ess::clr::converter::make_set_from_list(ess::clr::set_operand list) {
  ess::clr::set_operand set = gcnew System::Collections::Generic::List<System::String^>();
  for each (auto elem in System::Linq::Enumerable::Distinct(list)) {
    set->Add(elem);
  }
  return set;
};

#pragma unmanaged
#pragma warning(pop)
