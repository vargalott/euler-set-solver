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
#ifndef __PARSER_CLI_HPP__
#define __PARSER_CLI_HPP__

/*
*	Global includes, cli dll exports
*/
#pragma region GIE
#pragma managed

#using <System.dll>
#using <System.Core.dll>

#include "./../include/BasicSetOperation.hpp"
#include "./..//include/Set.hpp"
#include "./..//include/Converter.hpp"

#pragma unmanaged
#pragma endregion

#pragma managed
namespace __InvokingCLR
{
	ref class Set;

	using SetOperand = System::Collections::Generic::List<System::String^>^;

	/*
	*	Implements main class which
	*	parse the expression to evaluating
	*/
	public ref class Parser
	{
	private:
#pragma region Addition_Classes

		/*
		*	Class which represents the
		*	expression entity
		*/
		ref class Expression
		{
		public:
			explicit Expression(System::String^ token);
			explicit Expression(System::String^ token, Expression^ expr);
			explicit Expression(System::String^ token, Expression^ expr_l, Expression^ expr_r);

			property System::Collections::Generic::List<Expression^>^ Arguments
			{
				System::Collections::Generic::List<Expression^>^ get(void);
			};
			property System::String^ Token
			{
				System::String^ get(void);
			};
		private:
			System::String^ token;
			System::Collections::Generic::List<Expression^>^ arguments;
		};
		using SetDictionary = System::Collections::Generic::Dictionary<System::String^, Set^>^;
#pragma endregion
	public:
		explicit Parser(System::String^ expression);

		property SetDictionary Sets
		{
			SetDictionary get(void);
		};
		property System::String^ CurrentOperation
		{
			System::String^ get(void);
		}
		property SetDictionary SetsMainGetter
		{
			SetDictionary get(void);
		};

		Set^ Run(void);
	private:
#pragma region Parser_Private_Zone

		SetDictionary sets;
		System::String^ expression;
		SetOperand tokens;

		std::size_t iterator; std::size_t current_operation;

		std::size_t			__get_priority(System::String^ token);
		System::String^		__parse_t(void);
		Expression^			__parse_be(std::size_t min_p);
		Expression^			__parse(void);
		Expression^			__parse_se(void);
		Set^				__evaluate(Expression^ expr);

#pragma endregion
	};

	/*
	*	Main control class
	*/
	public ref class Parsing
	{
	public:
		static void Run(void);
	};
};

#endif // !__PARSER_CLI_HPP__