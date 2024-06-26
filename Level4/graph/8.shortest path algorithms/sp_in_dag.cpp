// C++ program to find single source shortest paths 
// in a Directed Acyclic Graph (DAG). 
#include<bits/stdc++.h>
using namespace std;


// V represents number of Vertices, present 
// in the given DAG.
int V;
// INF means infinity, which is taken
// as largest possible value of 32-bit integer.
int INF=INT_MAX;

// Node class
class Node{
public:
    // v is the vertex, 
    // and wt is the weight.
    int v;
    int wt;
    Node(int _v,int _wt){
        v=_v;
        wt=_wt;
    }
};
vector<vector<Node>> adj;
// Function to add edge u->v of weigth wt.
void addEdge(int u,int v,int wt){
    adj[u].push_back(Node(v,wt));
}

// Adjacency list. 

// Function to find topological Sort which is always possible
// as the given graph is a DAG.
void topologicalSort(int v, bool *visited,
                                stack<int> &st){
    // Marking v as visited.
    
    visited[v]=true;
    // Iterating for all the adjacent nodes of v.
    for(Node node:adj[v]){
        
        // If any adjacent node to v is not 
        // visited, call topologicalSort function on it.
        if(!visited[node.v]){
            topologicalSort(node.v, visited, st);
        }
    }
    // Push v into Stack
    
    st.push(v);
}

// Function to compute the shortest path 
// to all other vertices starting from src.
void shortestPath(int src){
    
    // Declare a Stack (st) which is used to find 
    // the topological sort of the given DAG.
    stack<int> st;

    // Declare a dist array where dist[i] denotes
    // shortest distance of src from i. 
    // Initialize all it's entries with INF and 
    // dist[src] with 0.
    int dist[V];
    for(int i=0;i<V;i++)
        dist[i]=INF;

    dist[src]=0;

    // Create boolean visited array to keep track 
    // of visited elements.
    bool visited[V];
    for(int i=0;i<V;i++)
        visited[i]=false;
    // Iterate for all the V vertices.
    for(int i=0;i<V;i++){
        // If 'i' found to unvisited call 
        // topoplogicalSort from there.
        if(!visited[i]){
            topologicalSort(i,visited,st);
        }
    }
    
    // Iterate till the stack is not empty.
    while(!st.empty()){
        // Pop element from stack and store it in u.
        int u=st.top();
        st.pop();

        // If shortest distance from src to u is 
        // not infinity i.e. it is reachable.
        
        if(dist[u]!=INF){
            // Iterate for all the adjacent vertices 
            // of u.
            for(Node node:adj[u]){
                // If distance of src->v is greater than
                // distance of src->u + u->v then update
                // the value as shown.
                if(dist[node.v]>dist[u]+node.wt)
                    dist[node.v]=dist[u]+node.wt;
            }
        }
    }
    
    // Print the distances.
    for(int i=0;i<V;i++){
        if(dist[i]==INF)
            cout<<"INF ";
        else
            cout<<dist[i]<<" ";
    }
    
}
// Main function
int main(){
    V=6;
    // Initialize Adjacency List.
    // adj=new ArrayList<>();
    for(int i=0;i<V;i++)
        adj.push_back(vector<Node>());

    // Add edges.
    addEdge(0, 2, 4);
    addEdge(1, 0, 3);
    addEdge(2, 3,-3);
    addEdge(2, 4, 2);
    addEdge(1, 2, 2);
    addEdge(1, 3, 5);
    addEdge(4, 3, 2);
    // Find the shortest path from a 
    // vertex (here 0).
    shortestPath(0);
    
    return 0;
}
