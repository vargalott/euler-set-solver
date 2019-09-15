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
#ifndef __EXPRESSION_CLI_HPP__
#define __EXPRESSION_CLI_HPP__

/*
*	Global includes, cli dll exports
*/
#pragma region GIE
#pragma managed

#using <System.dll>
#using <System.Core.dll>

#pragma unmanaged
#pragma endregion

#pragma managed
namespace __InvokingCLR
{
	/*
	*	Class which represents the
	*	expression entity
	*/
	private ref class Expression
	{
	public:
		explicit Expression(System::String^ token);
		explicit Expression(System::String^ token, Expression^ expr);
		explicit Expression(System::String^ token, Expression^ expr_l, Expression^ expr_r);

		property System::Collections::Generic::List<Expression^>^ Arguments
		{
			System::Collections::Generic::List<Expression^>^ get(void);
		};
		property System::String^ Token
		{
			System::String^ get(void);
		};
	private:
		System::String^ token;
		System::Collections::Generic::List<Expression^>^ arguments;
	};
};
#pragma unmanaged

#endif // !__EXPRESSION_CLI_HPP__