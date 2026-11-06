#include "phxo_app.h"

#include <string>

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "phxo_handler.h"

namespace {

PhxoApp* g_app = nullptr;

}  // namespace

PhxoApp::PhxoApp() {
  g_app = this;
}

void PhxoApp::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();

  CefBrowserSettings browser_settings;

  CefWindowInfo window_info;
  window_info.SetAsPopup(NULL, "PHXO Browser");

  CefRefPtr<PhxoHandler> handler(new PhxoHandler(false));

  CefBrowserHost::CreateBrowser(window_info, handler,
                                "https://cn.bing.com", browser_settings,
                                nullptr, nullptr);
}