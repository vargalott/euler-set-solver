// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

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

#pragma managed
#include "./../include/BasicSetOperation.hpp"
#pragma unmanaged

//#include <Windows.h>

//=========================================================================================================================================
//=========================================================================================================================================
//=========================================================================================================================================
//													DANGEROUS ZONE
//=========================================================================================================================================
//=========================================================================================================================================
//=========================================================================================================================================
#pragma managed

namespace __InvokingCLR
{
	using SetOperand = System::Collections::Generic::List<System::String^>^;
	using SetDictionary = System::Collections::Generic::Dictionary<System::String^, Set^>^;

	public ref class Expression
	{
	public:
		inline explicit Expression(void) = default;
		//inline explicit Expression(Expression const% obj) : tokens(obj.tokens), args(obj.args) {};
		inline explicit Expression(System::String^ token) : token(token) {};
		inline explicit Expression(System::String^ token, Expression^ expr) : token(token)
		{
			this->arguments->Add(expr);
		};
		inline explicit Expression(System::String^ token, Expression^ expr_l, Expression^ expr_r) : token(token)
		{
			this->arguments->Add(expr_l);
			this->arguments->Add(expr_r);
		};

		inline void print(std::size_t count)
		{
			System::String^ tab = "";
			for (std::size_t t = 0; t < count; ++t)
				tab += "\t";
			System::Console::WriteLine(tab + this->token);
			//for arg in self.args:
			//	arg.print(tab_count + 1)
		};

		property System::Collections::Generic::List<Expression^>^ Arguments
		{
			inline System::Collections::Generic::List<Expression^>^ get(void)
			{
				return this->arguments;
			};
		};
		property System::String^ Token
		{
			inline System::String^ get(void)
			{
				return this->token;
			};
		};

	private:
		System::String^ token;
		System::Collections::Generic::List<Expression^>^ arguments;
	};

	public ref class Set
	{
	public:
		explicit Set(void) : set(nullptr), name("") {};
		explicit Set(SetOperand set, System::String^ name) : set(set), name(name) {};

		/*
		*	casting operator to System::String^
		*/
		operator System::String^ (void)
		{
			if (this->set)
				return __InvokingCLR::Converter::__list_to_cli_str(this->set);
			else
				return "{0}";
		};

		property System::String^ Name
		{
			System::String^ get(void)
			{
				return this->name;
			};
		};
		property SetOperand Set_
		{
			inline SetOperand get(void)
			{
				return this->set;
			};
			//inline void set(SetOperand set)
			//{
			//	this->set = set;
			//};
		};

		/*
		*	Computing sets union
		*	openard to parse - "u"
		*/
		inline Set^ __compute_union(Set^ operand)
		{
			Set^ result = gcnew Set();
			result->name = this->name + " n " + operand->name;
			result->set = __InvokingCLR::BasicSetSolving::__union(this->set, operand->set);
			return result;
		};
		/*
		*	Computing sets intersection
		*	openard to parse - "n"
		*/
		inline Set^ __compute_intersection(Set^ operand)
		{
			Set^ result = gcnew Set();
			result->name = this->name + " n " + operand->name;
			result->set = __InvokingCLR::BasicSetSolving::__intersection(this->set, operand->set);
			return result;
		};
		/*
		*	Computing sets complement
		*	openard to parse - "+"
		*/
		inline Set^ __compute_complement(Set^ operand)
		{
			Set^ result = gcnew Set();
			result->name = this->name + " n " + operand->name;
			result->set = __InvokingCLR::BasicSetSolving::__complement(this->set, operand->set);
			return result;
		};
		/*
		*	Computing sets substraction
		*	openard to parse - "\"
		*/
		inline Set^ __compute_substraction(Set^ operand)
		{
			Set^ result = gcnew Set();
			result->name = this->name + " n " + operand->name;
			result->set = __InvokingCLR::BasicSetSolving::__substraction(this->set, operand->set);
			return result;
		};
		/*
		*	Computing sets addition
		*	openard to parse - "_"
		*/
		inline Set^ __compute_addition(Set^ operand)
		{
			Set^ result = gcnew Set();
			result->name = this->name + " n " + operand->name;
			result->set = __InvokingCLR::BasicSetSolving::__addition(this->set, operand->set);
			return result;
		};

	private:

		SetOperand set;
		System::String^ name;
	};

