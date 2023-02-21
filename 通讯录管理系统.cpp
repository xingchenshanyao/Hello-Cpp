#include<iostream>
using namespace std;
#include <string>
#include<ctime>
#include <unistd.h>
#define MAX 1000

//设计联系人结构体
struct Person
{
    string m_Name;
    int m_Sex;// 1 男 2女
    int m_Age;
    string m_Phone;
    string m_Addr;
};

//设计通讯录结构体
struct Addressbooks
{
    struct Person personArray[MAX];//通讯录中保存的联系人数组
    int m_Size;//通讯录中目前保存联系人的个数
};

//菜单界面
void showMenu()
{
    cout<<"****************************"<<endl;
    cout<<"*****   1.添加联系人   *****"<<endl;
    cout<<"*****   2.显示联系人   *****"<<endl;
    cout<<"*****   3.删除联系人   *****"<<endl;
    cout<<"*****   4.查找联系人   *****"<<endl;
    cout<<"*****   5.修改联系人   *****"<<endl;
    cout<<"*****   6.清空联系人   *****"<<endl;
    cout<<"*****   0.退出通讯录   *****"<<endl;
    cout<<"****************************"<<endl;
}

//添加联系人
void addPerson(Addressbooks *abs)
{
    //判断通讯录是否已满
    if(abs->m_Size == MAX)
    {
        cout<<"联系人已满"<<endl;
        return;
    }
    else
    {
        string name;
        cout<<"请输入姓名:"<<endl;
        cin>>name;
        abs->personArray[abs->m_Size].m_Name=name;
        int sex=0;
        cout<<"请输入性别:"<<endl;
        cout<<"1 --- 男"<<endl;
        cout<<"2 --- 女"<<endl;
        while(true)
        {
            cin>>sex;
            if(sex==1||sex==2)
        {
            abs->personArray[abs->m_Size].m_Sex = sex;
            break;
        }
        else
        {
            cout<<"输入有误，请重新输入"<<endl;
        }
        }
        cout<<"请输入年龄"<<endl;
        int age=0;
        while(true)
        {
            cin>>age;
            if(age>0&&age<150)
        {
            abs->personArray[abs->m_Size].m_Age = age;
            break;
        }
        else
        {
            cout<<"输入有误，请重新输入"<<endl;
        }
        }
        cout<<"请输入联系电话"<<endl;
        string phone;
        cin>>phone;
        abs->personArray[abs->m_Size].m_Phone = phone;
        cout<<"请输入家庭地址"<<endl;
        string address;
        cin>>address;
        abs->personArray[abs->m_Size].m_Addr = address;
        //更新通讯录人数
        abs->m_Size++;
        cout<<"添加成功"<<endl;

        //system("pause");
        //system("cls");//清屏操作 windows才能用
    }

}

//显示联系人
void showPerson(Addressbooks *abs)
{
    //判断通讯录是否为空
    if(abs->m_Size==0)
    {
        cout<<"当前记录为空"<<endl;
    }
    else
    {
        for(int i=0; i<abs->m_Size; i++)
        {
            cout<<"序号:"<<i+1<<"\t";
            cout<<"姓名:"<<abs->personArray[i].m_Name<<"\t";
            cout<<"性别:"<<(abs->personArray[i].m_Sex == 1?"男":"女")<<"\t";
            cout<<"年龄:"<<abs->personArray[i].m_Age<<"\t";
            cout<<"电话:"<<abs->personArray[i].m_Phone<<"\t";
            cout<<"住址:"<<abs->personArray[i].m_Addr<<endl;
        }
        cout<<"总计:"<<" "<<abs->m_Size<<" "<<"人"<<endl;
    }
}

