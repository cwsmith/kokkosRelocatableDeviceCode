#include "helper.h"

KOKKOS_INLINE_FUNCTION int kkInlineFunc(int i) {
   return i+2; 
}

KOKKOS_FUNCTION int kkFunc(int i) {
   return i+2; 
}
