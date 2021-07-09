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
#ifndef __WOLFRAM_CALLING_CLI_HPP__
#define __WOLFRAM_CALLING_CLI_HPP__

/*
*	Global includes, cli dll exports
*/
#pragma region GIE
#pragma managed

#using <System.dll>
#using <System.Core.dll>

#include "./Converter.hpp"

using namespace Wolfram::Alpha;

#pragma unmanaged
#pragma endregion

#pragma managed
namespace __InvokingCLR
{
	private ref class PrepareQuery
	{
	public:
		static System::String^ Evaluate(System::String^ input);
	};
	private ref class ResultImage
	{
	public:
		static System::Drawing::Image^ GetImage(System::String^ url);
		static System::Drawing::Bitmap^ ResizeImage(System::Drawing::Image^ image, int width);
		static void PrintAscii(System::Drawing::Bitmap^ bitmap);
	};
	private ref class UseWolframAPI
	{
	public:
		void SendRequest(System::String^ unevaluated_query);
		System::String^ GetVennUrl(void);
		void PrintAscii(System::String^ image_url);

	private:
		System::Threading::Tasks::Task<Wolfram::Alpha::Models::WolframAlphaResult^>^ query_result;
	};
};
#pragma unmanaged

#endif // !__WOLFRAM_CALLING_CLI_HPP__