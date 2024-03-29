#include<iostream>
#include<queue>
#include"ds/Graph.h"

using namespace std;
// struct disPair{
//     int nodeNum;
//     int *disPointer;
//     disPair(int _nodeNum,int* _disPointer){nodeNum=_nodeNum; disPointer = _disPointer;}
// };
// auto gt = [](const disPair& p1,const disPair& p2){ return *(p1.disPointer)>*(p2.disPointer);};

// vector<int> getShortestDis(Graph& g,int s=0)
// {
//     int v_num=g.getVnum();
//     //距离向量
//     vector<int> dis(v_num);
//     //优先级队列
//     priority_queue<disPair,vector<disPair>,decltype(gt)> pq(gt);
//     for(int i=0;i<v_num;i++)
//         pq.push(disPair(i,&dis[i]));
//     /*无法在dis被改变时，重新建堆，标准库提供的优先级队列不可直接用*/
// }
//在不在最小距离的顶点集合中 找最小值的顶点编号
int getMinIndex(vector<int>& dis,vector<bool> flag)
{
    int min=__INT_MAX__;//trick
    int pos = 0;//一定会在每次循环中找到最小值，初值不重要
    for(int i=0;i<dis.size();i++)
    {
        if(!flag[i]&&dis[i]<min)//flag为false的元素中的最小值
        {
            min = dis[i];
            pos = i;
        }
    }
    return pos;
}
//单源最短路，Dijkstra算法
vector<int> Dijkstra(Graph& g,int s=0)
{
    int v_num=g.getVnum();
    //距离向量
    vector<int> dis(v_num);
    dis[s] = 0;//源点距离为0
    //初始化为边的权重
    for(int i=0;i<v_num;i++)
        dis[i] = g.getWeight(s,i);
    //标记各点是否已为最小距离
    vector<bool> flag(v_num);
    for(bool f:flag)
        f = false;
    flag[s] = true;//源点初始为最小距离
    //第一次迭代
    for(int i=1;i<v_num;i++)
    {
        int node = getMinIndex(dis,flag);
        flag[node] = true;

        for(int i=0;i<v_num;i++)
        {
            //不为最小距离节点&&存在从node到i的边（短路计算，防止INT_MAX加法溢出
            if(!flag[i]&&g.existsEdge(node,i)&&dis[i]>dis[node]+g.getWeight(node,i))
            {
                dis[i] = dis[node]+g.getWeight(node,i);
            }
        }
    }

    return dis;
}

