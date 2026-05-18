#pragma once

class NativeApp {
public:
    NativeApp();
    ~NativeApp();
    void Run();

private:
    void* w; // Opaque pointer to hide webview implementation
};
