#include <windows.h>

#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h"
#include "phxo_app.h"

int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPTSTR lpCmdLine,
                      int nCmdShow) {
  CefMainArgs main_args(hInstance);

  CefRefPtr<PhxoApp> app(new PhxoApp());

  // CEF 多进程：子进程入口
  int exit_code = CefExecuteProcess(main_args, app.get(), nullptr);
  if (exit_code >= 0) {
    return exit_code;
  }

  // ===== 命令行参数：内存优化 =====
  CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
  command_line->InitFromString(::GetCommandLineW());

  command_line->AppendSwitchWithValue("renderer-process-limit", "2");
  command_line->AppendSwitchWithValue(
      "disable-features",
      "Translate,AutofillServerCommunication,OptimizationHints,"
      "MediaRouter,CalculateNativeWinOcclusion,"
      "IsolateOrigins,site-per-process");
  command_line->AppendSwitch("disable-site-isolation-trials");
  command_line->AppendSwitchWithValue(
      "enable-features",
      "NetworkServiceInProcess,StorageServiceInProcess,"
      "AudioServiceInProcess,TracingServiceInProcess");
  command_line->AppendSwitch("disable-gpu-shader-disk-cache");
  command_line->AppendSwitchWithValue(
      "js-flags", "--max-old-space-size=128 --memory-reducer");

  // ===== CEF 设置 =====
  CefSettings settings;
  settings.no_sandbox = true;
  settings.multi_threaded_message_loop = false;
  settings.log_severity = LOGSEVERITY_WARNING;

  CefInitialize(main_args, settings, app.get(), nullptr);

  CefRunMessageLoop();

  CefShutdown();

  return 0;
}