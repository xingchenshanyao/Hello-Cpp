#include"speechManager.h"

//构造函数
SpeechManger::SpeechManger()
{

}

//菜单功能
void SpeechManger::show_Menu()
{
    cout<<"****************************"<<endl;
    cout<<"***** 欢迎参加演讲比赛 *****"<<endl;
    cout<<"****** 1.开始演讲比赛 ******"<<endl;
    cout<<"****** 2.查看往届记录 ******"<<endl;
    cout<<"****** 3.清空比赛记录 ******"<<endl;
    cout<<"****** 0.退出比赛程序 ******"<<endl;
    cout<<"****************************"<<endl;
    cout<<endl;
}

//退出系统
void SpeechManger::exitSystem()
{
    cout<<"欢迎下次使用"<<endl;
    // pause();
    // exit(0);
}

//析构函数
SpeechManger::~SpeechManger()
{

}