//
// Created by Administrator on 2017/11/22.
//

#ifndef INDEXHEAP_INDEXHEAP_H
#define INDEXHEAP_INDEXHEAP_H

#include <cassert>
#include <iostream>
using namespace std;

class indexheap {
private:
    int* data;//数据存储数组
    int *index;//索引存储数组
    int Count;//记录堆中存放的数据的数量，每次都保证指向最后一个索引所在的位置
    int capacity;//记录数组最大能够承载元素的数量,也是索引最大承受数量
    int *rev;//rev为记录i索引所在数组的位置，与index数组恰好相反

    void shiftup(int k)//k代表索引所处的位置
    {
        int e;//交换操作备用
        e=index[k];
        while (k > 1 && data[index[k / 2]] < data[index[k]]) {//如果k>1并且K的父节点的值要小于k节点的值
            //swap(index[k], index[k / 2]);//交换
            //优化交换操作，提高效率，替换代码如下：具体可参考插入排序的优化方法
            index[k]=index[k/2];
            rev[index[k]]=k;
            k /= 2;//k重新指向其原来父节点所在索引
        }
        index[k]=e;
        rev[index[k]]=k;
    }

    void shiftdown(int k){
        int e;//交换操作备用
        e=index[k];
        while(k*2<=Count){//K所处节点下沉条件成立，存在左孩子
            int j=k*2;//j指向孩子中的最大者,默认为其左孩子
            if(j+1<=Count&&data[index[j+1]]>data[index[j]]){//不仅存在右孩子，而且右孩子的值比左孩子还要大，则j指向右孩子
                j++;
            }
            if(data[index[j]]>data[index[k]]){//如果父节点的值小于大孩子节点的值则进行交换
              //  swap(index[j],index[k]);优化替换操作提高效率
                index[k]=index[j];
                rev[index[k]]=k;
            }
            else break;//父节点相比较大则不用交换直接退出下沉循环操作
            k=j;
        }
        index[k]=e;
        rev[e]=k;
    }

public:
    indexheap(int n)//索引堆构造函数
    {
        data=new int[n+1];
        index=new int[n+1];
        rev=new int[n+1];
        Count=0;
        capacity=n;
        for(int i=0;i<n+1;i++){//初始化rev数组
            rev[i]=0;//若rev为0则代表不存在此元素，因为堆从1开始计数
        }
    }

    ~indexheap()
    {
        delete [] data;
        delete [] index;
        delete[] rev;
    }

    void insert(int i,int item){//i为索引，元素值为item,对用户而言从0开始
        i+=1;//修正用户从0开始计数与堆从1开始计数引起的偏差
        assert(i<=capacity);
        assert(Count+1<=capacity&&i>=1);
        data[i]=item;//插入数据
        index[Count+1]=i;//插入索引
        rev[i]=Count+1;
        Count++;//更新Count指向，使其指向最后一个数据的索引
        shiftup(Count);//对其新添加的元素更新索引位置
    }

    int getmax(){//获取最大值
        assert(Count>0);
        return data[index[1]];
    }

    int getitem(int i)//i相对于用户从0开始
    {
        assert(IsInHeap(i));
        i+=1;//偏移为内部索引
        return data[i];
    }

    void test()//测试函数，打印出Index和data
    {
        cout<<"index:"<<endl;
        for(int i=1;i<=Count;i++)
        {
            cout<<index[i]<<' ';
        }
        cout<<endl;
        cout<<"data:"<<endl;
        for(int i=1;i<=Count;i++)
        {
            cout<<data[i]<<' ';
        }
        cout<<endl;
        cout<<"rev:"<<endl;
        for(int i=1;i<=capacity;i++){
            cout<<rev[i]<<' ';
        }
        cout<<endl;
    }

    int size()//返回堆中存放的数据数量
    {
        return Count;
    }
     bool isempty()//堆是否为空堆
     {
         return Count==0;
     }

    void change(int i,int item)//修改数据,i为用户索引，item为需要新修改的数据值
    {
        assert(i+1>=1);
        assert(IsInHeap(i));
        i+=1;//偏移操作,使其符合从1开始计数标准
        data[i]=item;
        int j;
       j=rev[i];
        shiftup(j);
        shiftdown(j);
        cout<<"change "<<i<<" to "<<item<<" succeed"<<endl;
    }

    int extractmax(){//取出最大值并返回最大值
        assert(Count>0);//判断是否有数据可取
        int ret;
        ret=data[index[1]];
       swap(index[1],index[Count]) ;//index[1]由最后一位来取代，之后Count缩小一位
        rev[index[1]]=1;
        rev[index[Count]]=0;
        Count--;
        shiftdown(1);//对新上来的index[1]进行下沉操作保证堆的正确
        return ret;
    }

    bool IsInHeap(int i){//判断用户提供的索引在堆中是否存在
        assert(i+1>=1&&i+1<=capacity);
        i+=1;//偏移用户索引使其成为堆中索引
        return rev[i]!=0;
    }
};




#endif //I= default;AP_H
