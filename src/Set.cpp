// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#pragma warning(push)
#pragma warning(disable:4677)
#pragma warning(disable:4267)
#pragma warning(disable:4506)

#include "./../include/Set.hpp"

#pragma managed

__InvokingCLR::Set::Set(void) : set(nullptr), name("") {}
__InvokingCLR::Set::Set(SetOperand set, System::String^ name) : name(name)
{
	if (set == nullptr)
		return;
	this->set = gcnew System::Collections::Generic::List<System::String^>();
	for each (auto elem in set)
		if (elem)
			this->set->Add(elem);
};

__InvokingCLR::Set::operator System::String^ (void)
{
	if (this->set)
		return __InvokingCLR::Converter::__list_to_cli_str(this->set);
	else
		return "{}";
}
inline __InvokingCLR::Set^ __InvokingCLR::Set::__compute_union(Set^ operand)
{
	Set^ result = gcnew Set();
	result->name = this->name + "u" + operand->name;
	if (this->set != nullptr)
		result->set = __InvokingCLR::BasicSetSolving::__union(this->set, operand->set);
	else
		result->set = __InvokingCLR::BasicSetSolving::__union(operand->set, operand->set);
	return result;
};
inline __InvokingCLR::Set^ __InvokingCLR::Set::__compute_intersection(Set^ operand)
{
	Set^ result = gcnew Set();
	result->name = this->name + "n" + operand->name;
	result->set = __InvokingCLR::BasicSetSolving::__intersection(this->set, operand->set);
	return result;
};
inline __InvokingCLR::Set^ __InvokingCLR::Set::__compute_s_difference(Set^ operand)
{
	Set^ result = gcnew Set();
	result->name = this->name + "+" + operand->name;
	result->set = __InvokingCLR::BasicSetSolving::__s_difference(this->set, operand->set);
	return result;
};
inline __InvokingCLR::Set^ __InvokingCLR::Set::__compute_substraction(Set^ operand)
{
	Set^ result = gcnew Set();
	result->name = this->name + "\\" + operand->name;
	result->set = __InvokingCLR::BasicSetSolving::__substraction(this->set, operand->set);
	return result;
};
inline __InvokingCLR::Set^ __InvokingCLR::Set::__compute_complement(Set^ operand)
{
	Set^ result = gcnew Set();
	result->name = "|" + this->name;
	result->set = __InvokingCLR::BasicSetSolving::__substraction(operand->set, this->set);
	return result;
};

#pragma unmanaged
#pragma warning(pop)