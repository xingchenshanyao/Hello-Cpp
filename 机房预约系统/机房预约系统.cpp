#include<iostream>
using namespace std;
#include"globalFile.hpp"
#include"identity.hpp"
#include"student.hpp"
#include"teacher.hpp"
#include"manager.hpp"
#include<fstream>
#include<string>

//进入教师的子菜单
void teacherMenu(Identity* &teacher)
{
    while(true)
    {
        //教师菜单
        teacher->operMenu();
        Teacher* tea = (Teacher*) teacher;
        int select = 0;
        cin>>select;
        if(select == 1)
        {
            //查看所有预约
            tea->showAllOrder();
        }
        else if(select == 2)
        {
            //审核预约
            tea->validOrder();
        }
        else
        {
            delete teacher;
            cout<<"注销成功"<<endl;
            return;
        }
    }
}


//进入学生的子菜单
void studentMenu(Identity* &student)
{
    while(true)
    {
        //学生菜单
        student->operMenu();
        Student* stu = (Student*)student;
        int select;
        cin>>select;

        if(select == 1) //申请预约
        {
            stu->applyOrder();
        }
        else if(select == 2) //查看自身预约
        {
            stu->showMyOrder();
        }
        else if(select == 3) //查看所有预约
        {
            stu->showAllOrder();
        }
        else if(select == 4) //取消预约
        {
            stu->cancelOrder();
        }
        else
        {
            delete student;
            cout<<"注销成功"<<endl;
            // system("pause");
            // system("cls");
            return;
        }
    }
}

//进入管理员的子菜单
void managerMenu(Identity* &manager)
{
    //调用管理员子菜单
    manager->operMenu();
    //将父类指针转化为子类指针
    Manager* man = (Manager*)manager;
    int select = 0;
    cin>>select;
    if(select == 1) //添加账号
    {
        man->addPerson();
    }
    else if(select == 2) //查看账号
    {
        man->showPerson();
    }
    else if(select == 3) //查看机房
    {
        man->showComputer();
    }
    else if(select == 4) //清空预约
    {
        man->cleanFile();
    }
    else
    {
        delete manager;
        cout<<"注销成功"<<endl;
        return;
    }

}

//登录功能
void LoginIn(string fileName, int type)
{
    Identity *person = NULL;
    ifstream ifs;
    ifs.open(fileName, ios::in);

    //文件不存在情况
    if(!ifs.is_open())
    {
        cout<<"文件不存在"<<endl;
        ifs.close();
        return;
    }

    int id = 0;
    string name;
    string pwd;

    if(type == 1) //学生登录
    {
        cout<<"请输入你的学号"<<endl;
        cin>>id;
    }
    else if(type == 2) //教师登录
    {
        cout<<"请输入你的职工号"<<endl;
        cin>>id;
    }

    cout<<"请输入用户名"<<endl;
    cin>>name;
    cout<<"请输入密码"<<endl;
    cin>>pwd;

    if(type == 1)
    {
        //学生登录验证
        int fId;
        string fName;
        string fPwd;
        while(ifs>>fId && ifs>>fName && ifs>>fPwd)
        {
            if(id == fId && name == fName && pwd == fPwd)
            {
                cout<<"学生登录验证成功！"<<endl;
                person = new Student(id, name, pwd);
                //进入学生子菜单
                studentMenu(person);
                return;
            }
        }
    }
    else if(type == 2)
    {
        //教师登录验证
        int fId;
        string fName;
        string fPwd;
        while(ifs>>fId && ifs>>fName && ifs>>fPwd)
        {
            if(id == fId && name == fName && pwd == fPwd)
            {
                cout<<"教师登录验证成功！"<<endl;
                person = new Teacher(id, name, pwd);
                //进入教师子菜单
                teacherMenu(person);
                return;
            }
        }
    }
    else if(type == 3)
    {
        //管理员验证
        string fName;
        string fPwd;
        while(ifs>>fName && ifs>>fPwd)
        {
            if(name == fName && pwd == fPwd)
            {
                cout<<"管理员登录验证成功！"<<endl;
                person = new Manager(name, pwd);
                //进入管理员子菜单
                managerMenu(person);
                return;
            }
        }
    }

    cout<<"验证登录失败！"<<endl;

    return;

}

int main()
{
    int select = 0;
    while(true)
    {
    cout<<"==================== 欢迎使用机房预约系统 ===================="<<endl;
    cout<<endl<<"请输入您的身份"<<endl;
    cout<<"\t\t ------------------------------\n";
    cout<<"\t\t|                              |\n";
    cout<<"\t\t|         1.学生代表           |\n";
    cout<<"\t\t|                              |\n";
    cout<<"\t\t|         2.老师               |\n";
    cout<<"\t\t|                              |\n";
    cout<<"\t\t|         3.管理员             |\n";
    cout<<"\t\t|                              |\n";
    cout<<"\t\t|         0.退出               |\n";
    cout<<"\t\t|                              |\n";
    cout<<"\t\t ------------------------------\n";
    cout<<"请输入您的选择：";
    cin>>select;
    switch(select)
    {
        case 1://学生身份
            LoginIn(STUDENT_FILE, select);
            break;
        case 2://老师身份
            LoginIn(TEACHER_FILE, select);
            break;
        case 3://管理员身份
            LoginIn(ADMIN_FILE, select);
            break;
        case 0://退出系统
            cout<<"欢迎下次使用！"<<endl;
            // system("pause");
            return 0;
            break;
        default:
            cout<<"输入有误，请重新选择！"<<endl;
            break;
    }
    
    }
    


    
    cout<<"----------------------------------------------------------------------"<<endl;
    return 0;
}