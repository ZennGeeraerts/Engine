#include "SmileEnginePCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "SmileEngine.h"

int main(int, char*[]) {
	dae::SmileEngine engine;
	engine.Run();
    return 0;
}