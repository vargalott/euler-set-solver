#pragma once
#ifndef __APP_CLI_HPP__
#define __APP_CLI_HPP__

#pragma managed
#include <euler-set-solver/parser.hpp>

#pragma unmanaged
#include <iostream>
#include <stdexcept>


#pragma managed
namespace ess::clr {

/**
 * Main app class
 *
 * ...
 *
 * Implements main app execute line
 */
public ref class app {
public:
   /**
   * Perform application executing
   */
  static void run(void);
};

}; // namespace ess::clr

#endif // !__APP_CLI_HPP__
