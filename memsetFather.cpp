#include <iostream>
using namespace std;

// 使用memest 把父类的vtr给清除了，没有了

// 父类先构造，内存结构如下：
//      vtpr, Class A data    // 注意这里的vtpr是指向Class A的虚表

//    - 然后你把指向上述地址的内存给清零了

//    - 然后是子类构造, 会有如下几步：
//        > 更新vtpr,指向Class B的虚表   // vtpr有新值啦
//        > 初始化Class B的数据
//        > 最后内存结构如: vtpr of Class B, Class A data, Class B data

// 这样就不难理解楼主的问题了

// 1.  a.func();       //1 func.A
//     b.func();    //2 func.B
//    不涉及多态,没访问虚表

// 2. pa->func();    //3 异常
//    因为vtpr被清零,访问虚表出错;

// 2.  pab->func();    //4 func.B
//     pb->func();    //5 func.B
//    因为是ClassB的object, 在构造中,最终的vtpr是指向Class B的虚表, 其vtpr是有效的值


class ClassA
{
public:
    ClassA()
    {       
        cout<<"A: "<<this<<endl;
        Clear();
    }
 
    void Clear()
    { 
        memset(this,0,sizeof(*this));
    }
 
    ~ClassA()
    {
    }
    virtual void func()
    {
         cout<<"func.A "<<endl;
    }
};
 
class ClassB:public ClassA
{
public:
    ClassB()
    {         
        cout<<"B: "<<this<<endl;
    }
    void func()
    {
        cout<<"func.B "<<endl;
    }
 
};
 
int main()
{      
       
    ClassA a;
    ClassB b;
 
    ClassA *pa = &a;
    ClassA *pab = &b;
    ClassB* pb = &b;
 
    a.func();       //1 func.A
    b.func();    //2 func.B
    //pa->func();    //3 异常
    pab->func();    //4 func.B
    pb->func();    //5 func.B
 return 1;
} 