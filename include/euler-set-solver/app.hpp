#pragma once
#ifndef __APP_CLI_HPP__
#define __APP_CLI_HPP__

/*
 *	Global includes, cli dll exports
 */
#pragma region GIE
#pragma managed

#include <euler-set-solver/parser.hpp>

#pragma unmanaged
#pragma endregion

#pragma managed

namespace ess::clr {
  public ref class app {
  public:
    static void run(void);
  };
}; // namespace ess::clr

#pragma unmanaged

#endif // !__APP_CLI_HPP__
