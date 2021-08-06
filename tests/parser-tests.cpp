#include <catch2/catch.hpp>

#include <euler-set-solver/utility.hpp>
#include <euler-set-solver/parser.hpp>

#pragma managed

/**
 * ess::clr::parser::dict test
 */
TEST_CASE( "parser::dict", "[dict]" ) {
  auto comp = gcnew System::Collections::Generic::Dictionary<System::String^, ess::clr::set^>();
  comp["A"] = gcnew ess::clr::set(ess::clr::set_operand(), "A");
  comp["B"] = gcnew ess::clr::set(ess::clr::set_operand(), "B");
  comp["C"] = gcnew ess::clr::set(ess::clr::set_operand(), "C");

  auto expr = gcnew ess::clr::parser("AuBnC");
  auto ret = expr->dict();

  auto ret_data = gcnew System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>;
  auto comp_data = gcnew System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>;

  for each (System::Collections::Generic::KeyValuePair<System::String^, ess::clr::set^> elem in ret) {
    ret_data->Add(gcnew System::Tuple<System::String^, System::String^>(elem.Key->ToString(), elem.Value->name));
  }
  for each (System::Collections::Generic::KeyValuePair<System::String^, ess::clr::set^> elem in comp) {
    comp_data->Add(gcnew System::Tuple<System::String^, System::String^>(elem.Key->ToString(), elem.Value->name));
  }

  REQUIRE( !System::Linq::Enumerable::Any(System::Linq::Enumerable::Except(ret_data, comp_data)) );
}
