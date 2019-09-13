// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma warning(push)
#pragma warning(disable:4677)
#pragma warning(disable:4267)
#pragma warning(disable:4506)

#include "./../include/Parser.hpp"

#pragma managed

__InvokingCLR::Parser::Parser(System::String^ expression) : iterator(std::size_t(0)), current_operation(cli::safe_cast<int>(std::size_t(1)))
{
	this->expression = expression->Replace(" ", "");
	this->tokens = __InvokingCLR::Converter::__cli_str_to_list(__InvokingCLR::Converter::__std_str_to_cli_str("( ) u n \\ + |"));
	this->sets = gcnew System::Collections::Generic::Dictionary<System::String^, Set^>();
};
__InvokingCLR::Set^ __InvokingCLR::Parser::Run(void)
{
	return this->__evaluate(this->__parse());
};

std::size_t __InvokingCLR::Parser::__get_priority(System::String^ token)
{
	if ((__InvokingCLR::Converter::__cli_str_to_list(__InvokingCLR::Converter::__std_str_to_cli_str("u n \\ + |")))->Contains(token))
		return cli::safe_cast<int>(std::size_t(1));
	return cli::safe_cast<int>(std::size_t(0));
};
System::String^ __InvokingCLR::Parser::__parse_t(void)
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
__InvokingCLR::Parser::Expression^ __InvokingCLR::Parser::__parse_be(std::size_t min_p)
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
__InvokingCLR::Parser::Expression^ __InvokingCLR::Parser::__parse(void)
{
	return this->__parse_be(0);
};
__InvokingCLR::Parser::Expression^ __InvokingCLR::Parser::__parse_se(void)
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
__InvokingCLR::Set^ __InvokingCLR::Parser::__evaluate(Expression^ expr)
{
	if (expr->GetArguments() == nullptr)
		return this->sets[expr->GetToken()];
	if (expr->GetArguments()->Count == 1)
	{
		Set^ set = this->__evaluate(expr->GetArguments()[0]);

		System::Console::Write(this->CurrentOperation + " ");
		System::Console::ForegroundColor = System::ConsoleColor::Red;
		System::Console::Write(expr->GetToken());
		System::Console::ResetColor();
		System::Console::Write(set->Name + "\n");

		System::Console::Write("A:  " + expr->GetToken() + "{" + cli::safe_cast<System::String^>(set) + "} = ");

		++this->current_operation;

		if (expr->GetToken() == "|")
		{
			Set^ universum = gcnew Set();
			for each (auto elem in this->sets)
				universum = universum->__compute_union(elem.Value);
			System::Console::Write("{" + cli::safe_cast<System::String^>(set->__compute_complement(universum)) + "}\n");
			return set->__compute_complement(universum);
		};

		throw gcnew System::Exception("unknow unary operation");
	};
	if (expr->GetArguments()->Count == 2)
	{
		Set^ set_l = this->__evaluate(expr->GetArguments()[0]);
		Set^ set_r = this->__evaluate(expr->GetArguments()[1]);

		System::Console::Write(this->CurrentOperation + " " + set_l->Name + " ");
		System::Console::ForegroundColor = System::ConsoleColor::Red;
		System::Console::Write(expr->GetToken());
		System::Console::ResetColor();
		System::Console::Write(" " + set_r->Name + "\n");
		System::Console::Write("A:  {" + cli::safe_cast<System::String^>(set_l) + "} " + expr->GetToken() + " {" + cli::safe_cast<System::String^>(set_r) + "} = ");

		++this->current_operation;

		if (expr->GetToken() == "u")
		{
			System::Console::Write("{" + cli::safe_cast<System::String^>(set_l->__compute_union(set_r)) + "}\n");
			return set_l->__compute_union(set_r);
		};
		if (expr->GetToken() == "n")
		{
			System::Console::Write("{" + cli::safe_cast<System::String^>(set_l->__compute_intersection(set_r)) + "}\n");
			return set_l->__compute_intersection(set_r);
		};			
		if (expr->GetToken() == "\\")
		{
			System::Console::Write("{" + cli::safe_cast<System::String^>(set_l->__compute_substraction(set_r)) + "}\n");
			return set_l->__compute_substraction(set_r);
		};
		if (expr->GetToken() == "+")
		{
			System::Console::Write("{" + cli::safe_cast<System::String^>(set_l->__compute_s_difference(set_r)) + "}\n");
			return set_l->__compute_s_difference(set_r);
		};			

		throw gcnew System::Exception("unknow binary operation");
	};
	throw gcnew System::Exception("unknow operation");
};

#pragma unmanaged
#pragma warning(pop)