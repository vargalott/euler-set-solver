#pragma warning(push)
#pragma warning(disable: 4267)
#pragma warning(disable: 4506)
#pragma warning(disable: 4677)
#pragma warning(disable: 4715)

#include <euler-set-solver/app.hpp>

#pragma managed
namespace ess::clr {

void app::run(void) {
  bool is_throw = false;

  try {
    System::Console::Write(
      "========================\n"
      "    euler-set-solver\n"
      "========================\n\n"
      "Operators:\n"
      "'u' - union\n"
      "'n' - intersection\n"
      "'\\' - substraction\n"
      "'+' - symmetric difference\n"
      "\nYou should use UPPERCASE letters to set the sets!\n\n"
      "Enter your expression: ");

    System::String^ input = System::Console::ReadLine();
    System::Console::WriteLine();

    if (input == input->ToLower()) {
      throw gcnew System::Exception("invalid input");
    }

    auto expr = gcnew ess::clr::parser(input);
    auto dict = gcnew System::Collections::Generic::Dictionary<System::String^, ess::clr::set^>();

    for each (auto elem in expr->dict()) {
      System::Console::Write("Enter {0}: ", elem.Key);
      ess::clr::set_operand set = ess::clr::converter::cli_str_to_cli_list(System::Console::ReadLine());
      dict[elem.Key] = gcnew ess::clr::set(set, elem.Key);
    }
    System::Console::WriteLine();
    for each (auto elem in expr->dict()) {
      expr->sets->Remove(elem.Key);
      expr->sets->Add(elem.Key, dict[elem.Key]);
    };

    System::Console::WriteLine("\nResult: {" + cli::safe_cast<System::String^>(expr->resolve()) + "}");
    System::Console::WriteLine("\nPress any key to exit...");
  }
  catch (System::Exception^ ex) {
    System::Console::WriteLine(ex->Message);
    is_throw = !is_throw;
  }
  catch (std::exception& ex) {
    std::cout << ex.what();
    is_throw = !is_throw;
  }
  finally {
    if (is_throw) {
      std::cout << "\nAn error has occurred... Press any key to exit...\n";
    }
  }
  std::cin.get();
};

}; // namespace ess::clr

#pragma warning(pop)