	public ref class Parser
	{
	public:
		inline explicit Parser(void) = default;
		inline explicit Parser(System::String^ expression) : iterator(std::size_t(0)), current_operation(std::size_t(1))
		{
			this->expression = expression->Replace(" ", "");
			//this->expression = System::Text::RegularExpressions::Regex::Replace(expression, "[ ]", " ");
			this->tokens = __InvokingCLR::Converter::__cli_str_to_list(__InvokingCLR::Converter::__std_str_to_cli_str("u n \\ + _ ( )"));

		};

		property SetDictionary Sets
		{
			SetDictionary get(void)
			{
				std::size_t iterator = std::size_t(0);
				SetDictionary dict;

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
						sets->operator[](name) = Set(SetOperand(), name);
					}
					else
						++iterator;
				};
				return this->sets;
			};
		};
		property System::String^ CurrentOperaion
		{
			System::String^ get(void)
			{
				return this->current_operation + ")";
			};
		};

		/* FIRST */
		inline std::size_t		__get_priority(System::String^ token)
		{
			if (this->tokens->Contains(token))
				return std::size_t(1);
			return 0;
		};

		/* SECOND */
		inline System::String^	__parse_t(void)
		{
			if (this->expression->Length > this->iterator)
			{
				if (System::Char::IsUpper(this->expression, this->iterator))
				{
					System::String^ name = "";
					while (this->expression->Length > this->iterator && System::Char::IsUpper(this->expression, this->iterator))
					{
						name += this->expression[this->iterator];
						++this->iterator;
					};
					return name;
				};

				for each (System::String^ token in this->tokens)
				{
					if (this->expression->Substring(this->iterator, token->Length))
					{
						this->iterator += token->Length;
						return token;
					};
				};
			};
			return "";
		};

		/* PRE2-THIRD */ 
		inline Expression^		__parse_be(std::size_t min_p)
		{
			Expression^ expr_l = this->__parse_se();

			for (;;)
			{
				System::String^ operand = this->__parse_t();
				std::size_t priority = this->__get_priority(operand);

				if (priority <= min_p)
				{
					this->iterator -= operand->Length;
					return expr_l;
				};

				Expression^ expr_r = this->__parse_be(priority);
				expr_l = gcnew Expression(operand, expr_l, expr_r);
			};
		};

		/* PRE-THIRD */ 
		inline Expression^		__parse(void)
		{
			return this->__parse_be(0);
		};

		/* THIRD */ 
		inline Expression^		__parse_se(void)
		{
			System::String^ token = this->__parse_t();
			if (!token)
				throw gcnew System::Exception("invalid in");
			if (System::Char::IsUpper(token, 0))
				return gcnew Expression(token); // TODO: fix second param

			if (token == "(")
			{
				Expression^ result = this->__parse();
				if (this->__parse_t() != ")")
					throw gcnew System::Exception("')' expected");
				return result;
			};

			return gcnew Expression(token, this->__parse_se());
		};

		/* MAIN? */ 
		inline Set^ evaluate(Expression^ expr)
		{
			switch (expr->Arguments->Count)
			{
			case 1:
				Set ^ set = this->evaluate(expr->Arguments[0]);

				System::Console::WriteLine(this->CurrentOperaion + " " + expr->Token + " " + set->Name);
				System::Console::WriteLine(this->CurrentOperaion + " " + expr->Token + " " + set);

				++this->current_operation;

				if (expr->Token == "_");
					// TODO: implement addition

				throw gcnew System::Exception("unknow unary operation");

				break;
			case 2:
				Set ^ set_l = this->evaluate(expr->Arguments[0]);
				Set^ set_r = this->evaluate(expr->Arguments[1]);

				System::Console::WriteLine(this->CurrentOperaion + " " + set_l->Name + " " + expr->Token + " " + set_r->Name);
				System::Console::WriteLine(this->CurrentOperaion + " " + set_l + " " + expr->Token + " " + set_r);

				++this->current_operation;

				if (expr->Token == "u")
					return set_l->__compute_union(set_r);
				if (expr->Token == "n")
					return set_l->__compute_intersection(set_r);
				if (expr->Token == "\\")
					return set_l->__compute_substraction(set_r);
				if (expr->Token == "+")
					return set_l->__compute_complement(set_r);

				throw gcnew System::Exception("unknow binary operation");

				break;
			case 0:
				//return this->sets[expr->Token];
				break;
			default:
				throw gcnew System::Exception("unknow operation");
			}
		};

		inline Set^ run(void)
		{
			if (!this->sets);
				//add sets data
			return this->evaluate(this->__parse());
		};

	private:
		System::String^ expression;
		SetOperand tokens;
		SetDictionary sets;

		std::size_t iterator; std::size_t current_operation;

		inline Set^ __compute_dict_union(Set^ set_l, Set^ set_r)
		{
			return gcnew Set(__InvokingCLR::BasicSetSolving::__union(set_l->Set_, set_r->Set_), set_l->Name);
		};
	};
};



#pragma unmanaged
//=========================================================================================================================================
//=========================================================================================================================================
//=========================================================================================================================================



/*
*	Entry Point: managed code
*/
#pragma managed
int __cdecl main(void)
{
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);

#pragma region TEST_1

	//std::string first, second;

	//std::cout << "First set:\t";
	//std::getline(std::cin, first);
	//std::cout << "Second set:\t";
	//std::getline(std::cin, second);

	//std::size_t curr_op; System::String^ res;

	//std::cout << "\nChoose operation:\n\t1 - union\n\t2 - intesection\n\t3 - substraction\n\t4 - complement\n:";
	//(std::cin >> curr_op).get();
	//
	//switch (curr_op)
	//{
	//case 1:
	//	res = __InvokingCLR_Basic_Solve(first, second, __InvokingCLR_Basic__UNION);
	//	break;
	//case 2:
	//	res = __InvokingCLR_Basic_Solve(first, second, __InvokingCLR_Basic__INTERSECTION);
	//	break;
	//case 3:
	//	res = __InvokingCLR_Basic_Solve(first, second, __InvokingCLR_Basic__SUBSTRACTION);
	//	break;
	//case 4:
	//	res = __InvokingCLR_Basic_Solve(first, second, __InvokingCLR_Basic__COMPLEMENT);
	//	break;
	//};

	//for each (auto elem in res)
	//	System::Console::Write(elem);

#pragma endregion

#pragma region TEST_2
	//System::String^ expr = "A+B-C";
	//expr = System::Text::RegularExpressions::Regex::Replace(expr, "[+-]", " ");
	//std::size_t count = 0;

	//for each (auto elem in expr)
	//	if (elem != L' ')
	//		++count;

	//System::Collections::Generic::List<__InvokingCLR::SetOperand>^ all_sets = gcnew System::Collections::Generic::List<__InvokingCLR::SetOperand>();

	//for (std::size_t t = 0; t < count; ++t)
	//{
	//	System::Console::WriteLine("\n{0}: ", t);
	//	auto x = System::Console::ReadLine();

	//	all_sets->Add(__InvokingCLR::Converter::__cli_str_to_list(x));
	//};
#pragma endregion

	



	std::cin.get();
	return 0;
};
#pragma unmanaged