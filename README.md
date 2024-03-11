# kokkosRelocatableDeviceCode
example of kokkos using CUDA rdc

## install kokkos

set `cudaArch` for your GPU
see https://kokkos.org/kokkos-core-wiki/keywords.html#architectures

```
cudaArch="Kokkos_ARCH_AMPERE86" 
d=buildKokkosCUDA
cmake -S kokkos -B $d \
  -DCMAKE_CXX_COMPILER=g++ \
  -DKokkos_ARCH_AMPERE86=ON \
  -D${cudaArch}=ON \
  -DKokkos_ENABLE_CUDA=on \
  -DKokkos_ENABLE_CUDA_LAMBDA=on \
  -DBUILD_SHARED_LIBS=OFF \
  -DKokkos_ENABLE_CUDA_RELOCATABLE_DEVICE_CODE=ON \
  -DKokkos_ENABLE_SERIAL=ON \
  -DKokkos_ENABLE_DEBUG=on \
  -DKokkos_ENABLE_TESTS=off \
  -DCMAKE_INSTALL_PREFIX=$d/install
cmake --build $d -j 12 --target install
```

## install rdc example

```
kk=$PWD/buildKokkosCUDA/install/lib64/cmake/Kokkos
cmake -S kkRdc -B buildRdc -DKokkos_DIR=$kk
cmake --build buildRdc
```
