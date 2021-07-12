#pragma once
#ifndef __CONVERTER_CLI_HPP__
#define __CONVERTER_CLI_HPP__

/*
 *	Global includes, cli dll exports
 */
#pragma region GIE
#pragma unmanaged

#include <string>

#pragma managed

#include <msclr\marshal_cppstd.h>
#include <vcclr.h>

#pragma unmanaged
#pragma endregion

#pragma managed

namespace ess::clr {
  using set_operand = System::Collections::Generic::List<System::String^>^;

  /*
   *	Some converting c++17/cli <-> c++17
   */
  public ref class converter {
  public:
    static System::String^ std_str_to_cli_str(std::string const& str);
    static std::string cli_str_to_std_str(System::String^ str);

    static ess::clr::set_operand cli_str_to_list(System::String^ str);
    static System::String^ list_to_cli_str(ess::clr::set_operand set_operand);

    static ess::clr::set_operand make_set_from_list(ess::clr::set_operand list);
  };
}; // namespace ess::clr

#pragma unmanaged

#endif // !__CONVERTER_CLI_HPP__
