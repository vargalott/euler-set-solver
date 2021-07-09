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
		static System::String^ __std_str_to_cli_str(std::string const& convertible);
		static std::string __cli_str_to_std_str(System::String^ convertible);

		static SetOperand __cli_str_to_list(System::String^ convertible);
		static System::String^ __list_to_cli_str(SetOperand convertible);

		static SetOperand __make_set_from_list(SetOperand list);
	};
};
#pragma unmanaged


#endif // !__CONVERTER_CLI_HPP__
