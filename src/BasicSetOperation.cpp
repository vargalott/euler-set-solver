// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "./../include/BasicSetOperation.hpp"

#pragma managed

using SetOperand = __InvokingCLR::SetOperand;

inline SetOperand __InvokingCLR::BasicSetSolving::__union(SetOperand left, SetOperand right)
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
inline SetOperand __InvokingCLR::BasicSetSolving::__intersection(SetOperand left, SetOperand right)
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
inline SetOperand __InvokingCLR::BasicSetSolving::__substraction(SetOperand left, SetOperand right)
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
inline SetOperand __InvokingCLR::BasicSetSolving::__complement(SetOperand left, SetOperand right)
{
	auto su1 = BasicSetSolving::__substraction(left, right);
	auto su2 = BasicSetSolving::__substraction(right, left);
	return BasicSetSolving::__union(su1, su2);
};

#pragma unmanaged