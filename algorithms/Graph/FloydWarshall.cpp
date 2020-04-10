#include <iostream>
#include <vector>

using namespace std;
typedef vector<vector<int> > adjMatrix;

//计算图中任意两点对之间的最短路径距离
adjMatrix getShortestDis(const adjMatrix& adj)
{
    adjMatrix cMatrix = adj;
    int v_num=adj.size();
    //用第k个点松弛，状态迁移至c(k)
    for(int k=0;k<v_num;k++)
    {
        for(int i=0;i<v_num;i++)
        {
            for(int j=0;j<v_num;j++)
            {
                //若i,k间和k,j间有边
                if(cMatrix[i][k]<__INT_MAX__ && cMatrix[k][j]<__INT_MAX__)
                {
                    int temp = cMatrix[i][k] + cMatrix[k][j];
                    if(temp<cMatrix[i][j])//松弛步
                        cMatrix[i][j] = temp;
                }
            }
        }
    }
    return cMatrix;
}
//打印最短距离矩阵
void print(const adjMatrix& adj)
{
    for(const vector<int>& v:adj)//可减少拷贝构造
    {
        for(int i:v)
            cout << i <<" ";
        cout << "\n";
    }
}
int main()
{
    int v_num = 5;
    adjMatrix adj;
    //初始化
    for(int i=0;i<v_num;i++)
        adj.push_back(vector<int>(v_num));
    //默认不连通
    for(int i=0;i<v_num;i++)
        for(int j=0;j<v_num;j++)
            adj[i][j] = __INT_MAX__;
    //结点到自身的距离为0
    for(int i=0;i<v_num;i++)
        adj[i][i] = 0;
    //添加边
    adj[0][1] = 3;
    adj[0][2] = 8;
    adj[0][4] = -4;
    adj[1][3] = 1;
    adj[1][4] = 7;
    adj[2][1] = 4;
    adj[3][0] = 2;
    adj[3][2] = -5;
    adj[4][3] = 6;
    //计算最短路径长度
    adjMatrix shortestPath = getShortestDis(adj);
    //设置locale，配合wcout，使utf-8格式文件的中文字符正确被打印
    setlocale(LC_ALL,"");
    wcout << "图的邻接矩阵：\n";
    print(adj);
    cout << "\n";//wcout不能正常输出"\n"
    wcout << "图的最短距离矩阵：\n";
    print(shortestPath);
    return 0;
}

