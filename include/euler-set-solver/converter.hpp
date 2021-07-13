#pragma once
#ifndef __CONVERTER_CLI_HPP__
#define __CONVERTER_CLI_HPP__

#pragma managed
#include <msclr\marshal_cppstd.h>
#include <vcclr.h>

#pragma unmanaged
#include <string>


#pragma managed
namespace ess::clr {

using set_operand = System::Collections::Generic::List<System::String^>^;

/**
 * Data types converter class
 *
 * ...
 *
 * Implements some necessary converts c++/cli <-> stdc++
 */
public ref class converter {
public:
  /**
   * Perform converting to c++/cli string for a given
   * instance of stdc++ string
   *
   * @param[in] str Instance of std::string const& (stdc++)
   */
  static System::String^ std_str_to_cli_str(std::string const& str);
  /**
   * Perform converting to stdc++ string for a given
   * instance of c++/cli string
   *
   * @param[in] str Instance of System::String^ (c++/cli)
   */
  static std::string cli_str_to_std_str(System::String^ str);
  /**
   * Perform converting to c++cli list of string for a given
   * instance of c++/cli string
   *
   * @param[in] str Instance of System::String^ (c++/cli)
   */
  static ess::clr::set_operand cli_str_to_cli_list(System::String^ str);
  /**
   * Perform converting to a c++/cli string for a given
   * instance of c++cli list of string
   *
   * @param[in] set_operand Instance of ess::clr::set_operand (c++/cli)
   */
  static System::String^ cli_list_to_cli_str(ess::clr::set_operand set_operand);
};

}; // namespace ess::clr

#endif // !__CONVERTER_CLI_HPP__
