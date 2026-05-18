#include "NativeApp.h"
#include "webview/webview.h"
#include "web_content.h"
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

NativeApp::NativeApp() {
    auto* webview_instance = new webview::webview(false, nullptr);
    webview_instance->set_title("ProBilling");
    webview_instance->set_size(1024, 768, WEBVIEW_HINT_NONE);
    w = webview_instance;
}

NativeApp::~NativeApp() {
    if (w) {
        delete static_cast<webview::webview*>(w);
        w = nullptr;
    }
}

void NativeApp::Run() {
    if (w) {
        auto* webview_instance = static_cast<webview::webview*>(w);
        
        // Write embedded HTML to a temporary file to enable localStorage
        // Data URIs often restrict localStorage access.
        fs::path temp_path = fs::temp_directory_path() / "probilling_app.html";
        
        std::ofstream out(temp_path, std::ios::binary);
        if (out) {
            out.write(reinterpret_cast<const char*>(html_data), html_len);
            out.close();
            
            std::string url = "file:///" + temp_path.generic_string();
            webview_instance->navigate(url);
        } else {
            // Fallback if file write fails (unlikely)
            std::string html(reinterpret_cast<const char*>(html_data), html_len);
            webview_instance->set_html(html);
        }
        
        webview_instance->run();
    }
}
