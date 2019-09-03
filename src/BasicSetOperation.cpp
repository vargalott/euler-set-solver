#include "../include/BasicSetOperation.hpp"

#pragma managed

#using <System.dll>
#using <System.Core.dll>

using SetOperand = System::Collections::Generic::List<System::String^>^;

inline System::String^ __InvokingCLR_Set_BasicOperation::__InvokingCLR_Convert::__std_str_to_cli_str(std::string const& convertible)
{
	return gcnew System::String(convertible.c_str());
	// TODO: UTF-8 fix
}
inline std::string __InvokingCLR_Set_BasicOperation::__InvokingCLR_Convert::__cli_str_to_std_str(System::String^ convertible)
{
	return msclr::interop::marshal_as<std::string>(convertible);
};
inline SetOperand __InvokingCLR_Set_BasicOperation::__InvokingCLR_Convert::__cli_str_to_list(System::String^ convertible)
{
	System::Collections::Generic::List<System::String^>^ list = gcnew System::Collections::Generic::List<System::String^>();
	for each (auto elem in convertible->Split(' '))
		list->Add(elem);
	return list;
};

inline System::String^ __InvokingCLR_Set_BasicOperation::__InvokingCLR_BasicSetSolving::__union(SetOperand left, SetOperand right)
{
	return
	(
		System::Linq::Enumerable::Any(left) || System::Linq::Enumerable::Any(right) ?
		System::Text::RegularExpressions::Regex::Replace
		(
			System::String::Join(" ", System::Linq::Enumerable::Union(left, right)),
			"[ ]+", " "
		) :
		__InvokingCLR_BasicSetSolving::__error_str
	);
};
inline System::String^ __InvokingCLR_Set_BasicOperation::__InvokingCLR_BasicSetSolving::__intersection(SetOperand left, SetOperand right)
{
	return
	(
		System::Linq::Enumerable::Any(left) || System::Linq::Enumerable::Any(right) ?
		System::Text::RegularExpressions::Regex::Replace
		(
			System::String::Join(" ", System::Linq::Enumerable::Intersect(left, right)),
			"[ ]+", " "
		) :
		__InvokingCLR_BasicSetSolving::__error_str
	);
};
inline System::String^ __InvokingCLR_Set_BasicOperation::__InvokingCLR_BasicSetSolving::__substraction(SetOperand left, SetOperand right)
{
	return
	(
		System::Linq::Enumerable::Any(left) || System::Linq::Enumerable::Any(right) ?
		System::Text::RegularExpressions::Regex::Replace
		(
			System::String::Join(" ", System::Linq::Enumerable::Except(left, right)),
			"[ ]+", " "
		) :
		__InvokingCLR_BasicSetSolving::__error_str
	);
};
inline System::String^ __InvokingCLR_Set_BasicOperation::__InvokingCLR_BasicSetSolving::__complement(SetOperand left, SetOperand right)
{
	auto su1 = __InvokingCLR_Convert::__cli_str_to_list(__InvokingCLR_BasicSetSolving::__substraction(left, right));
	auto su2 = __InvokingCLR_Convert::__cli_str_to_list(__InvokingCLR_BasicSetSolving::__substraction(right, left));
	return __InvokingCLR_BasicSetSolving::__union(su1, su2);
};

#pragma unmanaged