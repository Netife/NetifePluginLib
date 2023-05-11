#include <iostream>
#include "include/plugins/v1/NetifePluginAgent.h"
#if defined(_WIN32)
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API
#endif
extern "C" void LIBRARY_API LoadMe(NetifePluginAgent* agent);

void LoadMe(NetifePluginAgent* agent) {
    agent->LogInfo("Netife OFFICIALLY Basic Lib hooked successfully...");
    agent->LogInfo("Netife OFFICIALLY Basic Lib's UUID is '2f81e161-7124-420e-9397-1db3cb969b0b', "
                   "please pay attention to this UUID to check if NETIFE modified");
}
