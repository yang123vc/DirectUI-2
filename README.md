# DirectUI

Windows自带的未公开DUI库，主要是把chuyu和Tranch的一些工作组合起来了

- **demangler** 用作解析符号.

- **UITest** 是示例工程，主要文件`UITest.cpp`中提供了初始化的方法、窗口消息解析的方法和XML组件交互的方法，`*.xml`文件是UIFILES文件，放入`UITest.rc`后在`UITest.cpp`中加载，可以呈现在主窗口上.

- **DirectUI** 是UI框架，包含了`dui70.dll`的所有导出函数头和不完全类定义.
