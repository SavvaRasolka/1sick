

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;
vector<int> top, color, used, row;
vector<vector<int>> graph,rever,cycles,rezult;
void dfs1(int v, int m, int n) // поиск в глубину графа
{
    used[v] = true;
    for (int i = 0; i < n; i++)
    {
        if (graph[v][i] == 2) {
            for (int j = 0; j < m; j++) {
                if ((graph[j][i] == 1)&&(!used[j]))
                    dfs1(j, m, n);
            }
        }
    }
    //cout << v << endl;
    top.push_back(v);

}
void dfs2(int v, int m, int n, int c) // обход обратного графа
{       color[v] = c;
        cycles[c].push_back(v);
    for (int i = 0; i < n; i++)
    {  
        if (rever[v][i] == 2) {
        
            for (int j = 0; j < m; j++) {
                if ((rever[j][i] == 1) && (color[j] == -1)) {   
                    dfs2(j, m, n, c);
                }
            }
        }
    }
}
int rebro;
void compr(int v,vector<int> komp, int n) { // граф конденсации через МИ
    int ver = komp[v];
    int p = komp.size();
    for (int i = 0; i < n; i++) {
        if (graph[ver][i] == 2)
            for(int j=0;j<p;j++)
            if (graph[komp[j]][i] == 1)
            {
                rezult[v][rebro] = 2;
                rezult[j][rebro] = 1;
                rebro++;
            }
    }
}
int main()
{ int ver,reb,c,v,req=0;
vector<int> komp;
cout << "Vershin: " << endl;
cin >> ver;
cout << "Reber: " << endl;
cin >> reb;
graph.assign(ver, vector<int>(reb));
rever.assign(ver, vector<int>(reb));
cycles.assign(20, vector<int>());
used.resize(ver);
cout << "MATRICA INCIDENT:" << endl;
used.assign(ver, false);
//заполение матрицы инцидентности и обратной матрицы из файла
    ifstream graf("E:\\TIIT\\t1.txt"); 
    for (int i = 0; i < ver; i++) {
        for (int j = 0; j < reb; j++)
        {
            graf >> graph[i][j];
            if (graph[i][j] == 1)
                rever[i][j] = 2;
            else if (graph[i][j] == 2)
                rever[i][j] = 1;
            else rever[i][j] = 0;
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
         graf.close();
         dfs1(0, ver, reb);
         //заполнение цветов -1
         color.assign(ver+1, -1); 
         c = 0;
         //поиск циклов
         for (int i = 1; i <= ver; i++) { 
             v = top[ver-i];
             if(color[v]==-1)
             dfs2(v, ver, reb, c);
             c++;
         }
         cout << endl;
         //вывод соответствия вершин и циклов
         for (int i = 0; i < cycles.size(); i++) {
             if (cycles[i].size() != 0) {
                 cout << i << ": ";
                 komp.push_back(cycles[i][0]);
             }
             for (int j = 0; j < cycles[i].size(); j++)
                 if(cycles[i].size()!=0)
                 cout <<cycles[i][j] << " ";
             if (cycles[i].size() != 0) {
                 cout <<endl;
             }
         }
         cout << endl;
         int p = komp.size();
         rezult.assign(p, vector<int>(p - 1));
         for (int i = 0; i < p; i++)
             rezult[i].assign(p - 1, 0);
         for (int i = 0; i < komp.size(); i++) {
             compr(i, komp, reb);
         }
         for (int i = 0; i < rezult.size(); i++) {
             for (int j = 0; j < rezult[i].size(); j++)
                 cout << rezult[i][j] << " ";
             cout << endl;
         }
}
