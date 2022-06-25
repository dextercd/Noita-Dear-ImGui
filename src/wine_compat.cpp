#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct wine_detector {
    bool on_wine = false;

    wine_detector()
    {
        auto ntdll = GetModuleHandleA("ntdll.dll");
        void* wine_get_version = GetProcAddress(ntdll, "wine_get_version");
        on_wine = wine_get_version != nullptr;
    }
};

bool running_on_wine()
{
    static const wine_detector detector;
    return detector.on_wine;
}
