#pragma once //防止头文件重复包含
#include <iostream> //包含输入输出流头文件
using namespace std; //使用标准命名空间
#include <string>

//职工抽象类
class Worker
{
public:
    //显示个人信息
    virtual void showInfo() = 0;
    //获取岗位名称
    virtual string getDeptName() = 0;

    //职工编号
    int m_Id;
    //职工姓名
    string m_Name;
    //部门编号
    int m_DeptId;
};
