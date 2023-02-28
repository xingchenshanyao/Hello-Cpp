#pragma once
#include<iostream>
using namespace std;
#include<string>

//身份抽象基类
class Identity
{
public:

    //操作菜单 纯虚函数
    virtual void operMenu() = 0;

    //用户名
    string m_Name;
    //密码
    string m_Pwd;
};