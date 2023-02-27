#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"speaker.hpp"
#include<string>
#include<algorithm>
#include"deque"
#include<functional>
#include<numeric>
#include<fstream>

//设计演讲管理类

class SpeechManger
{
public:
    //构造函数
    SpeechManger();

    //菜单功能
    void show_Menu();

    //退出系统
    void exitSystem();

    //初始化容器和属性
    void initSpeech();

    //创建12名参赛选手
    void createSpeaker();

    //开始比赛 比赛流程控制函数
    void startSpeech();

    //抽签
    void speechDraw();

    //比赛
    void speechContest();

    //显示得分
    void showScore();

    //保存记录
    void saveRecord();

    //读取记录
    void loadRecord();

    //显示往届得分
    void showRecord();

    //清空记录
    void clearRecord();

    //析构函数
    ~SpeechManger();


    //成员属性
    //保存第一轮比赛选手编号容器
    vector<int>v1;
    
    //第一轮晋级选手编号容器
    vector<int>v2;

    //胜出前三名选手编号容器
    vector<int>vVictory;

    //存放编号以及对应的选手容器
    map<int, Speaker>m_Speaker;

    //存放比赛轮数
    int m_Index;

    //判断文件是否为空
    bool fileIsEmpty;

    //存放往届记录的容器
    map<int, vector<string>>m_Record;
};

//-------------------------------------函数实现--------------------------------------------//

//构造函数
SpeechManger::SpeechManger()
{
    //初始化容器和属性
    this->initSpeech();

    //创建12名参赛选手
    this->createSpeaker();

    //加载往届记录
    this->loadRecord();
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
    cout<<"按任意键退出系统"<<endl;
    // pause();
    exit(0);
}

//初始化容器和属性
void SpeechManger::initSpeech()
{
    //容器都置空
    this->v1.clear();
    this->v2.clear();
    this->vVictory.clear();
    this->m_Speaker.clear();
    this->m_Record.clear();

    //初始化比赛轮数
    this->m_Index = 1;
}

//创建12名参赛选手
void SpeechManger::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";
    for(int i=0; i<nameSeed.size(); i++)
    {
        string name = "选手";
        name += nameSeed[i];
        //创建具体选手
        Speaker sp;
        sp.m_Name = name;
        for(int j=0; j<2; j++)
        {
            sp.m_Score[j] = 0;
        }
        //创建选手编号，并且放入容器v1中
        this->v1.push_back(i+10001);
        //选手编号及对应选手 放入到map容器中
        this->m_Speaker.insert(make_pair(i+10001, sp));
    }
}

//开始比赛 比赛流程控制函数
void SpeechManger::startSpeech()
{
    //第一轮开始
    //1.抽签
    this->speechDraw();
    //2.比赛
    this->speechContest();
    //3.显示晋级结果
    this->showScore();
    //第二轮比赛
    this->m_Index++;
    //1.抽签
    this->speechDraw();
    //2.比赛
    this->speechContest();
    //3.显示最终结果
    this->showScore();
    //4.保存分数
    this->saveRecord();

    //重置比赛，获取记录
    //初始化容器和属性
    this->initSpeech();
    //创建12名参赛选手
    this->createSpeaker();
    //加载往届记录
    this->loadRecord();

    cout<<"本届比赛完毕！"<<endl;
}

//抽签
void SpeechManger::speechDraw()
{
    cout<<"第<<"<<this->m_Index<<">>轮比赛选手正在抽签"<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"抽签后演讲顺序如下："<<endl;
    if(this->m_Index == 1)
    {
        //第一轮比赛
        random_shuffle(v1.begin(),v1.end());
        for(vector<int>::iterator it=v1.begin(); it!=v1.end(); it++)
        {
            cout<<*it<<" ";
        }
        cout<<endl;
    }
    else
    {
        //第二轮比赛
        random_shuffle(v2.begin(),v2.end());
        for(vector<int>::iterator it=v2.begin(); it!=v2.end(); it++)
        {
            cout<<*it<<" ";
        }
        cout<<endl;
    }
    cout<<"----------------------------------"<<endl;
    cout<<endl;
}

