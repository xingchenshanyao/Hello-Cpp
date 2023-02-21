#include<iostream>
using namespace std;
#include<string> //字符串头文件
#include<ctime> //时间头文件
#include<unistd.h> //Linux/unix 的系统调用
#include<fstream> //文件操作头文件
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
//职工管理系统



int main()
{
    // 测试代码1
    // Worker * worker = NULL;
    // worker = new Employee(1, "张三", 1);
    // worker->showInfo();
    // delete worker;
    // worker = new Manager(2, "李四", 2);
    // worker->showInfo();
    // delete worker;
    // worker = new Boss(3, "王五", 3);
    // worker->showInfo();
    // delete worker;

    //实例化管理者对象
    WorkerManager wm;

    int choice = 0; //用来存储用户的选项
    while(true)
    {
        //调用展示菜单的成员函数
        wm.Show_Menu();

        cout<<"请输入您的选择："<<endl;
        cin>>choice; //接受用户的选项

        switch (choice)
        {
        //退出系统
        case 0:
            wm.ExitSystem();
            break;
        //增加职工
        case 1:
            wm.Add_Emp();
            break;
        //显示职工
        case 2:
            wm.Show_Emp();
            break;
        //删除职工
        case 3:
            wm.Del_Emp();
            break;
        //修改职工
        case 4:
            wm.Mod_Emp();
            break;
        //查找职工
        case 5:
            wm.Find_Emp();
            break;
        //排序职工
        case 6:
            wm.Sort_Emp();
            break;
        //清空文档
        case 7:
            wm.Clean_File();
            break;
        default:
            // system("cls"); //清屏操作，windows系统使用

        }
    }
    

    
    cout<<"----------------------------------------------------------------------"<<endl;
    //pause();
    return 0;
}