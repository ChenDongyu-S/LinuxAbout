/*
程序退出码：
	程序：结束时传递给操作系统的整形数据
		实际上时main（）的返回值
		其他函数也可以调用exit（）函数返回特定
		退出码的变量名称经常为exit_code
		应该仔细设计程序退出码，确保能过区分不同错误
	操作系统：响应程序退出码，如果必要，进行后续处理
	shell编程可以通过echo $? 查看上一个程序的退出码是什么
	
系统调用错误处理：
	实现逻辑：
		C程序使用断言，C++程序使用断言或者异常处理机制
	两个主要问题
		系统调用：访问系统资源的手段
		系统调用失败原因：资源不足；因权限不足而被阻塞；调用参数无效，如无效的内存地址或无效的文件描述符；被外部事件中孤单；不可预计的外部原因
		资源管理：已分配资源必须在任何情况下都能正确释放
		
	Linux使用整数表示系统调用错误
		标准错误码为一E开头的全大写宏
		宏errno（使用方法类似全局变量）：表示错误码，位于头文件errno.h中
		每次错误都重写该值，处理错误时必须保留其副本
		函数strerror（）：返回宏errno对应的错误说明字符串，位于头文件string.h中
		
资源管理
	必须予以明确管理的资源类型
		内存、文件描述符、文件指针、临时文件、同步对象
	资源管理流程
		1：分配资源
		2：正常处理流程
		3：如果流程失败释放资源并推出，否则执行正常处理流程
		4：释放资源
		5：函数返回
		
系统日志
	系统或者程序运行的记录
	系统日志进程：syslogd/rsyslogd
		两者均为守护进程（daemon），即在后台运行的进程，没有控制终端，也不会接受用户输入，附近工厂通常为init进程
		日志文件一般为"/dev/log"，日志文件一般保存在"/var/log"目录下
		rsyslogd既能接收用户进程输出的日志，也能接收内核日志；在接受到日志信息以后，会输出到特定的日志文件中；日志信息的分发可配置
		
	日志生成函数：syslog()
		头文件："syslog.h"
		原型：void syslog(int priority,const char* msg,...);
		可变参数列表，用于结构化输出
		priority：日志优先级设施值（一般默认为LOG_USER）与日志级别的位或
		
		日志级别：0-7：LOG_EMERG（0系统不可用） LOG_ALERT（1报警需要立即采取行动） LOG_CRIT（2严重情况） LOG_ERR（3错误） LOG_WARNING（4警告） LOG_NOTICE（5通知） LOG_INFO（6信息） LOG_DEBUG（7调试）
		
	日志打开函数：openlog()
		原型：void openlog(const char * ident, int logopt,int facility);
		改变syslog()函数的默认输出方式，以进一步结构化日志内容
		ident：标志项，指定添加到日志消息的日期和时间后的字符串
		logopt：日志选项，用于配置syslog()函数的行为，取值为LOG_PID（在日志消息中包含程序PID）、LOG_CONS（如果日志不能记录至日志文件，则打印到终端）、LOG_ODELAY（延迟打开日志功能直到第一次调用syslog()函数）LOG_NDELAY（不延迟打开日志功能）的位或
		facility：用于修改syslog()函数的默认设施值一般位置LOG_USER不变
		
		
	日志过滤函数：setlogmask()
		原型：int setlogmask(int maskpri);
		设置日志掩码，大于maskpri的日志级别信息被过滤
		返回值：设置日志掩码前的日志掩码旧值
	日志关闭函数：closelog()
		原型void closelog()
		
用户信息
	UID EUID GID EGID
		每个进程拥有两个用户ID：UID（真实用户ID）和EUID（有效用户ID）
		EUID的目的：方便资源访问，运行程序的用户拥有该程序有效用户的权限
		组与用户类似
	用户信息处理函数
		获取真实用户ID：uid_t getuid();
		获取有效用户ID：uid_t geteuid();
		获取真实组ID：gid_t getgid();
		获取有效组ID：gid_t getegid();
		
		设置真实用户ID：uid_t setuid();
		设置有效用户ID：uid_t seteuid();
		设置真实组ID：gid_t setgid();
		设置有效组ID：gid_t setegid();
		
	
*/
#include<unistd.h>
#include<stdio.h>

int main(){
	uid_t uid= getuid();
	uid_t euid= geteuid();
	printf("uid:%d;euid:%d",uid,euid);
	return 0;
}















