#pragma once
#ifndef __SET_OP_CLI_HPP__
#define __SET_OP_CLI_HPP__

/*
*	Global includes, cli dll exports
*/
#pragma region GIE
#pragma managed

	#using <System.dll>
	#using <System.Core.dll>

  #include <euler-set-solver/converter.hpp>

#pragma unmanaged
#pragma endregion

#pragma managed
namespace __InvokingCLR
{
	using SetOperand = System::Collections::Generic::List<System::String^>^;

	/*
	*	 Implementation of basic set operation :
	*	- union
	*	- intersection
	*	- substraction
	*	- complement
	*	Methods take a two Lists which contains Strings and returning String
	*/
	private ref class BasicSetSolving
	{
	public:
		static SetOperand __union(SetOperand left, SetOperand right);
		static SetOperand __intersection(SetOperand left, SetOperand right);
		static SetOperand __substraction(SetOperand left, SetOperand right);
		static SetOperand __s_difference(SetOperand left, SetOperand right);
	};

	/*
	*	Some preprocessor definitions
	*	which simplify using BasicSetSolving
	*
	*	Should use __InvokingCLR_Basic_Solve with one of four
	*	types of operations
	*/
#ifdef __InvokingCLR_Macro
	#pragma region __InvokingCLR_Preprocessor_definitions

	#define __InvokingCLR_Basic__UNION			__InvokingCLR::BasicSetSolving::__union
	#define __InvokingCLR_Basic__INTERSECTION	__InvokingCLR::BasicSetSolving::__intersection
	#define __InvokingCLR_Basic__SUBSTRACTION	__InvokingCLR::BasicSetSolving::__substraction
	#define __InvokingCLR_Basic__COMPLEMENT		__InvokingCLR::BasicSetSolving::__complement
	#define __InvokingCLR_Basic__ADDITION		__InvokingCLR::BasicSetSolving::__addition

	/*
	*	Returns Set which contains elements of
	*	operand that was converted to System::String^
	*/
	#define __InvokingCLR_Basic_Prepare_Solving(operand)		\
		__InvokingCLR::Converter::__make_set_from_list			\
		(														\
			__InvokingCLR::Converter::__cli_str_to_list			\
			(													\
				__InvokingCLR::Converter::__std_str_to_cli_str	\
				((operand))										\
			)													\
		)

	/*
	*	Returns System::String^ which contains elements
	*	of the set after basic operation
	*/
	#define __InvokingCLR_Basic_Solve(left_set, right_set, operation)		\
		__InvokingCLR::Converter::__list_to_cli_str							\
		(																	\
			(operation)														\
			(																\
				__InvokingCLR_Basic_Prepare_Solving((left_set)), 			\
				__InvokingCLR_Basic_Prepare_Solving((right_set))			\
			)																\
		)
	#pragma endregion
	// __InvokingCLR_Preprocessor_definitions
#endif // __InvokingCLR_Macro
};
#pragma unmanaged

#endif // !__SET_OP_CLI_HPP__