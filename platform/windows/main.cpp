#include "../../core/NativeApp.h"
#include <windows.h>

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#else
int main() {
#endif
    NativeApp app;
    app.Run();
    return 0;
}