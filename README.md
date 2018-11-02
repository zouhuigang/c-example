下载七牛 c++ sdk

	cd ~
	git clone https://github.com/qiniu/c-
	
环境(该项目依赖库curl和openssl库):

	sudo apt-get install libcurl4-openssl-dev
	
centos7:
	
	yum install libcurl-dev libcurl-devel
	yum install openssl openssl-devel
	


编写Makefile文件:

cd /root/c-sdk && vi Makefile

	INCLUDE_PATH=-Ibase64 -IcJSON -Iqiniu
	SOURCE_FILES=\
	        b64/b64.c\
	        b64/urlsafe_b64.c\
	        cJSON/cJSON.c\
	        qiniu/auth_mac.c\
	        qiniu/base.c\
	        qiniu/base_io.c\
	        qiniu/cdn.c\
	        qiniu/conf.c\
	        qiniu/fop.c\
	        qiniu/http.c\
	        qiniu/io.c\
	        qiniu/macro.h\
	        qiniu/qetag.c\
	        qiniu/reader.c\
	        qiniu/resumable_io.c\
	        qiniu/rs.c\
	        qiniu/tm.c\
	
	all: $(SOURCE_FILES)
	        gcc -g -c -fPIC $^ $(INCLUDE_PATH) -lcurl -lcrypto -lssl -lm

保存:wq,	

	chmod +x Makefile
	make

上面的Makefile是把所有代码编译为.o目标文件


我们可以使用工具ar打包为静态库

	ar rcs libqiniu.a *.o


我们也可以基于.o文件构建动态库

	gcc -shared -o libqiniu.so *.o  -lcurl -lcrypto -lssl -lm




最终得到的构建完毕的发布包,官方得到的（自己的在同一个目录）：

	.
	├── include
	│   ├── b64
	│   │   ├── b64.h
	│   │   └── urlsafe_b64.h
	│   ├── cJSON
	│   │   └── cJSON.h
	│   └── qiniu
	│       ├── base.h
	│       ├── cdn.h
	│       ├── conf.h
	│       ├── fop.h
	│       ├── http.h
	│       ├── io.h
	│       ├── macro.h
	│       ├── qetag.h
	│       ├── reader.h
	│       ├── region.h
	│       ├── resumable_io.h
	│       ├── rs.h
	│       └── tm.h
	└── lib
	    ├── libqiniu.a
	    └── libqiniu.so


### 指定模式运行

	cc -g -std=c99 1.c
	cc -g -std=c99 -lqiunu


清理:

	make clean 


### 问题汇总


Q：
	make报错
	recipe commences before first target.  Stop

A：

	1. 上一行换行符号 \ 后面有空格

	2. 本行前面的空白有非法字符
	

Q:

	make: *** No rule to make target `qiniu/region.c', needed by `all'.  Stop.

A:

	发现region.c不存在，所有makefile中删除这行即可


### 参考文档

[https://blog.csdn.net/guoer9973/article/details/51492466](https://blog.csdn.net/guoer9973/article/details/51492466)

[https://github.com/xiaoyuLi-China0372/wheel_and_note/tree/master/queue](https://github.com/xiaoyuLi-China0372/wheel_and_note/tree/master/queue)

[https://wenku.baidu.com/view/d01cb0240722192e4536f60a.html](https://wenku.baidu.com/view/d01cb0240722192e4536f60a.html)
[https://www.zhihu.com/question/23844552](https://www.zhihu.com/question/23844552)