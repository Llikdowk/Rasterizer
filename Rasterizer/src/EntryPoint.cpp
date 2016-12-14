#include <Window.h>
#include "Profiler.h"

int main(int, char**) {
//#ifdef __PROFILER_ENABLED__
//	const char* profiler_init[] {"Rasterizer"};
//	Profiler::detect(1, profiler_init);
//#endif
	Window window;
	window.start();
//#ifdef __PROFILER_ENABLED__
//	Profiler::dumphtml();
//#endif
	return 0;
}
