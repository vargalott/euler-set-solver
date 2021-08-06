#include <catch2/catch.hpp>

#include <euler-set-solver/utility.hpp>
#include <euler-set-solver/set.hpp>

#pragma managed

/**
 * ess::clr::set::uni0n test
 */
TEST_CASE( "set::uni0n", "[uni0n]" ) {
  INIT_LIST(comp, {"1", "2", "3", "4"} );
  auto set_comp = gcnew ess::clr::set(comp, "C");

  INIT_LIST(lhs, {"1", "2"} )
  auto set_lhs = gcnew ess::clr::set(lhs, "A");
  INIT_LIST(rhs, {"3", "4"} )
  auto set_rhs = gcnew ess::clr::set(rhs, "B");

  auto set_ret = set_lhs->uni0n(set_rhs);
  bool is_equal = set_ret == set_comp;

  if (!is_equal) {
    PRINT_ASSERTED(set::uni0n,
      set_lhs->set_instance,
      set_rhs->set_instance,
      set_ret->set_instance,
      set_comp->set_instance
    );
  }

  REQUIRE( is_equal );
}

/**
 * ess::clr::set::intersect test
 */
TEST_CASE( "set::intersect", "[intersect]" ) {
  INIT_LIST(comp, {"3", "4"} );
  auto set_comp = gcnew ess::clr::set(comp, "C");

  INIT_LIST(lhs, {"1", "2", "3", "4"} )
  auto set_lhs = gcnew ess::clr::set(lhs, "A");
  INIT_LIST(rhs, {"3", "4", "5", "6"} )
  auto set_rhs = gcnew ess::clr::set(rhs, "B");

  auto set_ret = set_lhs->intersect(set_rhs);
  bool is_equal = set_ret == set_comp;

  if (!is_equal) {
    PRINT_ASSERTED(set::intersect,
      set_lhs->set_instance,
      set_rhs->set_instance,
      set_ret->set_instance,
      set_comp->set_instance
    );
  }

  REQUIRE( is_equal );
}

/**
 * ess::clr::set::substract test
 */
TEST_CASE( "set::substract", "[substract]" ) {
  INIT_LIST(comp, {"1", "2"} );
  auto set_comp = gcnew ess::clr::set(comp, "C");

  INIT_LIST(lhs, {"1", "2", "3", "4"} )
  auto set_lhs = gcnew ess::clr::set(lhs, "A");
  INIT_LIST(rhs, {"3", "4"} )
  auto set_rhs = gcnew ess::clr::set(rhs, "B");

  auto set_ret = set_lhs->substract(set_rhs);
  bool is_equal = set_ret == set_comp;

  if (!is_equal) {
    PRINT_ASSERTED(set::substract,
      set_lhs->set_instance,
      set_rhs->set_instance,
      set_ret->set_instance,
      set_comp->set_instance
    );
  }

  REQUIRE( is_equal );
}

/**
 * ess::clr::set::sdiff test
 */
TEST_CASE( "set::sdiff", "[sdiff]" ) {
  INIT_LIST(comp, {"1", "2", "5", "6"} );
  auto set_comp = gcnew ess::clr::set(comp, "C");

  INIT_LIST(lhs, {"1", "2", "3", "4"} )
  auto set_lhs = gcnew ess::clr::set(lhs, "A");
  INIT_LIST(rhs, {"3", "4", "5", "6"} )
  auto set_rhs = gcnew ess::clr::set(rhs, "B");

  auto set_ret = set_lhs->sdiff(set_rhs);
  bool is_equal = set_ret == set_comp;

  if (!is_equal) {
    PRINT_ASSERTED(set::sdiff,
      set_lhs->set_instance,
      set_rhs->set_instance,
      set_ret->set_instance,
      set_comp->set_instance
    );
  }

  REQUIRE( is_equal );
}
