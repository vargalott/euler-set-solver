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
	ref class Set;
	using SetOperand = System::Collections::Generic::List<System::String^>^;
	using SetDictionary = System::Collections::Generic::Dictionary<System::String^, Set^>^;

	public ref class Expression
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

		//inline void print(std::size_t count)
		//{
		//	System::String^ tab = "";
		//	for (std::size_t t = 0; t < count; ++t)
		//		tab += "\t";
		//	System::Console::WriteLine(tab + this->token);
		//	//for arg in self.args:
		//	//	arg.print(tab_count + 1)
		//};

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

	public ref class Set
	{
	public:
		explicit Set(void) : set(nullptr), name("") {};
		explicit Set(SetOperand set, System::String^ name) : name(name)
		{
			if (set == nullptr)
				return;
			this->set = gcnew System::Collections::Generic::List<System::String^>();
			for each (auto elem in set)
				if (elem)
					this->set->Add(elem);
		};

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
			inline void set(SetOperand set)
			{
				this->set = set;
			};
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
		//inline explicit Parser(void) = default;
		inline explicit Parser(System::String^ expression) : iterator(std::size_t(0)), current_operation(std::size_t(1))
		{
			this->expression = expression->Replace(" ", "");
			//this->expression = System::Text::RegularExpressions::Regex::Replace(expression, "[ ]", " ");
			this->tokens = __InvokingCLR::Converter::__cli_str_to_list(__InvokingCLR::Converter::__std_str_to_cli_str("u n \\ + _ ( )"));
			this->sets = gcnew System::Collections::Generic::Dictionary<System::String^, Set^>();
		};

		property SetDictionary Sets
		{
			SetDictionary get(void)
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
			void set(SetDictionary sets)
			{
				//sets["U"] = gcnew Set(SetOperand(), "U");

				//for each (auto elem in sets)
				//	if (elem.Key != "U")
				//		sets["U"] = this->__compute_dict_union(sets["U"], sets[elem.Key]);

				for each (auto elem in sets)
				{
					this->sets->Add(elem.Key, elem.Value);
					auto x = elem.Value->Set_;
					this->sets[elem.Key]->Set_ = x;
				};
			};
		};
		property System::String^ CurrentOperaion
		{
			System::String^ get(void)
			{
				return this->current_operation + ")";
			};
		};
		property SetDictionary SetsMainGetter
		{
			SetDictionary get(void)
			{
				return this->sets;
			};
		};

		inline Set^ run(void)
		{
			return this->__evaluate(this->__parse());
		};

		
	private:
		SetDictionary sets;
		System::String^ expression;
		SetOperand tokens;
		

		std::size_t iterator; std::size_t current_operation;

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

				for each (System::String ^ token in this->tokens)
				{
					if (this->expression->Substring(this->iterator, token->Length) == token)
					{
						this->iterator += token->Length;
						return token;
					};
				};
			};
			return "";
		};

		/* PRE-THIRD */
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

		/* PRE2-THIRD */
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
				return gcnew Expression(token);

			if (token == "(")
			{
				Expression^ result = this->__parse();
				if (this->__parse_t() != ")")
					throw gcnew System::Exception("')' expected");
				return result;
			};

			return gcnew Expression(token, this->__parse_se());
		};

		/* STEP-EVAL */
		inline Set^ __evaluate(Expression^ expr)
		{
			if (expr->GetArguments() == nullptr)
				return this->sets[expr->GetToken()];
			if (expr->GetArguments()->Count == 1)
			{
				Set^ set = this->__evaluate(expr->GetArguments()[0]);

				System::Console::WriteLine(this->CurrentOperaion + " " + expr->GetToken() + " " + set->Name);
				System::Console::Write("\t" + expr->GetToken() + " {");
				for each (auto elem in set->Set_)
					System::Console::Write(elem + " ");
				System::Console::Write("}\n");

				++this->current_operation;

				if (expr->GetToken() == "_");
				// TODO: implement addition

				throw gcnew System::Exception("unknow unary operation");
			};
			if (expr->GetArguments()->Count == 2)
			{
				Set^ set_l = this->__evaluate(expr->GetArguments()[0]);
				Set^ set_r = this->__evaluate(expr->GetArguments()[1]);

				System::Console::WriteLine(this->CurrentOperaion + " " + set_l->Name + " " + expr->GetToken() + " " + set_r->Name);

				System::Console::Write(this->CurrentOperaion +" { ");
				for each (auto elem in set_l->Set_)
					System::Console::Write(elem + " ");
				System::Console::Write("} " + expr->GetToken() + " { ");
				for each (auto elem in set_r->Set_)
					System::Console::Write(elem + " ");
				System::Console::Write("}\n");



				++this->current_operation;

				if (expr->GetToken() == "u")
					return set_l->__compute_union(set_r);
				if (expr->GetToken() == "n")
					return set_l->__compute_intersection(set_r);
				if (expr->GetToken() == "\\")
					return set_l->__compute_substraction(set_r);
				if (expr->GetToken() == "+")
					return set_l->__compute_complement(set_r);

				throw gcnew System::Exception("unknow binary operation");
			};
			throw gcnew System::Exception("unknow operation");
		};

		/* SUB */
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

	System::Console::Write("\n\t\t=== Set calculator ===\n\n\tu - union\n\tn - intersection\n\t+ - complement\n\t\\ - substraction\n\t_ - addition\n\nEnter expr: ");

	System::String^ input = System::Console::ReadLine();
	auto expr = gcnew __InvokingCLR::Parser(input);

	auto dict = gcnew System::Collections::Generic::Dictionary<System::String^, __InvokingCLR::Set^>();

	for each (auto elem in expr->Sets)
	{
		System::Console::Write("Enter {0}: ", elem.Key);
		__InvokingCLR::SetOperand tmp =__InvokingCLR::Converter::__cli_str_to_list(System::Console::ReadLine());
		dict[elem.Key] = gcnew __InvokingCLR::Set(tmp, elem.Key);
	};
	for each (auto elem in expr->Sets)
	{
		expr->SetsMainGetter->Remove(elem.Key);
		expr->SetsMainGetter->Add(elem.Key, dict[elem.Key]);
	};

	auto result = expr->run();

	System::Console::Write("Result: ");
	for each (auto elem in result->Set_)
		System::Console::Write(elem + " ");

	std::cin.get();
	return 0;
};
#pragma unmanaged