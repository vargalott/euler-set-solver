#pragma once
#ifndef __UTILITY_CLI_HPP__
#define __UTILITY_CLI_HPP__

#include <catch2/catch.hpp>

/**
 * Wrap given values into cli::array then convert to ess::clr::set_operand
 */
#define INIT_LIST(var, ...) \
  ess::clr::set_operand var = gcnew System::Collections::Generic::List<System::String^>( \
    safe_cast<System::Collections::Generic::IEnumerable<System::String^>^>( \
      gcnew array<System::String^>##__VA_ARGS__ \
    ) \
  );

/**
 * Print wrong expression info when assertion failed for a given
 * lhs, rhs, ret and comp values
 */
#define PRINT_ASSERTED(operator, lhs, rhs, ret, comp) \
  UNSCOPED_INFO( \
    "<" #operator ">(" #lhs ", " #rhs ") : " #ret " = { " + \
    ess::clr::converter::cli_str_to_std_str(System::String::Join(", ", lhs)) + " } @ { " + \
    ess::clr::converter::cli_str_to_std_str(System::String::Join(", ", rhs)) + " } = { " + \
    ess::clr::converter::cli_str_to_std_str(System::String::Join(", ", ret)) + " } != { " + \
    ess::clr::converter::cli_str_to_std_str(System::String::Join(", ", comp)) + " }" \
  );

#endif // !__UTILITY_CLI_HPP__
