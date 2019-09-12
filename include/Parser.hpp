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
			inline explicit Expression(System::String^ token) : token(token) {};
			inline explicit Expression(System::String^ token, Expression^ expr) : token(token)
			{
				this->arguments = gcnew System::Collections::Generic::List<Expression^>();
				this->arguments->Add(expr);
			};
			inline explicit Expression(System::String^ token, Expression^ expr_l, Expression^ expr_r) : token(token)
			{
				this->arguments = gcnew System::Collections::Generic::List<Expression^>();
				this->arguments->Add(expr_l);
				this->arguments->Add(expr_r);
			};

			System::Collections::Generic::List<Expression^>^ GetArguments(void)
			{
				return this->arguments;
			};
			System::String^ GetToken(void)
			{
				return this->token;
			};
		private:
			System::String^ token;
			System::Collections::Generic::List<Expression^>^ arguments;
		};
		using SetDictionary = System::Collections::Generic::Dictionary<System::String^, Set^>^;
#pragma endregion
	public:
		//inline explicit Parser(void) = default;
		explicit Parser(System::String^ expression);

		property SetDictionary Sets
		{
			inline SetDictionary get(void)
			{
				std::size_t iterator = std::size_t(0);
				SetDictionary dict = gcnew System::Collections::Generic::Dictionary<System::String^, Set^>();

				while (this->expression->Length > iterator)
				{
					if (System::Char::IsUpper(this->expression[iterator]))
					{
						System::String^ name = "";
						while (this->expression->Length > iterator && System::Char::IsUpper(this->expression[iterator]))
						{
							name += this->expression[iterator];
							++iterator;
						};
						dict[name] = gcnew Set(SetOperand(), name);
					}
					else
						++iterator;
				};
				return dict;
			};
		};
		property System::String^ CurrentOperaion
		{
			inline System::String^ get(void)
			{
				return this->current_operation + ": ";
			};
		};
		property SetDictionary SetsMainGetter
		{
			inline SetDictionary get(void)
			{
				return this->sets;
			};
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
		inline static void Run(void)
		{
			System::Console::Write("\n\t\t=== Set calculator ===\n\n\tu - union\n\tn - intersection\n\t+ - complement\n\t\\ - substraction\n\t| - addition\n\nEnter expr: ");

			System::String^ input = System::Console::ReadLine();
			System::Console::Write("\n");

			auto expr = gcnew __InvokingCLR::Parser(input);

			auto dict = gcnew System::Collections::Generic::Dictionary<System::String^, __InvokingCLR::Set^>();

			for each (auto elem in expr->Sets)
			{
				System::Console::Write("Enter {0}: ", elem.Key);
				__InvokingCLR::SetOperand tmp = __InvokingCLR::Converter::__cli_str_to_list(System::Console::ReadLine());
				dict[elem.Key] = gcnew __InvokingCLR::Set(tmp, elem.Key);
			};
			System::Console::Write("\n");
			for each (auto elem in expr->Sets)
			{
				expr->SetsMainGetter->Remove(elem.Key);
				expr->SetsMainGetter->Add(elem.Key, dict[elem.Key]);
			};

			auto result = expr->Run();

			System::Console::Write("\nResult: {" + cli::safe_cast<System::String^>(result) + "}");
		};
	};
};

#endif // !__PARSER_CLI_HPP__