//删除联系人前，检测联系人是否存在
int isExist(Addressbooks *abs, string name)
{
    for(int i=0; i<abs->m_Size; i++)
    {
        if(abs->personArray[i].m_Name == name)
        {
            return i;
        }
    }
    return -1;
}
//删除联系人
void deletePerson(Addressbooks *abs)
{
    cout<<"请输入您要删除的联系人"<<endl;
    string name;
    cin>>name;
    int ret = isExist(abs,name);
    if(ret != -1)
    {
        for(int i=ret;i<abs->m_Size;i++)
        {
            //数据前移
            abs->personArray[i]=abs->personArray[i+1];
        }
        abs->m_Size--;
        cout<<"删除成功"<<endl;

    }
    else
    {
        cout<<"查无此人"<<endl;
    }
}

//查找联系人
void findPerson(Addressbooks *abs)
{
    cout<<"请输入您要查找的联系人"<<endl;
    string name;
    cin>>name;
    int ret = isExist(abs,name);
    if(ret != -1)
    {
        int i=ret;
        cout<<"姓名:"<<abs->personArray[i].m_Name<<"\t";
        cout<<"性别:"<<(abs->personArray[i].m_Sex == 1?"男":"女")<<"\t";
        cout<<"年龄:"<<abs->personArray[i].m_Age<<"\t";
        cout<<"电话:"<<abs->personArray[i].m_Phone<<"\t";
        cout<<"住址:"<<abs->personArray[i].m_Addr<<endl;
        cout<<"查找成功"<<endl;
    }
    else
    {
        cout<<"查无此人"<<endl;
    }
}

//修改联系人
void modifPerson(Addressbooks *abs)
{
    cout<<"请输入您要修改的联系人"<<endl;
    string name;
    cin>>name;
    int ret = isExist(abs,name);
    if(ret != -1)
    {
        int sex=0;
        cout<<"请输入性别:"<<endl;
        cout<<"1 --- 男"<<endl;
        cout<<"2 --- 女"<<endl;
        while(true)
        {
            cin>>sex;
            if(sex==1||sex==2)
        {
            abs->personArray[ret].m_Sex = sex;
            break;
        }
        else
        {
            cout<<"输入有误，请重新输入"<<endl;
        }
        }
        cout<<"请输入年龄"<<endl;
        int age=0;
        while(true)
        {
            cin>>age;
            if(age>0&&age<150)
        {
            abs->personArray[ret].m_Age = age;
            break;
        }
        else
        {
            cout<<"输入有误，请重新输入"<<endl;
        }
        }
        cout<<"请输入联系电话"<<endl;
        string phone;
        cin>>phone;
        abs->personArray[ret].m_Phone = phone;
        cout<<"请输入家庭地址"<<endl;
        string address;
        cin>>address;
        abs->personArray[ret].m_Addr = address;
        cout<<"修改成功"<<endl;
    }
    else
    {
        cout<<"查无此人"<<endl;
    }
}

//清空联系人
void cleanPerson(Addressbooks *abs)
{
    cout<<"请确认是否清空"<<endl;
    cout<<"1 --- 清空"<<endl;
    cout<<"0 --- 取消"<<endl;
    int i;
    cin>>i;
    if(i)
    {
    abs->m_Size=0;
    cout<<"通讯录已清空"<<endl;
    }
    else
    {
        cout<<"已取消清空"<<endl;
    }
    
}

int main()
{
    Addressbooks abs;
    abs.m_Size=0;

    int select = 0;
    while(true)
    {
        showMenu();
        cin>>select;
        switch(select)
        {
            case 1:
                            addPerson(&abs);//利用地址传递修饰实参
                            break;//1.添加联系人
            case 2:
                            showPerson(&abs);
                            break;//2.显示联系人
            case 3:
                            deletePerson(&abs);
                            break;//3.删除联系人
            case 4:
                            findPerson(&abs);
                            break;//4.查找联系人
            case 5:
                            modifPerson(&abs);
                            break;//5.修改联系人
            case 6:
                            cleanPerson(&abs);
                            break;//6.清空联系人
            case 0:
                            cout<<"欢迎下次使用"<<endl;
                            system("pause");
                            return 0;
                            break;//0.退出通讯录

        }

    }
    pause();//按任意键继续
    return 0;//退出函数
}