#pragma once
#ifndef __SET_CLI_HPP__
#define __SET_CLI_HPP__

/*
 *	Global includes, cli dll exports
 */
#pragma region GIE
#pragma managed

#include <euler-set-solver/converter.hpp>
#include <euler-set-solver/set-op.hpp>

#pragma unmanaged
#pragma endregion

#pragma managed

#pragma managed
namespace __InvokingCLR {
using SetOperand = System::Collections::Generic::List<System::String ^> ^ ;

/*
 *	Class implements the representation of
 *	Set operand with needed operation
 */
private ref class Set {
public:
  explicit Set(void);
  explicit Set(SetOperand set, System::String ^ name);

  /*
   *	casting operator to System::String^
   */
  explicit operator System::String ^(void);

  property System::String ^ Name { System::String ^ get(void); };
  property SetOperand Set_ {
    SetOperand get(void);
    void set(__InvokingCLR::SetOperand);
  };

  /*
   *	Computing sets union
   *	openard to parse - "u"
   */
  Set ^ __compute_union(Set ^ operand);
  /*
   *	Computing sets intersection
   *	openard to parse - "n"
   */
  Set ^ __compute_intersection(Set ^ operand);
  /*
   *	Computing sets complement
   *	openard to parse - "+"
   */
  Set ^ __compute_s_difference(Set ^ operand);
  /*
   *	Computing sets substraction
   *	openard to parse - "\"
   */
  Set ^ __compute_substraction(Set ^ operand);
  /*
   *	Computing sets addition
   *	openard to parse - "_"
   */
  Set ^ __compute_complement(Set ^ operand);

private:
  SetOperand set;
  System::String ^ name;
};
}; // namespace __InvokingCLR
#pragma unmanaged

#endif // !__SET_CLI_HPP__
