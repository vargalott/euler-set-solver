#pragma once
#ifndef __PARSER_CLI_HPP__
#define __PARSER_CLI_HPP__

/*
*	Global includes, cli dll exports
*/
#pragma region GIE
#pragma managed

#include <euler-set-solver/set.hpp>
#include <euler-set-solver/set-op.hpp>
#include <euler-set-solver/converter.hpp>
#include <euler-set-solver/expression.hpp>
#include <euler-set-solver/wolfram-wrapper.hpp>

#pragma unmanaged
#pragma endregion

#pragma managed
namespace __InvokingCLR
{
	ref class Set;

	using SetOperand = System::Collections::Generic::List<System::String^>^;
	using SetDictionary = System::Collections::Generic::Dictionary<System::String^, Set^>^;

	/*
	*	Implements main class which
	*	parse the expression to evaluating
	*/
	private ref class Parser
	{
	public:
		explicit Parser(System::String^ expression);

		property SetDictionary Sets
		{
			SetDictionary get(void);
		};
		property System::String^ CurrentOperation
		{
			System::String^ get(void);
		}
		property SetDictionary SetsMainGetter
		{
			SetDictionary get(void);
		};

		Set^ Run(void);
	private:
		SetDictionary sets;
		System::String^ expression;
		SetOperand tokens;

		std::size_t iterator; std::size_t current_operation;

		std::size_t			__get_priority(System::String^ token);
		System::String^		__parse_t(void);
		Expression^			__parse_be(std::size_t min_p);
		Expression^			__parse(void);
		Expression^			__parse_se(void);
		Set^				__evaluate(Expression^ expr);
	};

	/*
	*	Main control class
	*/
	public ref class Parsing
	{
	public:
		static void Run(void);
	};
};

#endif // !__PARSER_CLI_HPP__
