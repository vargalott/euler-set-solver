#pragma once
#ifndef __EXPRESSION_CLI_HPP__
#define __EXPRESSION_CLI_HPP__

/*
*	Global includes, cli dll exports
*/
#pragma region GIE
#pragma managed

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
