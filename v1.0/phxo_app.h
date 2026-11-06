#ifndef PHXO_APP_H_
#define PHXO_APP_H_

#include "include/cef_app.h"

class PhxoApp : public CefApp,
                public CefBrowserProcessHandler {
 public:
  PhxoApp();
  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
      override { return this; }
  virtual void OnContextInitialized() override;

 private:
  IMPLEMENT_REFCOUNTING(PhxoApp);
};

#endif  // PHXO_APP_H_