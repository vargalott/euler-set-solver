// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "./../include/Parser.hpp"

#pragma managed

__InvokingCLR::Parser::Parser(System::String^ expression) : iterator(std::size_t(0)), current_operation(std::size_t(1))
{
	this->expression = expression->Replace(" ", "");
	this->tokens = __InvokingCLR::Converter::__cli_str_to_list(__InvokingCLR::Converter::__std_str_to_cli_str("u n \\ + _ ( )"));
	this->sets = gcnew System::Collections::Generic::Dictionary<System::String^, Set^>();
};
__InvokingCLR::Set^ __InvokingCLR::Parser::Run(void)
{
	return this->__evaluate(this->__parse());
}

std::size_t __InvokingCLR::Parser::__get_priority(System::String^ token)
{
	if (this->tokens->Contains(token))
		return std::size_t(1);
	return 0;
};
System::String^ __InvokingCLR::Parser::__parse_t(void)
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
__InvokingCLR::Parser::Expression^ __InvokingCLR::Parser::__parse_be(std::size_t min_p)
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
}
__InvokingCLR::Parser::Expression^ __InvokingCLR::Parser::__parse(void)
{
	return this->__parse_be(0);
}
__InvokingCLR::Parser::Expression^ __InvokingCLR::Parser::__parse_se(void)
{
	System::String^ token = this->__parse_t();
	if (token == "")
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
}
__InvokingCLR::Set^ __InvokingCLR::Parser::__evaluate(Expression^ expr)
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

		if (expr->GetToken() == "_")
			return set->__compute_addition(this->sets["Z"]);

		throw gcnew System::Exception("unknow unary operation");
	};
	if (expr->GetArguments()->Count == 2)
	{
		Set^ set_l = this->__evaluate(expr->GetArguments()[0]);
		Set^ set_r = this->__evaluate(expr->GetArguments()[1]);

		System::Console::WriteLine(this->CurrentOperaion + " " + set_l->Name + " " + expr->GetToken() + " " + set_r->Name);

		System::Console::Write(this->CurrentOperaion + " { ");
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
}
__InvokingCLR::Set^ __InvokingCLR::Parser::__compute_dict_union(Set^ set_l, Set^ set_r)
{
	return gcnew Set(__InvokingCLR::BasicSetSolving::__union(set_l->Set_, set_r->Set_), set_l->Name);
};

#pragma unmanaged