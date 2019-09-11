// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

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
		return "{0}";
}
inline __InvokingCLR::Set^ __InvokingCLR::Set::__compute_union(Set^ operand)
{
	Set^ result = gcnew Set();
	result->name = this->name + " n " + operand->name;
	result->set = __InvokingCLR::BasicSetSolving::__union(this->set, operand->set);
	return result;
};
inline __InvokingCLR::Set^ __InvokingCLR::Set::__compute_intersection(Set^ operand)
{
	Set^ result = gcnew Set();
	result->name = this->name + " n " + operand->name;
	result->set = __InvokingCLR::BasicSetSolving::__intersection(this->set, operand->set);
	return result;
};
inline __InvokingCLR::Set^ __InvokingCLR::Set::__compute_complement(Set^ operand)
{
	Set^ result = gcnew Set();
	result->name = this->name + " n " + operand->name;
	result->set = __InvokingCLR::BasicSetSolving::__complement(this->set, operand->set);
	return result;
};
inline __InvokingCLR::Set^ __InvokingCLR::Set::__compute_substraction(Set^ operand)
{
	Set^ result = gcnew Set();
	result->name = this->name + " n " + operand->name;
	result->set = __InvokingCLR::BasicSetSolving::__substraction(this->set, operand->set);
	return result;
};
inline __InvokingCLR::Set^ __InvokingCLR::Set::__compute_addition(Set^ operand)
{
	Set^ result = gcnew Set();
	result->name = this->name + " n " + operand->name;
	result->set = __InvokingCLR::BasicSetSolving::__addition(this->set, operand->set);
	return result;
};

#pragma unmanaged