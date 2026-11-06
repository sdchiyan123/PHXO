#include "phxo_handler.h"

#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/cef_parser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"

namespace {

PhxoHandler* g_instance = nullptr;

}  // namespace

PhxoHandler::PhxoHandler(bool use_views)
    : use_views_(use_views), is_closing_(false) {
  DCHECK(!g_instance);
  g_instance = this;
}

PhxoHandler::~PhxoHandler() {
  g_instance = nullptr;
}

PhxoHandler* PhxoHandler::GetInstance() {
  return g_instance;
}

void PhxoHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
                                const CefString& title) {
  CEF_REQUIRE_UI_THREAD();

  if (use_views_) {
    CefRefPtr<CefBrowserView> browser_view =
        CefBrowserView::GetForBrowser(browser);
    if (browser_view) {
      CefRefPtr<CefWindow> window = browser_view->GetWindow();
      if (window) {
        window->SetTitle(title);
      }
    }
  }
}

void PhxoHandler::OnAddressChange(CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefFrame> frame,
                                  const CefString& url) {
  CEF_REQUIRE_UI_THREAD();

  if (!frame->IsMain()) return;
  // SetAsPopup 版本没有地址栏，这里什么都不做
}

void PhxoHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();
  browser_list_.push_back(browser);
}

bool PhxoHandler::DoClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  if (browser_list_.size() == 1) {
    is_closing_ = true;
  }

  return false;
}

void PhxoHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  BrowserList::iterator bit = browser_list_.begin();
  for (; bit != browser_list_.end(); ++bit) {
    if ((*bit)->IsSame(browser)) {
      browser_list_.erase(bit);
      break;
    }
  }

  if (browser_list_.empty()) {
    CefQuitMessageLoop();
  }
}

void PhxoHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame,
                              ErrorCode errorCode,
                              const CefString& errorText,
                              const CefString& failedUrl) {
  CEF_REQUIRE_UI_THREAD();

  if (errorCode == ERR_ABORTED) {
    return;
  }

  std::stringstream ss;
  ss << "<html><body bgcolor=\"white\">"
        "<h2>Failed to load URL: "
     << failedUrl.ToString() << " with error: " << errorText.ToString()
     << "</h2></body></html>";

  frame->LoadURL("data:text/html;charset=utf-8," +
                 CefURIEncode(ss.str(), false).ToString());
}

void PhxoHandler::CloseAllBrowsers(bool force_close) {
  if (browser_list_.empty()) {
    return;
  }

  BrowserList::const_iterator it = browser_list_.begin();
  for (; it != browser_list_.end(); ++it) {
    (*it)->GetHost()->CloseBrowser(force_close);
  }
}