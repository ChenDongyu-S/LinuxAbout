/*
makefile

	make命令：负责C/C++程序编译与连接
		make根据指定命令进行构建
		构建规则：GNUmakefile\makefile\Makefile
	Makefile文件格式
	makefile语法
		基本语法、变量、条件判断、循环、函数
		
	makefile文件基本格式
		target ...:prerequisites ...
		[Tab键] commands
	makefile文件规则：
		makefile文件有一系列规则构成
		规则的目的：构建目标的先决条件是什么以及如何构建目标
		如果未指定目标，缺省执行第一个目标
		若prerequisites中有一个以上的文件比target要新，之心commands所定义的命令
		
	target：目标
		通常为编译器的文件名，已制定要构建的对象，也可以时执行文件，还可以是标签（操作名称，伪目标）
		可以为单一目标，也可以为空格分隔的多个目标
		每个目标都顶一个一组处理规则，和其相关规则构成规则链
	prerequisites：先决条件
		为生成目标所需要的先决文件或目标（前置条件）
		一般为空格分隔的文件名指定目标是否重建的判断标准，即只要有一个先决文件不存在或有过更新，就重建目标
		如果目标先决条件本身需要重建，则匹配该先决条件的目标，执行器对应的命令
		
	commands：命令
		由一行或者多行shell命名组成，命令前有Tab键
		只是如何构建目标，一般为生成目标文件
		每行命令都在单独的进程中执行，彼此没没有继承关系，不能简单传递数据；解决办法：用分号将多条命令书写在单行（此时可以用"\"折行），或者为该条规则添加指示".ONESHELL"
		
	伪目标：操作名称，而不是文件名
		删除编译后的二进制木匾文件，例如
		clean:
			rm -f *.o
		执行命令时需指定伪目标:$make clean
		若当前目录下有clean文件，则此规则不会被执行；此时可用".PHONY:clean"明确指示clean为伪目标；make将跳过文件查找过程执行其对应的命令
		执行清楚任务的伪目标一般放置在脚本的最后
		
	伪目标惯例
		all:所有目标的目标，一般为编译所有目标，对同时编译的多个程序极为有用
		clean:删除由make创建的文件
		install:安装一编译好的程序，主要任务是完成目标执行文件的拷贝
		print:列出改变过的源文件
		tar:打包备份源程序，形成tar文件
		dist:创建压缩文件，一般将tar文件压缩成Z文件或者gz文件
		TAGS:更新所有的目标，以备完整的重编译使用
		check和test:一般用来测试makefile的流程
		
		
	示例：假设主程序为main.c,使用libary库
	
	#注释
	prog:main.o libary.o
		cc -o prog main.o libary.o
	main.o:main.c libary.h
		cc -c main.c
	libary.o:libary.c libary.h
		cc -c libart.c
	>PHONY clean
	clean:
		rm main.o libary.o
		
	makefile文件语法	
	行解析，命令安行解析
		命令行的行首字符为Tab键，其他行的行首字符不得为Tab键，但可以使用多个空格缩进
	换行：命令太长时间，行尾用"\"换行
	注释：行首字符为"#"的文本行
	关闭回显：在行首字符后和命令前添加"@"
		未关闭回显时，make会首先回显（打印）命令，然后执行改命令
		通常尽在注释和春现实的echo名领先使用此功能
		
	include filename :包含其他文件
		处理模式与C/C++leisi 
		行首加"-"：忽略文件包含错误
		
	通配符：
		"*"任意数目的字符
		"?"任意一个字符
		[abd]存在括号内的某个字符
		[0-9]存在集合中的某个字符
		[^abc]存在不是括号内的某个字符
		
	变量：
		基本变量定义：var_name = value
		$(变量名称)：引用变量（中间无多余空格）；shell变量用"$$"例如："@echo $$HOME"
		变量在使用时展开，形式上类似于宏替换
		变量的适用场合：目标、先决条件、命令、新的变量
		
	内置变量
		$(CC) :当前使用的编译器；$(MAKE)：当前使用的make工具
	自动变量
		$@:当前目标；$<:当前目标的首个先决条件；$?：比目标更新的所有先决条件；$^：所有先决条件；$(@D)和$(@F):$@的目录名和文件名；$(<D)和$(<F)：$<的目录名的文件名 






















*/
