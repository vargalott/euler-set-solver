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

/*
*	Entry Point: managed code
*/
#pragma managed
int __cdecl main(void)
{
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);

	std::string first, second;

	std::cout << "First set:\t";
	std::getline(std::cin, first);
	std::cout << "Second set:\t";
	std::getline(std::cin, second);

	std::size_t curr_op; System::String^ res;

	std::cout << "\nChoose operation:\n\t1 - union\n\t2 - intesection\n\t3 - substraction\n\t4 - complement\n:";
	(std::cin >> curr_op).get();
	
	switch (curr_op)
	{
	case 1:
		res = __InvokingCLR_Basic_Solve(first, second, __InvokingCLR_Basic__UNION);
		break;
	case 2:
		res = __InvokingCLR_Basic_Solve(first, second, __InvokingCLR_Basic__INTERSECTION);
		break;
	case 3:
		res = __InvokingCLR_Basic_Solve(first, second, __InvokingCLR_Basic__SUBSTRACTION);
		break;
	case 4:
		res = __InvokingCLR_Basic_Solve(first, second, __InvokingCLR_Basic__COMPLEMENT);
		break;
	};

	for each (auto elem in res)
		System::Console::Write(elem);

	std::cin.get();
	return 0;
};
#pragma unmanaged