#pragma warning(push)
#pragma warning(disable : 4677)
#pragma warning(disable : 4267)
#pragma warning(disable : 4506)

#include <euler-set-solver/parser.hpp>

#pragma managed

ess::clr::parser::parser(System::String^ expr)
  : _iterator(0), _current_operation(1) {
  this->_expr = expr->Replace(" ", "");
  this->_tokens = ess::clr::converter::cli_str_to_list("( ) u n \\ + |");
  this->_sets = gcnew System::Collections::Generic::Dictionary<System::String^, ess::clr::set_inner^>();
};
System::String^ ess::clr::parser::current_operation::get(void) {
  return this->_current_operation + ": ";
};
ess::clr::set_dict ess::clr::parser::sets::get(void) {
  return this->_sets;
};
ess::clr::set_dict ess::clr::parser::dict(void) {
  int iterator = 0;
  ess::clr::set_dict dict = gcnew System::Collections::Generic::Dictionary<System::String^, ess::clr::set_inner^>();

  while (this->_expr->Length > iterator) {
    if (System::Char::IsUpper(this->_expr[iterator])) {
      System::String^ name = "";

      while (this->_expr->Length > iterator && System::Char::IsUpper(this->_expr[iterator])) {
        name += this->_expr[iterator];
        ++iterator;
      }

      dict[name] = gcnew ess::clr::set_inner(ess::clr::set_operand(), name);
    }
    else {
      iterator++;
    }
  }
  return dict;
};
ess::clr::set_inner^ ess::clr::parser::resolve(void) {
  return this->_evaluate(this->_parse());
};
int ess::clr::parser::_get_priority(System::String^ token) {
  if (ess::clr::converter::cli_str_to_list("u n \\ + |")->Contains(token)) {
    return 1;
  }
  return 0;
};
System::String^ ess::clr::parser::_parse_token(void) {
  if (this->_iterator < this->_expr->Length) {
    if (System::Char::IsUpper(this->_expr, this->_iterator)) {
      System::String^ name = "";
      while (this->_expr->Length > this->_iterator && System::Char::IsUpper(this->_expr, this->_iterator)) {
        name += this->_expr[this->_iterator];
        this->_iterator++;
      }
      return name;
    }

    for each (System::String ^ token in this->_tokens) {
      if (this->_expr->Substring(this->_iterator, token->Length) == token) {
        this->_iterator += token->Length;
        return token;
      }
    }
  }

  return gcnew System::String("");
};
ess::clr::expression^ ess::clr::parser::_parse_be(int min_p) {
  ess::clr::expression^ lhs = this->_parse_se();

  while (true) {
    System::String^ token = this->_parse_token();
    int priority = this->_get_priority(token);

    if (priority <= min_p) {
      this->_iterator -= token->Length;
      return lhs;
    }

    ess::clr::expression^ rhs = this->_parse_be(priority);
    lhs = gcnew ess::clr::expression(token, lhs, rhs);
  }
};
ess::clr::expression^ ess::clr::parser::_parse(void) {
  return this->_parse_be(0);
};
ess::clr::expression^ ess::clr::parser::_parse_se(void) {
  System::String^ token = this->_parse_token();
  if (!token) {
    throw gcnew System::Exception("invalid input");
  }

  if (System::Char::IsUpper(token, 0)) {
    return gcnew ess::clr::expression(token);
  }

  if (token == "(") {
    ess::clr::expression^ ret = this->_parse();
    if (this->_parse_token() != ")") {
      throw gcnew System::Exception("')' expected but not found");
    }

    return ret;
  }

  return gcnew ess::clr::expression(token, this->_parse_se());
};
ess::clr::set_inner^ ess::clr::parser::_evaluate(ess::clr::expression^ expr) {
  if (expr->args == nullptr) {
    return this->_sets[expr->token];
  }

  switch (expr->args->Count) {
  case 1: {
    ess::clr::set_inner^ set = this->_evaluate(expr->args[0]);

    System::Console::Write(this->_current_operation + " ");
    System::Console::ForegroundColor = System::ConsoleColor::Red;
    System::Console::Write(expr->token);
    System::Console::ResetColor();
    System::Console::WriteLine(set->name);

    System::Console::Write("A:  " + expr->token + "{" +
      cli::safe_cast<System::String^>(set) + "} = ");

    this->_current_operation++;

    if (expr->token == "|") {
      ess::clr::set_inner^ uni = gcnew ::ess::clr::set_inner();

      for each (auto elem in this->_sets) {
        uni = uni->uni0n(elem.Value);
      }

      System::Console::WriteLine("{" + cli::safe_cast<System::String^>(set->complement(uni)) + "}");
      return set->complement(uni);
    }

    throw gcnew System::TypeAccessException("uknown unary operator");

    break;
  }
  case 2: {
    ess::clr::set_inner^ lhs = this->_evaluate(expr->args[0]);
    ess::clr::set_inner^ rhs = this->_evaluate(expr->args[1]);

    System::Console::Write(this->_current_operation + " " + lhs->name + " ");
    System::Console::ForegroundColor = System::ConsoleColor::Red;
    System::Console::Write(expr->token);
    System::Console::ResetColor();
    System::Console::Write(" " + rhs->name + "\n");
    System::Console::Write("A:  {" + cli::safe_cast<System::String^>(lhs) + "} " +
      expr->token + " {" + cli::safe_cast<System::String^>(rhs) + "} = ");

    this->_current_operation++;

    char token = ess::clr::converter::cli_str_to_std_str(expr->token).c_str()[0];
    switch (token) {
    case 'u': {
      System::Console::WriteLine("{" + cli::safe_cast<System::String^>(lhs->uni0n(rhs)) + "}");
      return lhs->uni0n(rhs);

      break;
    }
    case 'n': {
      System::Console::WriteLine("{" + cli::safe_cast<System::String^>(lhs->intersect(rhs)) + "}");
      return lhs->intersect(rhs);

      break;
    }
    case '\\': {
      System::Console::WriteLine("{" + cli::safe_cast<System::String^>(lhs->substract(rhs)) + "}");
      return lhs->substract(rhs);

      break;
    }
    case '+': {
      System::Console::WriteLine("{" + cli::safe_cast<System::String^>(lhs->sdiff(rhs)) + "}");
      return lhs->sdiff(rhs);

      break;
    }
    }

    throw gcnew System::Exception("unknown binary operator");

    break;
  }

  throw gcnew System::Exception("unknown operator");
  }
};

#pragma unmanaged
#pragma warning(pop)
