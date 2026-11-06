# PHXO Browser

> 一个基于 CEF (Chromium Embedded Framework) 构建的轻量、纯净、可定制的 Windows 桌面浏览器。

![Platform](https://img.shields.io/badge/platform-Windows%20x64-blue)
![CEF](https://img.shields.io/badge/CEF-109.1.18-green)
![License](https://img.shields.io/badge/license-MIT-orange)

---

## 📖 项目简介

PHXO Browser 是一个使用 C++ 和 CEF 从零构建的 Chromium 浏览器。它的核心理念是 **纯净、轻量、完全可控**——没有账号同步、没有遥测数据收集、没有不必要的后台服务。

---

## 📂 版本目录

| 版本 | 源码位置 | 状态 |
|------|----------|------|
| v1.0 | [`v1.0/`](./v1.0) | ✅ 当前稳定版 |
| v2.0 | 计划中 | 🚧 开发中 |

---

## ✨ 主要特性

- **Chromium 内核** — 与 Chrome / Edge 同源，完整支持现代网页标准、复杂 JavaScript 和 HTML5 视频。
- **H.264 视频播放** — 集成 CefSharp H.264 x64 二进制包，B 站等依赖 H.264 的视频网站可正常播放。
- **极致内存优化** — 关闭站点隔离、合并网络/存储进程、限制 V8 堆大小，单标签页浏览内存约 250 MB。
- **纯净无捆绑** — 无 Google 账号同步、无遥测上报、不收集任何个人隐私。
- **原生 C++ 性能** — 直接基于 CEF 底层开发，无 Electron 等框架的额外开销。

---

## 📥 下载

| 版本 | 平台 | 下载 |
|------|------|------|
| v1.0.0 | Windows x64 | [PHXO_Setup.exe](https://github.com/sdchiyan123/PHXO/releases/download/v1.0.0/PHXO_Setup.exe) |

> ⚠️ **下载提示**：建议安装前暂时关闭杀毒软件的误报拦截。

---

## 🛠️ 安装步骤

1. 下载 `PHXO_Setup.exe`。
2. 双击运行，按提示完成安装（默认路径 `C:\Program Files\PHXO`）。
3. 从开始菜单或桌面启动 **PHXO Browser**。
4. 默认主页为 `cn.bing.com`，在地址栏输入网址即可浏览。

---

## 🧱 技术栈

| 组件 | 说明 |
|------|------|
| 语言 | C++17 |
| 内核 | CEF 109.1.18 (Chromium 109) |
| 构建 | CMake + MSVC (Visual Studio) |
| 视频解码 | CefSharp.H264.x64 (含 H.264/AAC) |
| UI 框架 | CEF Views (CefWindow / CefPanel / CefBrowserView) |

---

## 🔨 从源码构建

```powershell
cd v1.0
mkdir build
cd build
cmake .. -G "Visual Studio 18 2026" -A x64
cmake --build . --config Release
