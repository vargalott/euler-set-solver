#pragma warning(push)
#pragma warning(disable:4677)
#pragma warning(disable:4267)
#pragma warning(disable:4506)

#pragma unmanaged
#include <iostream>
#include <stdexcept>
#pragma managed
#include <euler-set-solver/parser.hpp>
#pragma unmanaged

/*
*	Entry Point: managed code
*/
#pragma managed
int __cdecl main(void)
{
	bool is_throw = false;
	try
	{
		__InvokingCLR::Parsing::Run();
		System::Console::WriteLine("\n\nPress any key to exit...");
	}
	catch (System::Exception^ ex)
	{
		System::Console::WriteLine(ex->Message);
		is_throw = !is_throw;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
		is_throw = !is_throw;
	}
	finally
	{
		if (is_throw)
			std::cout << "\n\nAn error has occurred... Press any key to exit...\n";
	};
	std::cin.get();
	return 0;
};
#pragma unmanaged
#pragma warning(pop)
