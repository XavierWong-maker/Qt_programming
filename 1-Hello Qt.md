# QT简介

## 简介

Qt是一个跨平台的C++图形用户界面应用程序框架，提供给应用程序开发者建立艺术级的图形用户界面所需的所用功能。Qt很容易扩展，并且允许真正地组件编程。Qt与GTK、KDE、MFC，OWL，VCL，ATL是一样的图形界面库。

## 开发工具

QT开发工具包含Qt Creator、Qt Designer、Qt Linguist、Qt Assistant、Qmake。

**1、Qt Creator**
Qt Creator是用于Qt开发的轻量级跨平台集成开发环境。

**2、Qt Designer**
Qt Designer是强大的拖曳式图形化用户界面排版和设计工具。

Qt Designer功能如下：

A、支持表单和对话框的创建，可即时预览

B、与Qt版面系统集成

C、宏大的标准widgets集

D、支持客户定制的widgets和对话框

E、与Microsoft® Visual Studio .NET无缝集成

**3、Qt Linguist**
Qt Linguist一整套工具，支持对Qt应用作快捷无误的翻译，是一组能理顺国际化工作流的工具。

Qt Linguist功能如下：

A、采集所有的用户界面文本并以一个简洁的窗口将其展现给人工译者

B、支持所有语言

C、从单一应用的二进制程序内部提供同时多语言支持及同时多写入系统

**4、Qt Assistant**
Qt Assistant是可定制可重发布的帮助文件和文档阅读器。

Qt Assistant功能如下：

A、简单明快的web浏览器般导航、书签和文档文件连接

B、支持富文本HTML

C、全文本关键词查阅

D、可定制并随Qt供应

**5、Qmake**
Qmake跨平台makefile生成器。

Qmake功能如下：

A、读取工程源码，生成依赖关系树，生成平台相关工程和makefiles

B、与Visual Studio及Xcode集成

## QT模块

QT模块分为QT基础模块和QT扩展模块。

### 基础模块

A、Qt Core，提供核心的非GUI功能，所有模块都需要Qt Core模块。Qt Core模块的类包括了动画框架、定时器、各个容器类、时间日期类、事件、IO、JSON、插件机制、智能指针、图形（矩形、路径等）、线程、XML 等。

B、Qt Gui，提供 GUI 程序的基本功能，包括与窗口系统的集成、事件处理、OpenGL 和 OpenGL ES 集成、2D 图像、字体、拖放等，一般由 Qt 用户界面类内部使用，也可以用于访问底层的 OpenGL ES 图像 API。Qt Gui 模块提供的是所有图形用户界面程序都需要的通用功能。

C、Qt Multimedia，提供视频、音频、收音机以及摄像头等功能，需要在 pro 文件中添加 QT += multimedia。

D、Qt Network，提供跨平台的网络功能，需要在 pro 文件中添加 QT += network。

E、Qt Qml，提供供 QML（一种脚本语言，也提供 JavaScript 的交互机制） 使用的 C++ API，需要在 pro 文件中添加 QT += qml。

F、Qt Quick，允许在 Qt/C++ 程序中嵌入 Qt Quick（一种基于 Qt 的高度动画的用户界面，适合于移动平台开发），需要在 pro 文件中添加 QT += quick。

G、Qt SQL，允许使用 SQL 访问数据库，需要在 pro 文件中添加 QT += sql。

H、Qt Test，提供 Qt 程序的单元测试功能，需要在 pro 文件中添加 QT += testlib。

I、Qt Webkit，基于 WebKit2 的实现以及一套全新的 QML API

### 扩展模块

（1）Qt 3D，提供声明式语法，在 Qt 程序中可以简单地嵌入 3D 图像。Qt 3D 为 Qt Quick 添加了 3D 内容渲染。Qt 3D 提供了 QML 和 C++ 两套 API，用于开发 3D 程序。

（2）Qt Bluetooth，提供用于访问蓝牙无线设备的 C++ 和 QML API。

（3）Qt Contacts，用于访问地址簿或者联系人数据库的 C++ 和 QML API。

（4）Qt Concurrent，封装了底层线程技术的类库，方便开发多线程程序。

（5）Qt D-Bus，是一个仅供 Unix 平台使用的类库，用于利用 D-Bus 协议进行进程间交互。

（6）Qt Graphical Effects，提供一系列用于实现图像特效的类，比如模糊、锐化等。

（7）Qt Image Formats，支持图片格式的一系列插件，包括 TIFF、MNG、TGA 和 WBMP。

（8）Qt JS Backend，模块没有公开的 API，是 V8 JavaScript 引擎的一个移植，仅供 QtQml 模块内部使用。

（9）Qt Location，提供定位机制、地图和导航技术、位置搜索等功能的 QML 和 C++ API。

（10）Qt OpenGL，方便在 Qt 应用程序中使用 OpenGL，仅仅为了程序从 Qt 4 移植到 Qt 5 的方便才保留下来，如果你需要在新的 Qt 5 程序中使用 OpenGL 相关技术，需要使用的是 QtGui 模块中的 QOpenGL。

（11）Qt Organizer，使用 QML 和 C++ API 访问组织事件（organizer event）。organizer API 是 Personal Information Management API 的一部分，用于访问 Calendar 信息。通过 Organizer API 可以实现：从日历数据库访问日历时间、导入 iCalendar 事件或者将自己的事件导出到 iCalendar。

（12）Qt Print Support，提供对打印功能的支持。

（13）Qt Publish and Subscribe，为应用程序提供对项目值的读取、导航、订阅等的功能。

（14）Qt Quick 1，从 Qt 4 移植过来的 QtDeclarative 模块，用于提供与 Qt 4 的兼容。如果你需要开发新的程序，需要使用 QtQuick 模块。

（15）Qt Script，提供脚本化机制。这也是为提供与 Qt 4 的兼容性，如果要使用脚本化支持，请使用 QtQml 模块的 QJS* 类。

（16）Qt Script Tools，为使用了 Qt Script 模块的应用程序提供的额外的组件。

（17）Qt Sensors，提供访问各类传感器的 QML 和 C++ 接口。

（18）Qt Service Framework，提供客户端发现其他设备的服务。Qt Service Framework 为在不同平台上发现、实现和访问服务定义了一套统一的机制。

（19）Qt SVG，提供渲染和创建 SVG 文件的功能。

（20）Qt System Info，提供一套 API，用于发现系统相关的信息，比如电池使用量、锁屏、硬件特性等。

（21）Qt Tools，提供了 Qt 开发的方便工具，包括 Qt CLucene、Qt Designer、Qt Help 以及 Qt UI Tools 。

（22）Qt Versit，提供了对Versit API 的支持。Versit API是Personal Information Management API 的一部分，用于 QContacts 和 vCard 以及 QOrganizerItems 和 iCalendar 之间的相互转换。

（23）Qt Wayland，仅用于Linux平台，用于替代 QWS，包括 Qt Compositor API（server）和 Wayland 平台插件（clients）。

（24）Qt WebKit，从 Qt 4 移植来的基于 WebKit1 和 QWidget 的 API。

（25）Qt Widgets，使用 C++ 扩展的 Qt Gui 模块，提供了一些界面组件，比如按钮、单选框等。

（26）Qt XML，SAX 和 DOM 的 C++ 实现。该模块已经废除，请使用 QXmlStreamReader/Writer。

（27）Qt XML Patterns，提供对 XPath、XQuery、XSLT 和 XML Schema 验证的支持。