#pragma warning(push)
#pragma warning(disable : 4677)
#pragma warning(disable : 4267)
#pragma warning(disable : 4506)

#include <euler-set-solver/app.hpp>

#pragma managed

int __cdecl main(void) {
  ess::clr::app::run();
  return 0;
};

#pragma unmanaged
#pragma warning(pop)
