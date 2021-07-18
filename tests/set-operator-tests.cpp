#include <catch2/catch.hpp>

#include <euler-set-solver/set-operator.hpp>

#include "utility.hpp"

#pragma managed

/**
 * ess::clr::set_operator::uni0n test
 */
TEST_CASE( "set_operator::uni0n", "[uni0n]" ) {
  INIT_LIST( comp, {"1", "2", "3", "4"} );
  INIT_LIST( lhs, {"1", "2"} );
  INIT_LIST( rhs, {"3", "4"} );

  auto ret = ess::clr::set_operator::uni0n(lhs, rhs);
  bool is_equal = System::Linq::Enumerable::SequenceEqual(ret, comp);

  if (!is_equal) {
    PRINT_ASSERTED(set_operator::uni0n, lhs, rhs, ret, comp );
  }

  REQUIRE( is_equal );
}

/**
 * ess::clr::set_operator::intersect test
 */
TEST_CASE( "set_operator::intersect", "[intersect]" ) {
  INIT_LIST( comp, {"3", "4"} );
  INIT_LIST( lhs, {"1", "2", "3", "4"} );
  INIT_LIST( rhs, {"3", "4", "5", "6"} );

  auto ret = ess::clr::set_operator::intersect(lhs, rhs);
  bool is_equal = System::Linq::Enumerable::SequenceEqual(ret, comp);

  if (!is_equal) {
    PRINT_ASSERTED(set_operator::intersect, lhs, rhs, ret, comp );
  }

  REQUIRE( is_equal );
}

/**
 * ess::clr::set_operator::substract test
 */
TEST_CASE( "set_operator::substract", "[substract]" ) {
  INIT_LIST( comp, {"1", "2"} );
  INIT_LIST( lhs, {"1", "2", "3", "4"} );
  INIT_LIST( rhs, {"3", "4"} );

  auto ret = ess::clr::set_operator::substract(lhs, rhs);
  bool is_equal = System::Linq::Enumerable::SequenceEqual(ret, comp);

  if (!is_equal) {
    PRINT_ASSERTED(set_operator::substract, lhs, rhs, ret, comp );
  }

  REQUIRE( is_equal );
}

/**
 * ess::clr::set_operator::sdiff test
 */
TEST_CASE( "set_operator::sdiff", "[sdiff]" ) {
  INIT_LIST( comp, {"1", "2", "5", "6"} );
  INIT_LIST( lhs, {"1", "2", "3", "4"} );
  INIT_LIST( rhs, {"3", "4", "5", "6"} );

  auto ret = ess::clr::set_operator::sdiff(lhs, rhs);
  bool is_equal = System::Linq::Enumerable::SequenceEqual(ret, comp);

  if (!is_equal) {
    PRINT_ASSERTED(set_operator::sdiff, lhs, rhs, ret, comp );
  }

  REQUIRE( is_equal );
}
