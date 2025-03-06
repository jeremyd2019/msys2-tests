#include <assert.h>
#include <stdio.h>
#include <windows.h>

int __stdcall testme(int a) __MINGW_ASM_CALL(testme);
__declspec(dllexport) int main_f(void) { return testme(42); }
__declspec(dllexport) int main_f2(void) { return 42; }

int main(void) {
  HMODULE lib = LoadLibraryA("lib.dll");
  assert(lib);
  printf("MAIN: lib.dll loaded\n");
  FARPROC func = GetProcAddress(lib, "lib_f");
  assert(func);
  printf("MAIN: lib_f retrieved\n");
  int lib_return = func();
  printf("MAIN: lib_f called\n");
  assert(lib_return == main_f());
  func = GetProcAddress(lib, "lib_f2");
  assert(func);
  printf("MAIN: lib_f2 retrieved\n");
  lib_return = func();
  printf("MAIN: lib_f2 called\n");
  assert(lib_return == main_f2());
  printf("MAIN: OK\n");

  return 0;
}
