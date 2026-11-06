#ifndef PHXO_HANDLER_H_
#define PHXO_HANDLER_H_

#include "include/cef_client.h"

#include <list>

class PhxoHandler : public CefClient,
                    public CefDisplayHandler,
                    public CefLifeSpanHandler,
                    public CefLoadHandler {
 public:
  explicit PhxoHandler(bool use_views);
  ~PhxoHandler();

  static PhxoHandler* GetInstance();

  virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override {
    return this;
  }
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
    return this;
  }
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }

  virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                             const CefString& title) override;

  // 页面 URL 变化时更新地址栏
  virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               const CefString& url) override;

  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
  virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

  virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString& errorText,
                           const CefString& failedUrl) override;

  void CloseAllBrowsers(bool force_close);
  bool IsClosing() const { return is_closing_; }

 private:
  const bool use_views_;

  typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
  BrowserList browser_list_;

  bool is_closing_;

  IMPLEMENT_REFCOUNTING(PhxoHandler);
};

#endif  // PHXO_HANDLER_H_