//比赛
void SpeechManger::speechContest()
{
    cout<<"--------------------第<<"<<this->m_Index<<">>轮比赛开始--------------------"<<endl;
    //准备临时容器 存放小组成绩
    multimap<double,int,greater<double>> groupScore;
    int num = 0; //记录人员个数 6人一组


    vector<int>v_Src; //比赛选手容器
    if(this->m_Index == 1)
    {
        v_Src = v1;
    }
    else
    {
        v_Src = v2;
    }

    //遍历所有的选手进行比赛
    for(vector<int>::iterator it = v_Src.begin(); it!=v_Src.end(); it++)
    {
        num ++;
        //评委打分
        deque<double>d;
        for(int i=0; i<10; i++)
        {
            double score = (rand()%401 + 600)/10.f; //60~100的小数
            // cout<<score<<" ";
            d.push_back(score);
        }
        // cout<<endl;
        sort(d.begin(), d.end(), greater<double>()); //排序 降序
        d.pop_front();
        d.pop_back();
        double sum = accumulate(d.begin(), d.end(), 0.0f); //总分
        double avg = sum/(double)d.size(); //平均分
        //打印平均分
        // cout<<"编号："<<*it<<" 姓名："<<this->m_Speaker[*it].m_Name<<" 获取平均分："<<avg<<endl;
        //把平均分放入map中
        this->m_Speaker[*it].m_Score[this->m_Index-1] = avg;

        //将打分数据 放入到小组成绩
        groupScore.insert(make_pair(avg, *it)); //key是得分，value是具体选手编号
        //每六人取出前三名
        if(num % 6 == 0)
        {
            cout<<"第<"<<num/6<<">组小组比赛每次："<<endl;
            for(multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it!= groupScore.end(); it++)
            {
                cout<<"编号："<<it->second<<" 姓名："<<this->m_Speaker[it->second].m_Name
                         <<" 成绩"<<this->m_Speaker[it->second].m_Score[this->m_Index-1]<<endl;
            }

            //取走前3名
            int count=0;
            for(multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it!= groupScore.end()&&count<3; it++,count++)
            {
                if(this->m_Index ==1)
                {
                    v2.push_back((*it).second);
                }
                else
                {
                    vVictory.push_back((*it).second);
                }
            }
            cout<<endl;
            groupScore.clear(); //小组容器清空
        }
    }
    cout<<"--------------------第<<"<<this->m_Index<<">>轮比赛完毕--------------------"<<endl;
}

//显示比赛结果
void SpeechManger::showScore()
{
    cout<<"-------------------第<<"<<this->m_Index<<">>轮晋级选手信息如下--------------------"<<endl;
    vector<int>v;
    if(this->m_Index == 1)
    {
        v = v2;
    }
    else
    {
        v = vVictory;
    }
    for(vector<int>::iterator it=v.begin(); it!=v.end(); it++)
    {
        cout<<"选手编号："<<*it<<" 姓名："<<this->m_Speaker[*it].m_Name<<" 得分："
                 <<this->m_Speaker[*it].m_Score[this->m_Index-1]<<endl;
    }
    cout<<endl;
    // pause();
    // system("cls");
    // this->show_Menu();
}

//保存记录
void SpeechManger::saveRecord()
{
    ofstream ofs;
    ofs.open("learn c++/3_演讲比赛流程管理系统/speech.csv", ios::out|ios::app); //用追加的方式写文件
    //将每个人的数据写入文件
    for(vector<int>::iterator it = vVictory.begin(); it!=vVictory.end(); it++)
    {
        ofs<<*it<<","<<this->m_Speaker[*it].m_Score[1]<<",";
    }
    ofs<<endl;

    //关闭
    ofs.close();
    this->vVictory.clear();
    this->v2.clear();
    this->m_Index = 1;

    cout<<"记录已经保存"<<endl;
    //更改文件不为空状态
    this->fileIsEmpty = false;
}

//读取记录
void SpeechManger::loadRecord()
{
    ifstream ifs("learn c++/3_演讲比赛流程管理系统/speech.csv", ios::in); //读文件
    if(!ifs.is_open())
    {
        this->fileIsEmpty = true;
        cout<<"文件不存在"<<endl;
        ifs.close();
        return;
    }
    //文件清空情况
    char ch;
    ifs>>ch;
    if(ifs.eof())
    {
        cout<<"文件为空"<<endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件不为空
    this->fileIsEmpty = false;
    ifs.putback(ch); //将上面读取的单个字符 放回来
    string data;
    int index = 0;
    while(ifs>>data)
    {
        // cout<<data<<endl;
        vector<string>v;
        int pos = -1; //查到逗号位置的变量
        int start = 0;
        while(true)
        {
            pos = data.find(",",start);
            if(pos == -1)
            {
                //没有找到
                break;
            }
            string temp = data.substr(start, pos-start);
            // cout<<temp<<endl;
            v.push_back(temp);
            start = pos+1;
        }
        this->m_Record.insert(make_pair(index,v));
        index++;
    }
    ifs.close();
    // for(map<int,vector<string>>::iterator it=m_Record.begin(); it!=m_Record.end(); it++)
    // {
    //     cout<<"第"<<it->first+1<<"届 冠军编号："<<it->second[0]<<" 分数："<<it->second[1]<<endl;
    // }
}

//显示往届得分
void SpeechManger::showRecord()
{
    for(int i=0; i<this->m_Record.size(); i++)
    {
        cout<<"第"<<i+1<<"届 "<<
                      "冠军编号："<<this->m_Record[i][0]<<" 得分："<<this->m_Record[i][1]<<" "
                      "亚军编号："<<this->m_Record[i][2]<<" 得分："<<this->m_Record[i][3]<<" "
                      "季军编号："<<this->m_Record[i][4]<<" 得分："<<this->m_Record[i][5]<<endl;
    }
    // system("pause");
    // system("cls");
}

//清空记录
void SpeechManger::clearRecord()
{
    cout<<"确认清空？"<<endl;
    cout<<"1.确认"<<endl;
    cout<<"2.取消"<<endl;
    int select = 0;
    cin>>select;
    if(select == 1)
    {
        ofstream ofs("learn c++/3_演讲比赛流程管理系统/speech.csv", ios::trunc);
        ofs.close();

        //初始化属性
        this->initSpeech();

        //创建选手
        this->createSpeaker();

        //获取往届记录
        this->loadRecord();

        cout<<"清空成功！"<<endl;
    }
}

//析构函数
SpeechManger::~SpeechManger()
{

}