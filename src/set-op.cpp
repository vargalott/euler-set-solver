#pragma warning(push)
#pragma warning(disable : 4677)
#pragma warning(disable : 4267)
#pragma warning(disable : 4506)

#include <euler-set-solver/set-op.hpp>

#pragma managed

ess::clr::set_operand ess::clr::set_operator::uni0n(ess::clr::set_operand lhs, ess::clr::set_operand rhs) {
  return (System::Linq::Enumerable::Any(lhs) || System::Linq::Enumerable::Any(rhs)
    ? ess::clr::converter::cli_str_to_list(
        System::Text::RegularExpressions::Regex::Replace(
          System::String::Join(" ", System::Linq::Enumerable::Union(lhs, rhs)), "[ ]+", " "
        )
      )
    : nullptr
  );
};
ess::clr::set_operand ess::clr::set_operator::intersect(ess::clr::set_operand lhs, ess::clr::set_operand rhs) {
  return (System::Linq::Enumerable::Any(lhs) || System::Linq::Enumerable::Any(rhs)
    ? ess::clr::converter::cli_str_to_list(
      System::Text::RegularExpressions::Regex::Replace(
        System::String::Join(" ", System::Linq::Enumerable::Intersect(lhs, rhs)), "[ ]+", " "
      )
    )
    : nullptr
  );
};
ess::clr::set_operand ess::clr::set_operator::substract(ess::clr::set_operand lhs, ess::clr::set_operand rhs) {
  return (System::Linq::Enumerable::Any(lhs) || System::Linq::Enumerable::Any(rhs)
    ? ess::clr::converter::cli_str_to_list(
      System::Text::RegularExpressions::Regex::Replace(
        System::String::Join(" ", System::Linq::Enumerable::Except(lhs, rhs)), "[ ]+", " "
      )
    )
    : nullptr
  );
};
ess::clr::set_operand ess::clr::set_operator::sdiff(ess::clr::set_operand lhs, ess::clr::set_operand rhs) {
  return ess::clr::set_operator::uni0n(
    ess::clr::set_operator::substract(lhs, rhs),
    ess::clr::set_operator::substract(rhs, lhs)
  );
};

#pragma unmanaged
#pragma warning(pop)
