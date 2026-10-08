# TinyWebServer 项目入口

原目录：`D:\Code\source\repos\TinyWebServer`。

原 README 链接到 [qinguoyi/TinyWebServer](https://github.com/qinguoyi/TinyWebServer)。原目录包含 LICENSE，应保留原项目来源与许可，不应把整套开源实现标注成独立原创算法题。

本轮在旧目录中数到该项目的18份 C/C++源码或头文件，其中包括 Webbench 压测工具源码；按一个完整项目理解。另一个 `WebServer` 的 vcxproj 引用 `../../TinyWebServer/config.cpp`、`main.cpp`、`webserver.cpp` 等，所以不能重复计数。

## 依赖与学习顺序

项目使用 Linux socket/epoll、pthread、MySQL客户端库。当前仓库的 Windows MinGW 单文件练习验证不能证明它可运行。

1. `main.cpp`、`config.cpp`、`webserver.cpp`：程序入口、配置和事件循环。
2. `http/http_conn.*`：请求状态机、读写与连接生命周期。
3. `threadpool`、`lock`：任务分派、同步与线程池。
4. `timer`、`log`：超时和日志。
5. `CGImysql`：连接池与数据库调用；最后再研究集成测试和压测。

本次仅建立项目索引，没有复制整个工程和网页资源、没有连接数据库或启动服务，也没有验证 README 中的并发性能宣称。原项目仍完整保存在上述目录。
