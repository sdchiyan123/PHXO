#include "phxo_handler.h"

#include <windows.h>

#include "include/cef_browser.h"

// 这个文件只放 Windows 平台相关的窗口处理逻辑。
// 注意：不要在这里定义 wWinMain，入口函数在 phxo_win.cc 里。
// 之前编译报 "wWinMain 已经在 phxo_handler_win.obj 中定义"，
// 就是因为这里多写了一个 wWinMain，现在删掉它。

// 如果以后需要处理窗口消息、修改窗口标题等平台相关操作，
// 在这里补充即可。目前保持为空。