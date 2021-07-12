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

namespace ess::clr {
  using set_operand = System::Collections::Generic::List<System::String^>^;

  /*
   *	Class implements the representation of
   *	Set operand with needed operation
   */
  private ref class set_inner {
  public:
    explicit set_inner(void);
    explicit set_inner(ess::clr::set_operand set, System::String^ name);

    explicit operator System::String^ (void);

    property System::String^ name {
      System::String^ get(void);
    };
    property ess::clr::set_operand set_instance {
      ess::clr::set_operand get(void);
      void set(ess::clr::set_operand _set_instance);
    };

    /*
     *	Computing sets union
     *	openard to parse - "u"
     */
    ess::clr::set_inner^ uni0n(ess::clr::set_inner^ operand);
    /*
     *	Computing sets intersection
     *	openard to parse - "n"
     */
    ess::clr::set_inner^ intersect(ess::clr::set_inner^ operand);
    /*
     *	Computing sets complement
     *	openard to parse - "+"
     */
    ess::clr::set_inner^ sdiff(ess::clr::set_inner^ operand);
    /*
     *	Computing sets substraction
     *	openard to parse - "\"
     */
    ess::clr::set_inner^ substract(ess::clr::set_inner^ operand);
    /*
     *	Computing sets addition
     *	openard to parse - "_"
     */
    ess::clr::set_inner^ complement(ess::clr::set_inner^ operand);

  private:
    ess::clr::set_operand _set_instance;
    System::String^ _name;
  };
}; // namespace ess::clr

#pragma unmanaged

#endif // !__SET_CLI_HPP__
