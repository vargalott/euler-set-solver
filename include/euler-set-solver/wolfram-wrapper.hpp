#pragma once
#ifndef __WOLFRAM_WRAPPER_CLI_HPP__
#define __WOLFRAM_WRAPPER_CLI_HPP__

/*
*	Global includes, cli dll exports
*/
#pragma region GIE
#pragma managed

#include <euler-set-solver/converter.hpp>

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

#endif // !__WOLFRAM_WRAPPER_CLI_HPP__
