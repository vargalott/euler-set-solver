#pragma once
#ifndef __SET_CLI_HPP__
#define __SET_CLI_HPP__

#pragma managed
#include <euler-set-solver/converter.hpp>
#include <euler-set-solver/set-operator.hpp>


#pragma managed
namespace ess::clr {

using set_operand = System::Collections::Generic::List<System::String^>^;

/**
 * Core set class
 *
 * ...
 *
 * Implements ball internal set functionality
 */
private ref class set {
public:
  /**
   * Class construnctor
   * Permorm construnction of an empty instance of the set
   */
  explicit set(void);
  /**
   * Class construnctor
   * Permorm construnction of the instance of the set
   *
   * @param[in] set Set's data
   * @param[in] name Set's name
   */
  explicit set(ess::clr::set_operand set, System::String^ name);

  /**
   * Perform explicit cast to the string
   */
  explicit operator System::String^ (void);

  /**
   * Class field property: name
   */
  property System::String^ name {
    /**
     * Get the set's name
     */
    System::String^ get(void);
  };
  /**
   * Class field property: set_instance
   */
  property ess::clr::set_operand set_instance {
    /**
     * Get the current list of the set's data
     */
    ess::clr::set_operand get(void);
    /**
     * Set the set's data
     */
    void set(ess::clr::set_operand _set_instance);
  };

  /**
   * Perform union for a given instance of set;
   * parse operator - "u"
   *
   * @param[in] operand right-hand set operand
   */
  ess::clr::set^ uni0n(ess::clr::set^ operand);
  /**
   * Perform intersection for a given instance of set;
   * parse operator - "n"
   *
   * @param[in] operand right-hand set operand
   */
  ess::clr::set^ intersect(ess::clr::set^ operand);
  /**
   * Perform substraction for a given instance of set;
   * parse operator - "\"
   *
   * @param[in] operand right-hand set operand
   */
  ess::clr::set^ substract(ess::clr::set^ operand);
  /**
   * Perform symmetric difference for a given instance of set;
   * parse operator - "+"
   *
   * @param[in] operand right-hand set operand
   */
  ess::clr::set^ sdiff(ess::clr::set^ operand);
  /**
   * Perform complemention for a given instance of set;
   * parse operator - "_" ("|")
   *
   * @param[in] operand right-hand set operand
   */
  [[maybe_unused]] ess::clr::set^ complement(ess::clr::set^ operand);

private:
  ess::clr::set_operand _set_instance;
  System::String^ _name;
};

}; // namespace ess::clr

#endif // !__SET_CLI_HPP__
