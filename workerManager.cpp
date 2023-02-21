#include "workerManager.h"


//构造函数
WorkerManager::WorkerManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); //读文件
    //1.文件不存在
    if(!ifs.is_open())
    {
        // cout<<"文件不存在"<<endl;
        //初始化属性
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    
    //2.文件存在 数据为空
    char ch;
    ifs>>ch;
    if(ifs.eof())
    {
        //文件为空
        // cout<<"文件为空"<<endl;
        //初始化属性
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //3.文件存在 并且记录数据
    int num = this->get_EmpNum();
    // cout<<"职工的人数为："<<num<<endl;
    this->m_EmpNum = num;
    //开辟数组空间
    this->m_EmpArray = new Worker *[this->m_EmpNum];
    //将文件中的数据，存放到数组中
    this->init_Emp();

    //测试文件中的数据是否全部读取
    // for(int i = 0; i<this->m_EmpNum; i++)
    // {
    //     cout<<"职工编号:"<<this->m_EmpArray[i]->m_Id<<" "
    //           <<"职工姓名:"<<this->m_EmpArray[i]->m_Name<<" "
    //           <<"部门编号:"<<this->m_EmpArray[i]->m_DeptId<<endl;
    // }
}
//展示菜单
void WorkerManager::Show_Menu()
{
    cout<<"*********************************************"<<endl;
    cout<<"**********   欢迎使用职工管理系统   **********"<<endl;
    cout<<"*************   0.退出管理程序   **************"<<endl;
    cout<<"*************   1.增加职工信息   **************"<<endl;
    cout<<"*************   2.显示职工信息   **************"<<endl;
    cout<<"*************   3.删除离职职工   **************"<<endl;
    cout<<"*************   4.修改职工信息   **************"<<endl;
    cout<<"*************   5.查找职工信息   **************"<<endl;
    cout<<"*************   6.按照编号排序   **************"<<endl;
    cout<<"*************   7.清空所有文档   **************"<<endl;
    cout<<"*********************************************"<<endl;
    cout<<endl;
    
}


//退出系统
void WorkerManager::ExitSystem()
{
    cout<<"欢迎下次使用"<<endl;
    // system("pause") 
    // exit(0); //退出程序
}

//添加职工
void WorkerManager::Add_Emp()
{
    cout<<"请输入添加职工的数量"<<endl;
    int addNum = 0;
    cin>>addNum;
    if(addNum>0)
    {
        //添加
        //计算添加新空间的大小
        int newSize = this->m_EmpNum + addNum; //新空间的大小=原来+新增
        //开辟新空间
        Worker ** newSpace = new Worker*[newSize];
        //将原来空间下的数据拷贝过来
        if(this->m_EmpNum != NULL)
        {
            for(int i=; i<this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //添加新数据
        for(int i=0; i<addNum; i++)
        {
            int id; //职工编号
            string name; //职工姓名
            int dSelect; //部门选择
            cout<<"请输入第"<<i+1<<"个新职工的编号："<<endl;
            cin>>id;
            cout<<"请输入第"<<i+1<<"个新职工的姓名："<<endl;
            cin>>name;
            cout<<"请输入第"<<i+1<<"个新职工的岗位："<<endl;
            cout<<"1-普通职工"<<endl;
            cout<<"2-经理"<<endl;
            cout<<"3-老板"<<endl;
            cin>>dSelect;

            Worker * worker = NULL;
            switch(dSelect)
            {
                case 1:
                    worker = new Employee(id,name, 1);
                    break;
                case 2:
                    worker = new Manager(id,name, 2);
                    break;
                case 3:
                    worker = new Boss(id,name, 3);
                    break;
                default:
                    break;
            }
            //将创建的职工指针保存到数组中
            newSpace[this->m_EmpNum + i] = worker;
        }
        //释放原有的空间
        delete []this->m_EmpArray;
        //更改新空间的指向
        this->m_EmpArray = newSpace;
        //更新新的职工人数
        this->m_EmpNum = newSize;
        //更新职工不为空
        this->m_FileIsEmpty = false;

        //成功添加后，保存到文件中，避免关闭程序时清空
        save();
        //提示添加成功
        cout<<"成功添加"<<addNum<<"名新职工!"<<endl;

        //按任意键后清屏(只适用于windows)
        // system("pause");
        // system("cls");
    }
    else
    {
        cout<<"输入有误"<<endl;
    }
}

//保存文件
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); //用输出的方式打开--写文件
    //把每个人的数据写入文件中
    for(int i; i<<this->m_EmpNum; i++)
    {
        ofs<<this->m_EmpArray[i]->m_Id<<" "
              <<this->m_EmpArray[i]->m_Name<<" "
              <<this->m_EmpArray[i]->m_DeptId<<endl;
    }

    //关闭文件
    ofs.close();
}

//统计文件中的人数
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); //打开文件 -- 读文件
    int id;
    string name;
    int dId;
    
    //统计人数变量
    int num = 0;
    while(ifs>>id && ifs>>name && ifs>>dId)
    {
        num++;
    }
    return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int index = 0;
    while(ifs>>id && ifs>>name && ifs>>dId)
    {
        Worker * worker = NULL;
        if(dId == 1)//普通职工
        {
            worker = new Employee(id, name, dId);
        }
        else if(dId == 2) //经理
        {
            worker = new Manager(id, name, dId);
        }
        else //老板
        {
            worker = new Boss(id, name, dId);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    ifs.close();
}

//显示职工
void WorkerManager::Show_Emp()
{
    //判断文件是否为空
    if(this->m_FileIsEmpty)
    {
        cout<<"文件不存在或者为空"<<endl;
    }
    else
    {
        for(int i = 0; i<m_EmpNum; i++)
        {
            //利用多态调用程序接口
            this->m_EmpArray[i]->showInfo();
        }
    }

    //按任意键清屏
    // system("pause");
    // system("cls");
}

//判断员工是否存在
int WorkerManager::IsExist(int id)
{
    int index = -1;
    for(int i = 0; i<this->m_EmpNum; i++)
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            index = i;//找到职工
            break;
        }
    }
    return index;
}

