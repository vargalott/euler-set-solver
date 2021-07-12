#pragma warning(push)
#pragma warning(disable : 4677)
#pragma warning(disable : 4267)
#pragma warning(disable : 4506)

#include <euler-set-solver/app.hpp>

#pragma unmanaged

#include <iostream>
#include <stdexcept>

#pragma managed

void ess::clr::app::run(void) {
  bool is_throw = false;

  try {
    System::Console::Write(
      "\n\t\t=== Set calculator ===\n\n\tu - union\n\tn - intersection\n\t+ - "
      "symmetric difference\n\t\\ - substraction" +
      "\n\t| - complement\n\n\tYou should using uppercase letters to set "
      "sets!\n\nEnter expr: ");

    System::String^ input = System::Console::ReadLine();
    System::Console::WriteLine();

    if (input == input->ToLower()) {
      throw gcnew System::Exception("invalid input");
    }

    auto expr = gcnew ess::clr::parser(input);
    auto dict = gcnew System::Collections::Generic::Dictionary<System::String^, ess::clr::set_inner^>();

    for each (auto elem in expr->dict()) {
      System::Console::Write("Enter {0}: ", elem.Key);
      ess::clr::set_operand set = ess::clr::converter::cli_str_to_list(System::Console::ReadLine());
      dict[elem.Key] = gcnew ess::clr::set_inner(set, elem.Key);
    }
    System::Console::WriteLine();
    for each (auto elem in expr->dict()) {
      expr->sets->Remove(elem.Key);
      expr->sets->Add(elem.Key, dict[elem.Key]);
    };

    System::Console::WriteLine("\nResult: {" + cli::safe_cast<System::String^>(expr->resolve()) + "}");

    //UseWolframAPI w_api;
    //w_api.SendRequest(input);
    //w_api.PrintAscii(w_api.GetVennUrl());


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

#pragma unmanaged
#pragma warning(pop)
