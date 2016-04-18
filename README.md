# webcpps
基于C++ Poco框架的HTTP动态服务器

纯C++开发，基于Poco框架，高性能、多线程

目标单一：纯动态资源服务器

# 依赖
* PocoUtil 
* PocoNet 
* PocoFoundation

# 使用方法
webcppd是基于动态库加载的web动态服务器
通过配置文件配置动态库搜索目录
通过url(/a/b/c)指定动态库(liba.so)和需要运行的函数(bImpl)，默认动态库名为libhome.so，默认运行函数是indexImpl。系统仅仅捕捉a和b，其余部分可选，例如c的含义由开发者自行定义使用。

编译:
make
即可

清理:
make clean
即可

运行:
make run
即可

停止:
make stop
即可

# 开发
开发者的工作很简单。只需三步：

* 编写Poco::Net::HTTPRequestHandler的子类例如A，实现void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
* 编写 extern "C" Poco::Net::HTTPRequestHandler* aImpl()函数，返回 new A；
* 编译为动态库例如libA.so并把动态库放置在配置的搜索目录中,测试访问http://localhost:8888/A/a即可

# 相关文章
[Poco HTTP 服务器](http://www.webcpp.net/blog/set/6.html)
