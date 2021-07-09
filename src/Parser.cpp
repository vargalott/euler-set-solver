// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma warning(push)
#pragma warning(disable:4677)
#pragma warning(disable:4267)
#pragma warning(disable:4506)

#include "./../include/Parser.hpp"

#pragma managed

__InvokingCLR::Parser::Parser(System::String^ expression) 
	: iterator(cli::safe_cast<int>(std::size_t(0))), 
	  current_operation(cli::safe_cast<int>(std::size_t(1)))
{
	this->expression = expression->Replace(" ", "");
	this->tokens = Converter::__cli_str_to_list("( ) u n \\ + |");
	this->sets = gcnew System::Collections::Generic::Dictionary<System::String^, Set^>();
};

__InvokingCLR::SetDictionary	__InvokingCLR::Parser::Sets::get(void)
{
	std::size_t _iterator = std::size_t(0);
	SetDictionary dict = gcnew System::Collections::Generic::Dictionary<System::String^, Set^>();

	while (this->expression->Length > _iterator)
	{
		if (System::Char::IsUpper(this->expression[_iterator]))
		{
			System::String^ name = "";
			while (this->expression->Length > _iterator && System::Char::IsUpper(this->expression[_iterator]))
			{
				name += this->expression[_iterator];
				++_iterator;
			};
			dict[name] = gcnew Set(SetOperand(), name);
		}
		else
			++_iterator;
	};
	return dict;
};
System::String^					__InvokingCLR::Parser::CurrentOperation::get(void)
{
	return this->current_operation + ": ";
};
__InvokingCLR::SetDictionary	__InvokingCLR::Parser::SetsMainGetter::get(void)
{
	return this->sets;
};
__InvokingCLR::Set^				__InvokingCLR::Parser::Run(void)
{
	return this->__evaluate(this->__parse());
};

std::size_t					__InvokingCLR::Parser::__get_priority(System::String^ token)
{
	if ((Converter::__cli_str_to_list("u n \\ + |"))->Contains(token))
		return cli::safe_cast<int>(std::size_t(1));
	return cli::safe_cast<int>(std::size_t(0));
};
System::String^				__InvokingCLR::Parser::__parse_t(void)
{
	if (this->iterator < this->expression->Length)
	{
		if (System::Char::IsUpper(this->expression, this->iterator))
		{
			System::String^ name = "";
			while (this->expression->Length > this->iterator && System::Char::IsUpper(this->expression, this->iterator))
			{
				name += this->expression[this->iterator];
				this->iterator++;
			};
			return name;
		};

		for each (System::String^ token in this->tokens)
		{
			if (this->expression->Substring(this->iterator, token->Length) == token)
			{
				this->iterator += token->Length;
				return token;
			};
		};
	};
	return gcnew System::String("");
};
__InvokingCLR::Expression^	__InvokingCLR::Parser::__parse_be(std::size_t min_p)
{
	Expression^	expr_l = this->__parse_se();

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
__InvokingCLR::Expression^	__InvokingCLR::Parser::__parse(void)
{
	return this->__parse_be(0);
};
__InvokingCLR::Expression^	__InvokingCLR::Parser::__parse_se(void)
{
	System::String^ token = this->__parse_t();
	if (!token)
		throw gcnew System::Exception("invalid input");

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
__InvokingCLR::Set^			__InvokingCLR::Parser::__evaluate(Expression^ expr)
{
	if (expr->Arguments == nullptr)
		return this->sets[expr->Token];
	if (expr->Arguments->Count == 1)
	{
		Set^ set = this->__evaluate(expr->Arguments[0]);

		System::Console::Write(this->CurrentOperation + " ");
		System::Console::ForegroundColor = System::ConsoleColor::Red;
		System::Console::Write(expr->Token);
		System::Console::ResetColor();
		System::Console::Write(set->Name + "\n");

		System::Console::Write("A:  " + expr->Token + "{" + cli::safe_cast<System::String^>(set) + "} = ");

		++this->current_operation;

		if (expr->Token == "|")
		{
			Set^ universum = gcnew Set();
			for each (auto elem in this->sets)
				universum = universum->__compute_union(elem.Value);
			System::Console::Write("{" + cli::safe_cast<System::String^>(set->__compute_complement(universum)) + "}\n");
			return set->__compute_complement(universum);
		};

		throw gcnew System::Exception("unknow unary operation");
	};
	if (expr->Arguments->Count == 2)
	{
		Set^ set_l = this->__evaluate(expr->Arguments[0]);
		Set^ set_r = this->__evaluate(expr->Arguments[1]);

		System::Console::Write(this->CurrentOperation + " " + set_l->Name + " ");
		System::Console::ForegroundColor = System::ConsoleColor::Red;
		System::Console::Write(expr->Token);
		System::Console::ResetColor();
		System::Console::Write(" " + set_r->Name + "\n");
		System::Console::Write("A:  {" + cli::safe_cast<System::String^>(set_l) + "} " + expr->Token + " {" + cli::safe_cast<System::String^>(set_r) + "} = ");

		++this->current_operation;

		if (expr->Token == "u")
		{
			System::Console::Write("{" + cli::safe_cast<System::String^>(set_l->__compute_union(set_r)) + "}\n");
			return set_l->__compute_union(set_r);
		};
		if (expr->Token == "n")
		{
			System::Console::Write("{" + cli::safe_cast<System::String^>(set_l->__compute_intersection(set_r)) + "}\n");
			return set_l->__compute_intersection(set_r);
		};			
		if (expr->Token == "\\")
		{
			System::Console::Write("{" + cli::safe_cast<System::String^>(set_l->__compute_substraction(set_r)) + "}\n");
			return set_l->__compute_substraction(set_r);
		};
		if (expr->Token == "+")
		{
			System::Console::Write("{" + cli::safe_cast<System::String^>(set_l->__compute_s_difference(set_r)) + "}\n");
			return set_l->__compute_s_difference(set_r);
		};			

		throw gcnew System::Exception("unknow binary operation");
	};
	throw gcnew System::Exception("unknow operation");
};


void __InvokingCLR::Parsing::Run(void)
{
	System::Console::Write("\n\t\t=== Set calculator ===\n\n\tu - union\n\tn - intersection\n\t+ - symmetric difference\n\t\\ - substraction" +
		"\n\t| - complement\n\n\tYou should using uppercase letters to set sets!\n\nEnter expr: ");

	System::String^ input = System::Console::ReadLine();
	System::Console::Write("\n");

	System::String^ compare = input->ToLower();
	if (compare == input)
		throw gcnew System::Exception("invalid input");

	UseWolframAPI w_api;
	w_api.SendRequest(input);

	auto expr = gcnew __InvokingCLR::Parser(input);

	auto dict = gcnew System::Collections::Generic::Dictionary<System::String^, __InvokingCLR::Set^>();

	for each (auto elem in expr->Sets)
	{
		System::Console::Write("Enter {0}: ", elem.Key);
		SetOperand tmp = Converter::__cli_str_to_list(System::Console::ReadLine());
		dict[elem.Key] = gcnew Set(tmp, elem.Key);
	};
	System::Console::Write("\n");
	for each (auto elem in expr->Sets)
	{
		expr->SetsMainGetter->Remove(elem.Key);
		expr->SetsMainGetter->Add(elem.Key, dict[elem.Key]);
	};

	auto result = expr->Run();

	System::Console::Write("\nResult: {" + cli::safe_cast<System::String^>(result) + "}\n\n");

	w_api.PrintAscii(w_api.GetVennUrl());
};

#pragma unmanaged
#pragma warning(pop)