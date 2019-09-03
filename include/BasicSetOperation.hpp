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
#ifndef __BASIC_SET_OPERATIONS_CLI__
#define  __BASIC_SET_OPERATIONS_CLI__

/*
*	Global includes, cli dll exports
*/
#pragma region GIE
#pragma unmanaged

	#include <iostream>
	#include <string>

#pragma managed

	#using <System.dll>
	#using <System.Core.dll>

	#include <vcclr.h>
	#include <msclr\marshal_cppstd.h>

#pragma unmanaged
#pragma endregion

#pragma managed
namespace __InvokingCLR_Set_BasicOperation
{
	using SetOperand = System::Collections::Generic::List<System::String^>^;

	/*
	*	Some converting c++17/cli <-> c++17
	*/
	public ref class __InvokingCLR_Convert
	{
	public:
		inline static System::String^ __std_str_to_cli_str(std::string const& convertible);
		inline static std::string __cli_str_to_std_str(System::String^ convertible);

		inline static SetOperand __cli_str_to_list(System::String^ convertible);
	};

	/*
	*	 Implementation of basic set operation :
	*	- union
	*	- intersection
	*	- substraction
	*	- complement
	*	Methods take a two Lists which contains Strings and returning String
	*/
	public ref class __InvokingCLR_BasicSetSolving
	{
	public:
		inline static System::String^ __union(SetOperand left, SetOperand right);
		inline static System::String^ __intersection(SetOperand left, SetOperand right);
		inline static System::String^ __substraction(SetOperand left, SetOperand right);
		inline static System::String^ __complement(SetOperand left, SetOperand right);
	private:
		static System::String^ __error_str = gcnew System::String("Not enough data");
	};
	
	/*
	*	Some preprocessor definitions
	*	which simplify using __InvokingCLR_BasicSetSolving
	*
	*	Should use __InvokingCLR_Basic_Solve with one of four
	*	types of operations
	*/
	#pragma region __InvokingCLR_Preprocessor_definitions

	#define __InvokingCLR_Basic__UNION			__InvokingCLR_Set_BasicOperation::__InvokingCLR_BasicSetSolving::__union
	#define __InvokingCLR_Basic__INTERSECTION	__InvokingCLR_Set_BasicOperation::__InvokingCLR_BasicSetSolving::__intersection
	#define __InvokingCLR_Basic__SUBSTRACTION	__InvokingCLR_Set_BasicOperation::__InvokingCLR_BasicSetSolving::__substraction
	#define __InvokingCLR_Basic__COMPLEMENT		__InvokingCLR_Set_BasicOperation::__InvokingCLR_BasicSetSolving::__complement

	#define __InvokingCLR_Basic_Prepare_Solving(operand)							\
		 __InvokingCLR_Set_BasicOperation::__InvokingCLR_Convert::__cli_str_to_list \
		(																			\
			__InvokingCLR_Set_BasicOperation::__InvokingCLR_Convert					\
			::__std_str_to_cli_str((operand))										\
		)
	#define __InvokingCLR_Basic_Solve(left_set, right_set, operation)				\
		(operation)																	\
		(																			\
			__InvokingCLR_Basic_Prepare_Solving(left_set),							\
			__InvokingCLR_Basic_Prepare_Solving(right_set)							\
		);

	#pragma endregion 
	// __InvokingCLR_Preprocessor_definitions
};
#pragma unmanaged

#endif // !__BASIC_SET_OPERATIONS_CLI__