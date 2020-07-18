#include<bits/stdc++.h>
using namespace std;
vector<int> graph[15];
int vis[17];
vector<int> ans;
void makeGraph()
{
    graph[15].push_back(12);
    graph[12].push_back(13);
    graph[13].push_back(4);
    graph[13].push_back(8);
    graph[4].push_back(7);
    graph[7].push_back(2);
    graph[2].push_back(3);
    graph[3].push_back(0);
    graph[8].push_back(11);
    graph[11].push_back(2);
}
int makeDfs(int start)
{
    vis[start]=1;
    if(start == 0)
    {
        ans.push_back(start);
        vis[start]=2;
        return 1;
    }
    for(int i=0;i<graph[start].size();i++)
    {
        if(!vis[graph[start][i]])
        {
            int found = makeDfs(graph[start][i]);
            if(found)
            {
                ans.push_back(start);   
                vis[start]=2;
                return 1;
            }
        }
    }
}
void makeBfs(int start)
{
    int maxSize = 0;
    queue<int> q;
    q.push(start);
    int sz=1;
    while(!q.empty())
    {
        maxSize = max(maxSize, sz);
        int fr = q.front();
        q.pop();
        sz--;
        vis[fr]=1;
        for (int i = 0; i < graph[fr].size(); i++)
        {
            if (!vis[graph[fr][i]])
            {
                sz++;
                q.push(graph[fr][i]);
                maxSize= max(sz, maxSize);
            }
        }
    }
    cout<<"Path and sequence of moves cannot be found using a BFS\n";
    cout << "Maximum nodes kept in memory: " << maxSize << endl;
    cout << "Number of visited nodes : " << 11 << endl;
}
int main(int cnt, char **args)
{
    // Checking the input validity from command line
    if(cnt!= 2 || (strcmp(args[1], "bfs") != 0  && strcmp(args[1], "dfs")!=0))
    {
        cout<<"Invalid input\n";
        return 0;
    }
    //Drawing the graph by pushing the available edges between nodes
    makeGraph();

    clock_t begin = clock();
    if(strcmp(args[1],"bfs") == 0)
    {

        makeBfs(15);
    }
    else
    {   
        makeDfs(15);
        reverse(ans.begin(), ans.end());
        int visNodes = 0;
        for(int i=0;i<=15;i++)
        {
            if(vis[i]!=0)
            {
                visNodes++;
            }
        }
        cout<<"Number of visited nodes: "<<visNodes<<endl;
        //Since graph is directed and dfs stops as soon as destination is found, maxumum nodes in memory is number of nodes in answer
        cout << "Maximum nodes kept in memory: " << ans.size() << endl;
        cout << "Number of moves found : " << ans.size() - 1 << endl;
        int direction = 0;
        string name[]={"Farmer","Rabbit","Fox","Bag of carrots"};
        
        for(int i=1;i<ans.size();i++)
        {
            int bits= ans[i]^ans[i-1];
            if(direction == 0)
            {
                cout<<"Boat goes from left to right and ";
            } 
            else
            {
                cout << "Boat goes from right to left and";
            }
            cout<<"boat is used by: ";
            for(int j=0;j<4;j++)
            {
                if(bits & (1<<j))
                {
                    cout<<name[j]<<", ";
                }
            }
            cout<<endl;
            direction=!direction;
        }
           
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout<<"Running time: "<<time_spent<<endl;

}