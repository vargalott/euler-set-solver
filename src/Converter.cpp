#pragma warning(push)
#pragma warning(disable : 4677)
#pragma warning(disable : 4267)
#pragma warning(disable : 4506)

#include <euler-set-solver/converter.hpp>

#pragma managed

using SetOperand = __InvokingCLR::SetOperand;

System::String ^ __InvokingCLR::Converter::__std_str_to_cli_str(
                     std::string const &convertible) {
  return gcnew System::String(convertible.c_str());
  // TODO: UTF-8 fix
}
std::string __InvokingCLR::Converter::__cli_str_to_std_str(System::String ^
                                                           convertible) {
  return msclr::interop::marshal_as<std::string>(convertible);
};
SetOperand __InvokingCLR::Converter::__cli_str_to_list(System::String ^
                                                       convertible) {
  SetOperand list =
      gcnew System::Collections::Generic::List<System::String ^>();
  for each (auto elem in convertible->Split(' '))
    list->Add(elem);
  return list;
}
System::String ^
    __InvokingCLR::Converter::__list_to_cli_str(SetOperand convertible) {
  return System::String::Join(" ", convertible);
};
SetOperand __InvokingCLR::Converter::__make_set_from_list(SetOperand list) {
  SetOperand set = gcnew System::Collections::Generic::List<System::String ^>();
  for each (auto elem in System::Linq::Enumerable::Distinct(list))
    set->Add(elem);
  return set;
};

#pragma unmanaged
#pragma warning(pop)
