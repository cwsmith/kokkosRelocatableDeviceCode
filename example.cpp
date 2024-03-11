#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
#include "helper.h"

KOKKOS_INLINE_FUNCTION int kkInlineFuncLocal(int i) {
   return i+2; 
}

template<typename T>
void checkVal(T view) {
  auto checkVal = KOKKOS_LAMBDA(int i) {
    assert(view(i) == i+2);
  };
  Kokkos::parallel_for("checkVal", view.size(), checkVal); 
}

int main(int argc, char* argv[]) {
  Kokkos::ScopeGuard guard(argc, argv);
  Kokkos::DefaultExecutionSpace().print_configuration(std::cout);

  Kokkos::Timer timer;
  size_t vSize = 1024*1024;
  Kokkos::View<int*> v("view", vSize);
  auto rdc = KOKKOS_LAMBDA(int i) {
    v(i) = 0;
    //v(i) = kkInlineFunc(i); // nvlink error   : Undefined reference to '_Z12kkInlineFunci' in 'CMakeFiles/example.dir/example.cpp.o'
    v(i) = kkFunc(i);
  };
  Kokkos::parallel_for("rdc", vSize, rdc);
  Kokkos::fence(); //parallel_for is async
  double time = timer.seconds();
  std::cout << "kkFunc time: " << time << "\n";

  checkVal(v);

  timer.reset();
  auto inlineLocal = KOKKOS_LAMBDA(int i) {
    v(i) = 0;
    v(i) = kkInlineFuncLocal(i);
  };
  Kokkos::parallel_for("inlineLocal", vSize, inlineLocal);
  Kokkos::fence(); //parallel_for is async
  time = timer.seconds();
  std::cout << "kkInlineFuncLocal time: " << time << "\n";

  checkVal(v);

  std::cout << "done\n";
  return 0;
}
