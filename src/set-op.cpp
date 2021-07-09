#pragma warning(push)
#pragma warning(disable:4677)
#pragma warning(disable:4267)
#pragma warning(disable:4506)

#include <euler-set-solver/set-op.hpp>

#pragma managed

using SetOperand = __InvokingCLR::SetOperand;

SetOperand __InvokingCLR::BasicSetSolving::__union(SetOperand left, SetOperand right)
{
	return
	(
		System::Linq::Enumerable::Any(left) || System::Linq::Enumerable::Any(right) ?
		Converter::__cli_str_to_list
		(
			System::Text::RegularExpressions::Regex::Replace
			(
				System::String::Join(" ", System::Linq::Enumerable::Union(left, right)),
				"[ ]+", " "
			)
		) :
		nullptr
	);
};
SetOperand __InvokingCLR::BasicSetSolving::__intersection(SetOperand left, SetOperand right)
{
	return
	(
		System::Linq::Enumerable::Any(left) || System::Linq::Enumerable::Any(right) ?
		Converter::__cli_str_to_list
		(
			System::Text::RegularExpressions::Regex::Replace
			(
				System::String::Join(" ", System::Linq::Enumerable::Intersect(left, right)),
				"[ ]+", " "
			)
		) :
		nullptr
	);
};
SetOperand __InvokingCLR::BasicSetSolving::__substraction(SetOperand left, SetOperand right)
{
	return
	(
		System::Linq::Enumerable::Any(left) || System::Linq::Enumerable::Any(right) ?
		Converter::__cli_str_to_list
		(
			System::Text::RegularExpressions::Regex::Replace
			(
				System::String::Join(" ", System::Linq::Enumerable::Except(left, right)),
				"[ ]+", " "
			)
		) :
		nullptr
	);
};
SetOperand __InvokingCLR::BasicSetSolving::__s_difference(SetOperand left, SetOperand right)
{
	auto su1 = BasicSetSolving::__substraction(left, right);
	auto su2 = BasicSetSolving::__substraction(right, left);
	return BasicSetSolving::__union(su1, su2);
}

#pragma unmanaged
#pragma warning(pop)
