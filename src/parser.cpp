#pragma warning(push)
#pragma warning(disable: 4267)
#pragma warning(disable: 4506)
#pragma warning(disable: 4677)
#pragma warning(disable: 4715)

#include <euler-set-solver/parser.hpp>

#pragma managed
namespace ess::clr {

ess::clr::parser::parser(System::String^ expr)
  : _iterator(0), _current_operation(1) {
  this->_expr = expr->Replace(" ", "");
  this->_tokens = ess::clr::converter::cli_str_to_cli_list("( ) u n \\ + |");
  this->_sets = gcnew System::Collections::Generic::Dictionary<System::String^, ess::clr::set^>();
};

System::String^ ess::clr::parser::current_operation::get(void) {
  return this->_current_operation + ": ";
};
ess::clr::set_dict ess::clr::parser::sets::get(void) {
  return this->_sets;
};

ess::clr::set_dict ess::clr::parser::dict(void) {
  int iterator = 0;
  ess::clr::set_dict dict = gcnew System::Collections::Generic::Dictionary<System::String^, ess::clr::set^>();

  while (this->_expr->Length > iterator) {
    if (System::Char::IsUpper(this->_expr[iterator])) {
      System::String^ name = "";

      while (this->_expr->Length > iterator && System::Char::IsUpper(this->_expr[iterator])) {
        name += this->_expr[iterator];
        ++iterator;
      }

      dict[name] = gcnew ess::clr::set(ess::clr::set_operand(), name);
    }
    else {
      iterator++;
    }
  }
  return dict;
};
ess::clr::set^ ess::clr::parser::resolve(void) {
  return this->_evaluate(this->_parse());
};

int ess::clr::parser::_get_priority(System::String^ token) {
  if (ess::clr::converter::cli_str_to_cli_list("u n \\ + |")->Contains(token)) {
    return 1;
  }
  return 0;
};
ess::clr::expression^ ess::clr::parser::_parse(void) {
  return this->_parse_binary_expr(0);
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
ess::clr::expression^ ess::clr::parser::_parse_unary_expr(void) {
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

  return gcnew ess::clr::expression(token, this->_parse_unary_expr());
};
ess::clr::expression^ ess::clr::parser::_parse_binary_expr(int min_p) {
  ess::clr::expression^ lhs = this->_parse_unary_expr();

  while (true) {
    System::String^ token = this->_parse_token();
    int priority = this->_get_priority(token);

    if (priority <= min_p) {
      this->_iterator -= token->Length;
      return lhs;
    }

    ess::clr::expression^ rhs = this->_parse_binary_expr(priority);
    lhs = gcnew ess::clr::expression(token, lhs, rhs);
  }
};
ess::clr::set^ ess::clr::parser::_evaluate(ess::clr::expression^ expr) {
  if (expr->args == nullptr) {
    return this->_sets[expr->token];
  }

  switch (expr->args->Count) {
  case 1: {
    ess::clr::set^ set = this->_evaluate(expr->args[0]);

    System::Console::Write(this->_current_operation + ")\t");
    System::Console::ForegroundColor = System::ConsoleColor::Red;
    System::Console::Write(expr->token);
    System::Console::ResetColor();
    System::Console::WriteLine(set->name);

    System::Console::Write("==>\t" + expr->token + "{" +
      cli::safe_cast<System::String^>(set) + "} = ");

    this->_current_operation++;

    if (expr->token == "|") {
      ess::clr::set^ uni = gcnew ::ess::clr::set();

      for each (auto elem in this->_sets) {
        uni = uni->uni0n(elem.Value);
      }

      System::Console::WriteLine("{" + cli::safe_cast<System::String^>(set->complement(uni)) + "}\n");
      return set->complement(uni);
    }

    throw gcnew System::TypeAccessException("uknown unary operator");

    break;
  }
  case 2: {
    ess::clr::set^ lhs = this->_evaluate(expr->args[0]);
    ess::clr::set^ rhs = this->_evaluate(expr->args[1]);

    System::Console::Write(this->_current_operation + ")\t" + lhs->name + " ");
    System::Console::ForegroundColor = System::ConsoleColor::Red;
    System::Console::Write(expr->token);
    System::Console::ResetColor();
    System::Console::WriteLine(" " + rhs->name);
    System::Console::Write("==>\t{" + cli::safe_cast<System::String^>(lhs) + "} " +
      expr->token + " {" + cli::safe_cast<System::String^>(rhs) + "} = ");

    this->_current_operation++;

    char token = ess::clr::converter::cli_str_to_std_str(expr->token).c_str()[0];
    switch (token) {
    case 'u': {
      System::Console::WriteLine("{" + cli::safe_cast<System::String^>(lhs->uni0n(rhs)) + "}\n");
      return lhs->uni0n(rhs);

      break;
    }
    case 'n': {
      System::Console::WriteLine("{" + cli::safe_cast<System::String^>(lhs->intersect(rhs)) + "}\n");
      return lhs->intersect(rhs);

      break;
    }
    case '\\': {
      System::Console::WriteLine("{" + cli::safe_cast<System::String^>(lhs->substract(rhs)) + "}\n");
      return lhs->substract(rhs);

      break;
    }
    case '+': {
      System::Console::WriteLine("{" + cli::safe_cast<System::String^>(lhs->sdiff(rhs)) + "}\n");
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

}; // namespace ess::clr

#pragma warning(pop)
