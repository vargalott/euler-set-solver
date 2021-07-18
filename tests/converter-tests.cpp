#include <catch2/catch.hpp>

#include <euler-set-solver/converter.hpp>

#include "utility.hpp"

#pragma managed

/**
 * ess::clr::converter::std_str_to_cli_str test
 */
TEST_CASE( "converter::std_str_to_cli_str", "[std_str_to_cli_str]") {
  System::String^ comp = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
  System::String^ ret = ess::clr::converter::std_str_to_cli_str(
    std::string("Lorem ipsum dolor sit amet, consectetur adipiscing elit.")
  );

  REQUIRE( ret->Equals(comp) );
}

/**
 * ess::clr::converter::cli_str_to_std_str test
 */
TEST_CASE( "converter::cli_str_to_std_str", "[cli_str_to_std_str]") {
  std::string comp = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
  std::string ret = ess::clr::converter::cli_str_to_std_str(
    gcnew System::String("Lorem ipsum dolor sit amet, consectetur adipiscing elit.")
  );

  REQUIRE( ret == comp );
}

/**
 * ess::clr::converter::cli_str_to_cli_list test
 */
TEST_CASE( "converter::cli_str_to_cli_list", "[cli_str_to_cli_list]") {
  INIT_LIST( comp, {"1", "2", "3", "4"});
  auto ret = ess::clr::converter::cli_str_to_cli_list("1 2 3 4");

  REQUIRE( System::Linq::Enumerable::SequenceEqual(ret, comp) );
}

/**
 * ess::clr::converter::cli_list_to_cli_str test
 */
TEST_CASE( "converter::cli_list_to_cli_str", "[cli_list_to_cli_str]") {
  System::String^ comp = "1 2 3 4";
  INIT_LIST( list, {"1", "2", "3", "4"} );

  auto ret = ess::clr::converter::cli_list_to_cli_str(list);

  REQUIRE( ret->Equals(comp) );
}
