#pragma once
#include<iostream>
using namespace std;
#include"identity.hpp"
// #define_CRT_SECURE_NO_WARNINGS
#include"order.hpp"

//老师类
class Teacher:public Identity
{
public:
    //默认构造
    Teacher();

    //有参构造(职工编号、姓名、密码)
    Teacher(int empId, string name, string pwd);

    //菜单界面
    virtual void operMenu();

    //查看所有预约
    void showAllOrder();

    //审核预约
    void validOrder();

    //教师编号
    int m_EmpId;
};

//---------------------------------------------函数实现-----------------------------------------------------------------//

//默认构造
Teacher::Teacher()
{

}

//有参构造(职工编号、姓名、密码)
Teacher::Teacher(int empId, string name, string pwd)
{
    //初始化属性
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

//菜单界面
void Teacher::operMenu()
{
    cout<<"欢迎教师："<<this->m_Name<<" 登录！"<<endl;
    cout<<"1.查看所有预约"<<endl;
    cout<<"2.审核预约"<<endl;
    cout<<"3.注销登录"<<endl;
    cout<<"请选择您的操作："<<endl;
}

//查看所有预约
void Teacher::showAllOrder()
{
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout<<"无预约记录"<<endl;
        return;
    }
    for(int i=0; i<of.m_Size; i++)
    {
        cout<<i+1<<". ";
        cout<<"预约日期：周"<<of.m_orderData[i]["date"];
        cout<<" 时段："<<(of.m_orderData[i]["interval"]=="1"?"上午":"下午");
        cout<<" 机房："<<of.m_orderData[i]["roomId"];
        string status = " 状态："; //0取消预约 1审核中 2已预约 -1预约失败
        if(of.m_orderData[i]["status"] == "1")
        {
            status +="审核中";
        }
        else if(of.m_orderData[i]["status"] == "2")
        {
            status +="预约成功";
        }
        else if(of.m_orderData[i]["status"] == "-1")
        {
            status +="审核未通过，请重新预约";
        }
        else
        {
            status +="预约已取消";
        }
        cout<<status<<endl;
    }
}

//审核预约
void Teacher::validOrder()
{
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout<<"无预约记录"<<endl;
        return;
    }
    cout<<"待审核的预约记录如下："<<endl;

    vector<int>v;
    int index = 0;
    for(int i=0; i<of.m_Size; i++)
    {
        if(of.m_orderData[i]["status"]=="1" )
            {
                v.push_back(i);
                cout<<++index<<". ";
                cout<<"预约日期：周"<<of.m_orderData[i]["date"];
                cout<<"时段："<<(of.m_orderData[i]["interval"]=="1"?"上午":"下午");
                cout<<"机房："<<of.m_orderData[i]["roomId"];
                string status = "状态："; //0取消预约 1审核中 2已预约 -1预约失败
                if(of.m_orderData[i]["status"] == "1")
                {
                    status +="审核中";
                }
                else if(of.m_orderData[i]["status"] == "2")
                {
                    status +="预约成功";
                }
                cout<<status<<endl;
            }
    }
    cout<<"请输入审核的预约记录，0代表返回"<<endl;
    int select;
    int ret = 0;
    while(true)
    {
        cin>>select;
        if(select>=0 && select <=v.size())
        {
            if(select == 0)
            {
                break;
            }
            else
            {
                cout<<"请输入审核结果"<<endl;
                cout<<"1.通过"<<endl;
                cout<<"2.不通过"<<endl;
                cin>>ret;

                if(ret == 1)
                {
                    of.m_orderData[v[select-1]]["status"] = "2";
                }
                else
                {
                    of.m_orderData[v[select-1]]["status"] = "-1";
                }
                of.updateOrder();
                cout<<"审核完毕！"<<endl;
                break;
            }
        }
        cout<<"输入有误，请重新输入"<<endl;
    }
}
