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
#pragma warning(push)
#pragma warning(disable:4677)
#pragma warning(disable:4267)
#pragma warning(disable:4506)

#pragma unmanaged
#include <iostream>
#include <stdexcept>
#pragma managed
#include "./../include/Parser.hpp"
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