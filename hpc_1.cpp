#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

class Graph
{
private:
    vector<vector<int>> adjList;
    int vertices;

public:
    void createGraph()
    {
        cout<<"Enter number of vertices: ";
        cin>>vertices;
        adjList.clear();
        adjList.resize(vertices);
        cout<<"Enter number of edges: ";
        int edges;
        cin>>edges;
        for(int i=0; i<edges; i++)
        {
            int v1, v2;
            cout<<"Edge "<<i+1<<endl;
            cout<<"Vertex 1: ";
            cin>>v1;
            cout<<"Vertex 2: ";
            cin>>v2;
            adjList[v1].push_back(v2);
            adjList[v2].push_back(v1);
        }
    }
    
    void display()
    {
        for(int i=0; i<adjList.size(); i++)
        {
            cout<<i<<" -> ";
            for(auto j:adjList[i])
                cout<<j<<", ";
            cout<<endl;
        }
    }
    
    void seqBFS()
    {
        vector<bool> visited(vertices, false);
        queue<int> queue;
        int current;
        cout<<"Enter start vertex: ";
        cin>>current;
        queue.push(current);
        visited[current] = true;
        
        while(!queue.empty())
        {
            current =  queue.front();
            queue.pop();
            cout<<current<<" ";

            for(int i=0; i<adjList[current].size(); i++)
            {
                if(!visited[adjList[current][i]])
                {
                    queue.push(adjList[current][i]);
                    visited[adjList[current][i]] = true;
                }
            }
        }
        cout<<endl;
    }

    void parBFS()
    {
        vector<bool> visited(vertices, false);
        queue<int> queue;
        int current;
        cout<<"Enter start vertex: ";
        cin>>current;
        queue.push(current);
        visited[current] = true;
        
        while(!queue.empty())
        {
#pragma omp parallel shared(queue, visited)
            {
#pragma omp single 
                {
                    current =  queue.front();
                    queue.pop();
                    cout<<"Thread "<< omp_get_thread_num() << " -> " << current <<endl;
                }
#pragma omp for
                for(int i=0; i<adjList[current].size(); i++)
                {
                    if(!visited[adjList[current][i]])
                    {
#pragma omp critical 
                        {
                            queue.push(adjList[current][i]);
                            visited[adjList[current][i]] = true;
                        }
                    }
                }
            }
        }
        cout<<endl;
    }

    void DFS(bool seq)
    {
        int current;
        cout<<"Enter start vertex: ";
        cin>>current;
        vector<bool> visited(vertices, false);

        if(seq)
            seqDFS(current, visited);
        else
            parDFS(current, visited);
    }

    void seqDFS(int current, vector<bool> &visited)
    {        
        visited[current] = true;
        cout<<current<<" ";

        for(int i=0; i<adjList[current].size(); i++)
            if(!visited[adjList[current][i]])
                seqDFS(adjList[current][i], visited);
    }

    void parDFS(int current, vector<bool> &visited)
    {
#pragma omp critical
        {
            visited[current] = true;
            cout<<"Thread "<< omp_get_thread_num() << " -> " << current<<endl;
        }
#pragma omp for
        for(int i=0; i<adjList[current].size(); i++)
            if(!visited[adjList[current][i]])
                seqDFS(adjList[current][i], visited);
    }

};

int main()
{
    Graph obj;
    int choice = -1;
    while(choice != 0)
    {
        cout<<"1. Create Graph"<<endl;
        cout<<"2. Display Graph"<<endl;
        cout<<"3. Sequential BFS"<<endl;
        cout<<"4. Parallel BFS"<<endl;
        cout<<"5. Sequential DFS"<<endl;
        cout<<"6. Parallel DFS"<<endl;
        cout<<"Press 0 to exit"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        double startTime = omp_get_wtime();
        if (choice == 1)
            obj.createGraph();
        else if(choice == 2)
            obj.display();
        else if(choice == 3)
            obj.seqBFS();
        else if(choice == 4)
            obj.parBFS();
        else if(choice == 5)
            obj.DFS(true);
        else if(choice == 6)
            obj.DFS(false);
        else if(choice == 0)
            return 0;
        else 
            cout<<"Invalid choice"<<endl;
        double endTime = omp_get_wtime();
        cout<<"TIME: "<<(endTime - startTime) * 1000 << "ms" << endl;
    }
    return 0;
}
