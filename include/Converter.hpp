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

#pragma once
#ifndef __CONVERTER_CLI_HPP__
#define __CONVERTER_CLI_HPP__

/*
*	Global includes, cli dll exports
*/
#pragma region GIE
#pragma unmanaged

	#include <string>

#pragma managed

	#using <System.dll>
	#using <System.Core.dll>

	#include <vcclr.h>
	#include <msclr\marshal_cppstd.h>

#pragma unmanaged
#pragma endregion

#pragma managed
namespace __InvokingCLR
{
	using SetOperand = System::Collections::Generic::List<System::String^>^;

	/*
	*	Some converting c++17/cli <-> c++17
	*/
	public ref class Converter
	{
	public:
		inline static System::String^ __std_str_to_cli_str(std::string const& convertible);
		inline static std::string __cli_str_to_std_str(System::String^ convertible);

		inline static SetOperand __cli_str_to_list(System::String^ convertible);
		inline static System::String^ __list_to_cli_str(SetOperand convertible);

		inline static SetOperand __make_set_from_list(SetOperand list);
	};
};
#pragma unmanaged


#endif // !__CONVERTER_CLI_HPP__