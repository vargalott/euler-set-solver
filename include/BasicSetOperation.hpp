/*
*
*	MIT License
*
*	Copyright(c) 2019 Mykola Symon
*
*	Permission is hereby granted, free of charge, to any person obtaining a copy
*	of this softwareand associated documentation files(the "Software"), to deal
*	in the Software without restriction, including without limitation the rights
*	to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
*	copies of the Software, and to permit persons to whom the Software is
*	furnished to do so, subject to the following conditions :
*
*	The above copyright noticeand this permission notice shall be included in all
*	copies or substantial portions of the Software.
*
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*	SOFTWARE.
*
*/

#pragma once
#ifndef __BASIC_SET_OPERATIONS_CLI_HPP__
#define __BASIC_SET_OPERATIONS_CLI_HPP__

/*
*	Global includes, cli dll exports
*/
#pragma region GIE
#pragma unmanaged

	#include <iostream>

#pragma managed

	#using <System.dll>
	#using <System.Core.dll>

	#include "./Converter.hpp"

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
	public ref class BasicSetSolving
	{
	public:
		inline static SetOperand __union(SetOperand left, SetOperand right);
		inline static SetOperand __intersection(SetOperand left, SetOperand right);
		inline static SetOperand __substraction(SetOperand left, SetOperand right);
		inline static SetOperand __complement(SetOperand left, SetOperand right);
		inline static SetOperand __addition(SetOperand left, SetOperand right);
	};
	
	/*
	*	Some preprocessor definitions
	*	which simplify using BasicSetSolving
	*
	*	Should use __InvokingCLR_Basic_Solve with one of four
	*	types of operations
	*/
	#pragma region __InvokingCLR_Preprocessor_definitions

	#define __InvokingCLR_Basic__UNION			__InvokingCLR::BasicSetSolving::__union
	#define __InvokingCLR_Basic__INTERSECTION	__InvokingCLR::BasicSetSolving::__intersection
	#define __InvokingCLR_Basic__SUBSTRACTION	__InvokingCLR::BasicSetSolving::__substraction
	#define __InvokingCLR_Basic__COMPLEMENT		__InvokingCLR::BasicSetSolving::__complement

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
};
#pragma unmanaged

#endif // !__BASIC_SET_OPERATIONS_CLI_HPP__