//删除职工
void WorkerManager::Del_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout<<"文件不存在或文件为空！"<<endl;
    }
    else
    {
        //按编号删除
        cout<<"请输入删除职工的编号："<<endl;
        int id = 0;
        cin>>id;
        int index = this->IsExist(id);
        if(index != -1) //职工存在
        {
            //数组前移
            for(int i = index; i<this->m_EmpNum-1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i+1];
            }
            //更新数组中记录的人员个数
            this->m_EmpNum--;
            //同步更新到文件中
            this->save();

            cout<<"删除成功！"<<endl;
        }
        else
        {
            cout<<"职工不存在！"<<endl;
        }
        //按任意键清屏
        // system("pause");
        // system("cls");
    }
}

//修改职工
void WorkerManager::Mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout<<"文件不存在或文件为空！"<<endl;
    }
    else
    {
        cout<<"请输入修改的职工编号："<<endl;
        int id;
        cin>>id;
        int ret = this->IsExist(id);
        if(ret != -1)
        {
            //查找到职工编号
            delete this->m_EmpArray[ret];

            int newId = 0;
            string newName = " ";
            int newDId = 0;

            cout<<"查找："<<id<<"号职工，请输入新的职工编号："<<endl;
            cin>>newId;
            cout<<"请输入新姓名："<<endl;
            cin>>newName;
            cout<<"请输入新岗位："<<endl;
            cout<<"1. 普通职工"<<endl;
            cout<<"2. 经理"<<endl;
            cout<<"3. 老板"<<endl;
            cin>>newDId;
            Worker * worker = NULL;
            switch (newDId)
            {
            case 1:
                worker = new Employee(newId, newName, newDId)
                break;
            case 2:
                worker = new Manager(newId, newName, newDId)
                break;
            case 3:
                worker = new Boss(newId, newName, newDId)
                break;
            default:
                break;
            }
            //更新数据到数组中
            this->m_EmpArray[ret] = worker;
            cout<<"修改成功！"<<endl;

            //保存到文件中
            this->save();
        }
        else
        {
            cout<<"修改失败，查无此人！"<<endl;
        }
        //按任意键清屏
        // system("pause");
        // system("cls");
    }
}

//查找职工
void WorkerManager::Find_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout<<"文件不存在或文件为空！"<<endl;
    }
    else
    {
        cout<<"请输入查找方式："<<endl;
        cout<<"1.按照职工编号查找"<<endl;
        cout<<"2.按照职工姓名查找"<<endl;
        int select = 0;
        cin>>select;
        if(select == 1)
        {
            //按照职工编号查找
            int id;
            cout<<"请输入查找的职工编号："<<endl;
            cin>>id;
            int ret = IsExist(id);
            if(ret != -1)
            {
                //找到职工
                cout<<"查找成功！该职工信息如下："<<endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout<<"查找失败！"<<endl;
            }
        }
        else if(select == 2)
        {
            //按照职工姓名查找
            string name;
            cout<<"请输入查找职工的姓名："<<endl;
            cin>>name;
            //判断是否查到的标志
            bool flag = false;
            for(int i = 0; i<m_EmpNum; i++)
            {
                if(this->m_EmpArray[i]->m_Name == name)
                {
                    cout<<"查找成功！"<<endl;
                    this->m_EmpArray[i]->showInfo();
                    flag = true;
                }
            }
            if(!flag)
            {
                cout<<"查找失败！"<<endl;
            }
        }
        else
        {
            cout<<"输入错误"<<endl;
        }
    }
    //按任意键清屏
    // system("pause");
    // system("cls");
}

//排序职工
void WorkerManager::Sort_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout<<"文件不存在或文件为空！"<<endl;
    }
    else
    {
        cout<<"请选择排序方式："<<endl;
        cout<<"1.按职工编号进行升序"<<endl;
        cout<<"2.按职工编号进行降序"<<endl;

        int selet = 0;
        cin>>select;

        for(int i=0; i<m_EmpNum; i++)
        {
            int minOrMax = i; // 声明最小值或者最大值下标
            for(int j = i+1; j<this->m_EmpNum; j++)
            {
                if(select == 1)//升序
                {
                    if(this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                else//降序
                {
                    if(this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                //判断一开始认定的最大/最小值 是否是真是的最大/最小值
                //如果不是 交换二者
                if(i != minOrMax)
                {
                    Worker * temp = this->m_EmpArray[i];
                    this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
                    this->m_EmpArray[minOrMax] = temp;
                }
            }
        }
        cout<<"排序成功！排序结果为："<<endl;
        this->Show_Emp(); //展示所有职工
        this->save();//保存结果
    }
}

//清空文件
void WorkerManager::Clean_File()
{
    cout<<"确认清空？"<<endl;
    cout<<"1.确认"<<endl;
    cout<<"2.取消"<<endl;
    int select;
    cin>>select;
    if(select == 1)
    {
        //清空文件
        ofstream ofs(FILENAME, ios::trunc); //删除文件后重新创建
        ofs.close();

        if(this->m_EmpArray != NULL)
        {
            for(int i=0; i<this->m_EmpNum; i++)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
            //删除堆区数组指针
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        cout<<"清空完毕！"<<endl;
    }

    //按任意键清屏
    // system("pause");
    // system("cls");
}

//析构函数
WorkerManager::~WorkerManager()
{
    if(this->m_EmpArray != NULL)
    {
        delete []this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}