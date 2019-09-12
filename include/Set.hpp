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
#ifndef __SET_CLI_HPP__
#define __SET_CLI_HPP__

/*
*	Global includes, cli dll exports
*/
#pragma region GIE
#pragma managed

#using <System.dll>
#using <System.Core.dll>

#include "./../include/BasicSetOperation.hpp"
#include "./..//include/Converter.hpp"

#pragma unmanaged
#pragma endregion

#pragma managed

#pragma managed
namespace __InvokingCLR
{
	using SetOperand = System::Collections::Generic::List<System::String^>^;

	/*
	*	Class implements the representation of
	*	Set operand with needed operation
	*/
	ref class Set
	{
	public:
		explicit Set(void);
		explicit Set(SetOperand set, System::String^ name);

		/*
		*	casting operator to System::String^
		*/
		explicit operator System::String^(void);

		property System::String^ Name
		{
			System::String^ get(void)
			{
				return this->name;
			};
		};
		property SetOperand Set_
		{
			inline SetOperand get(void)
			{
				return this->set;
			};
			inline void set(SetOperand set)
			{
				this->set = set;
			};
		};

		/*
		*	Computing sets union
		*	openard to parse - "u"
		*/
		inline Set^ __compute_union(Set^ operand);
		/*
		*	Computing sets intersection
		*	openard to parse - "n"
		*/
		inline Set^ __compute_intersection(Set^ operand);
		/*
		*	Computing sets complement
		*	openard to parse - "+"
		*/
		inline Set^ __compute_s_difference(Set^ operand);
		/*
		*	Computing sets substraction
		*	openard to parse - "\"
		*/
		inline Set^ __compute_substraction(Set^ operand);
		/*
		*	Computing sets addition
		*	openard to parse - "_"
		*/
		inline Set^ __compute_complement(Set^ operand);

	private:
		SetOperand set;
		System::String^ name;
	};
};
#pragma unmanaged

#endif // !__SET_CLI_HPP__