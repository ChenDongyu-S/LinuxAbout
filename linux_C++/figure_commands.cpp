
/*
选项数组的定义：
	结构体option：系统已定义，直接使用即可
	struct option
	{
		//选项长名称
		const char* name;
		//该选项是否具有附加参数；0：无  1：有  2：可选
		int has_arg;
		//指向整数，用于保存val值，设为0
		int * flag
		//选项短名称
		int val
	}
	
函数getopt_long()
函数原型：int getopt_long(int argc,char* const* argv, const char* short_options, const struct option * long_options, int * long_index)
	返回参数短名称，不存在返回-1
	如果为长选项，第五个参数输出该选项在长选项数组中的索引
	使用循环处理所有的命令行参数
	如果遇到错误信息输出错误消息并终止程序执行
	处理附加参数时，用全局变量optarg传递地址
	完成所有处理后，全局变量optind为首个非可选参数的索引
*/

//编写程序，接受如下三个选项并执行正确操作
//-h/--hlep:显示程序用法并退出
//-o filename/--output filename:指定文件名
//-v / --verbose:输出复杂信息


#include<iostream>
#include<cstdlib>
#include<getopt.h>
using namespace std;

const char * program_name;

void OutputInfo(ostream & os, int exit_code)
{
	os<<"Usage:"<<program_name<<"options[filename]"<<endl;
	os<<"-h --help:Display this usage information."<<endl;
	os<<"-o --output filename:Write output to file."<<endl;
	os<<"-v --verbose:Print verbose messages."<<endl;
	exit(exit_code);
}

int main(int argc, char* argv[])
{
	//全部段选项的合并字符，":"表示带有附加参数
	const char* const short_opts = "ho:v";
	//长选项数组，定义在前面注释已经标明
	const struct option long_opts[] =
	{
		{"help",0,NULL,'h'},
		{"output",1,NULL,'o'},
		{"verbose",0,NULL,'v'},
		{NULL,0,NULL,0}
	};
	//参数指定的输出文件名
	const char* output_filename = NULL;
	//是否显示复杂信息
	int verbose = 0;
	//保存程序名
	program_name = argv[0];
	//如果为长选项，第五个参数输出该选项在长选项数组中的索引
	int opt = getopt_long(argc,argv,short_opts,long_opts,NULL);
	//使用选项的返回值单独处理
	//使用循环处理所有的参数
	while(opt != -1)
	{
		switch(opt){
		case 'h'://-h 或 --help
			OutputInfo(cout,0);
		case 'o'://-o 或 --output，附加参数由optarg提供
			output_filename = optarg; break;
		case 'v'://-v 或者 --verbose
			verbose = 1; break;
		case '?'://用户输入了无效参数
			OutputInfo(cerr,1);
		case -1://处理完毕
			break;
		defalut://未知错误
			abort();
			
		}
		opt = getopt_long(argc,argv,short_opts,long_opts,NULL);
	}
	return 0;
}























