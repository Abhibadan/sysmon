#include <iostream>
#include <napi.h>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdint>

#ifdef _WIN32
    #include "requiredHeader/windowsHeader.h"
#elif __linux__ || __APPLE__ || __MACH__
    #include "requiredHeader/linuxHeader.h"
#endif


#define MAX_INTEL_TOP_LVL 4
using namespace std;

#include "requiredHeader/structures.h"
#include "memoryModule/MemoryWrapper.cc"
#include "cpuModule/CpuWrapper.cc"



Napi::Object InitAll(Napi::Env env, Napi::Object exports){
    CpuWrapper::Init(env, exports);
    MemoryWrapper::Init(env, exports);
    return exports;
}

NODE_API_MODULE(Sys_info, InitAll)