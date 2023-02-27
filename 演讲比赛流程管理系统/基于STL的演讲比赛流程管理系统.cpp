#include<iostream>
using namespace std;
#include"speechManager.hpp"
#include<string>
#include<ctime>

//测试函数

//测试12名选手创建
void test01(SpeechManger &sm);

int main()
{
    //添加随机数种子
    srand((unsigned int)time(NULL));

    //创建管理类对象
    SpeechManger sm;

    // test01(sm);

    int choice = 0; //用于存储用户输入
    while(true)
    {
        sm.show_Menu();
        cout<<"请输入您的选择："<<endl;
        cin>>choice;
        switch(choice)
        {
            case 1: //开始比赛
                sm.startSpeech();
                break;
            case 2: //查看往届比赛记录
                sm.showRecord();
                break;
            case 3: //清空比赛记录
                sm.clearRecord();
                break;
            case 0: //退出比赛系统
                sm.exitSystem();
                break;
            default: //清屏
                // system("cls");
                break;
        }

    }






    cout<<"----------------------------------------------------------------------"<<endl;
    //pause();
    return 0;
}

void test01(SpeechManger &sm)
{
    for(map<int, Speaker>::iterator it=sm.m_Speaker.begin(); it!=sm.m_Speaker.end();it++)
    {
        cout<<it->first<<" "<<it->second.m_Name<<" "<<it->second.m_Score[0]<<endl;
    }
}