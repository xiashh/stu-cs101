#include <iostream>
#include <stdio.h>		/* stdin */
#include <limits.h>		/* INT_MAX */
#include <assert.h>		/* assert */
#include <queue>			/* priority_queue */
#include <time.h>
using namespace std;
  
#define MAX_VERTEX_NUM    10000
  
class UnionFindSets {
private:
    int PI[MAX_VERTEX_NUM];
    int rank[MAX_VERTEX_NUM];
    int size;
public:
    UnionFindSets(int size) {
    	this->size = size;
    	for(int vertexIdx=0; vertexIdx<size; vertexIdx++) {
    		PI[vertexIdx] = -1;
    		rank[vertexIdx] = -1;
    	}
    }
    void makeset(int x) {
    	assert(x >= 0 && x < size);
    	PI[x] = x;
    	rank[x] = 0;
    }
    int find(int x) {
    	assert(x >= 0 && x < size);
        // cout << "<find>:" << endl; 
        // cout << "\tPI[" << x << "]: " << PI[x] << endl;
        /*
         * find(PI[x]): backtracking, finding the root node
         * PI[x]=<backtracking result>: 
         *	directly connect the leaf node to the root node to achieve path compression
         */
        if(x != PI[x]) {
        	PI[x] = find(PI[x]);
        }
    	return PI[x];
    }
    void unite(int x, int y) {
    	assert(x >= 0 && x < size);
    	assert(y >= 0 && y < size);
        // cout << "<unite>: " << endl;
        int rx = find(x);
        int ry = find(y);
        // cout << "\t" << x << "["  << rx << "]" << y << "[" << ry << "]" << endl;
    	assert(rx >= 0 && rx < size);
    	assert(ry >= 0 && ry < size);
        if(rx == ry) {
        	return;
        }
        if(rank[rx] > rank[ry]) {
        	PI[ry] = rx;
        }
        else {
            PI[rx] = ry;
            if(rank[rx] == rank[ry]) {
            	rank[ry] += 1;
            }
        }
    }
    void printset() {
    	cout << "<Union&Find set>: " << endl;
    	for(int i=0; i<size; i++) {
    		cout << "\tPI[" << i << "]: " << PI[i]
    			 << "   "
    			 << "rank[" << i << "]: " << rank[i] << endl;
    	}
    }
};
   
struct adjVertexNode {
  int adjVertexIdx;
  int weight;
  adjVertexNode* next;
};
  
struct VertexNode {
  int data;
  int vertexIdx;
  adjVertexNode* list;
  // cost for VertexNode to reach current MST
  int cost;
  // recording the pre-visit VertexNode in the path --> restore a MST
  VertexNode* prev;
};
  
struct Edge {
  int fromIdx, toIdx;
  int weight;
  bool operator< (const Edge& right) const {
    return weight > right.weight;
  };
};
   
struct Graph {
  VertexNode VertexNodes[MAX_VERTEX_NUM];
  int vertexNum;
  int edgeNum;
};
  
void CreateGraph (Graph& g) {
  int i, j, edgeStart, edgeEnd, weight;
  adjVertexNode* adjNode;
  //cout << "Please input vertex and edge num (vertex-num edge-num):" <<endl;
  cin >> g.vertexNum >> g.edgeNum;
  
  //cout << "Please input vertex information (v1)/n note: every vertex info end with Enter" <<endl;
  for (i=0; i<g.vertexNum; i++) {
    g.VertexNodes[i].data = i; // vertex data info.
    g.VertexNodes[i].vertexIdx = i;
    g.VertexNodes[i].list = NULL;
    g.VertexNodes[i].prev = NULL;
  }
  //cout << "input edge information(start end):" << endl;
  for (j=0; j<g.edgeNum; j++)	{
    cin >> edgeStart >> edgeEnd >> weight;
    // insert new adjacent VertexNode at the begining of the adjacent list
    adjNode = new adjVertexNode;
    adjNode->adjVertexIdx = edgeEnd;
    adjNode->weight = weight;
    adjNode->next = g.VertexNodes[edgeStart].list;
    g.VertexNodes[edgeStart].list = adjNode;
  }
}
  
void PrintAdjList(const Graph& g) {
  cout << "The adjacent list for graph is:" << endl;
  
  for (int i=0; i < g.vertexNum; i++) {
    cout << " " << g.VertexNodes[i].data << "->";
    adjVertexNode* head = g.VertexNodes[i].list;
    if (head == NULL)
      cout << "NULL";
    while (head != NULL) {
      cout << g.VertexNodes[head->adjVertexIdx].data << "(" << head->weight << ") ";
      // printf("%d(%d)", g.VertexNodes[head->adjVertexIdx].data, head->weight);
      head = head->next;
    }
    cout << endl;
  }
}
  
void DeleteGraph(Graph& g) {
  for (int i=0; i<g.vertexNum; i++) {
    adjVertexNode* tmp = NULL;
    while(g.VertexNodes[i].list != NULL) {
      tmp = g.VertexNodes[i].list;
      g.VertexNodes[i].list = g.VertexNodes[i].list->next;
      delete tmp;
      tmp = NULL;
    }
  }
}
  
void Kruskal(Graph& g) {
  UnionFindSets sets(g.vertexNum);
  // use priority_queue for sorting the edges E by weight
  priority_queue<Edge> EdgeQueue;
  for(int i=0; i<g.vertexNum; i++) {
    sets.makeset(g.VertexNodes[i].vertexIdx);
    adjVertexNode* head = g.VertexNodes[i].list;
    while (head != NULL) {
      Edge e;
      e.fromIdx = g.VertexNodes[i].vertexIdx;
      e.toIdx = head->adjVertexIdx;
      e.weight = head->weight;
      EdgeQueue.push(e);

      head = head->next;
    }
  }
  cout << "\nMST constructing: " << endl;
  while(!EdgeQueue.empty()) {
    Edge e = EdgeQueue.top();
    EdgeQueue.pop();
    // cout << "\npop: " << e.fromIdx << "->" << e.toIdx << "(" << e.weight << ")" << endl;
    if(sets.find(e.fromIdx) != sets.find(e.toIdx)) {
      /*
			 * 2 edges with same vertex in an undirect graph
			 *	but every VertexNode can only have on prev.
			 */
      if(g.VertexNodes[e.toIdx].prev != NULL) {
        continue;
      }
      g.VertexNodes[e.toIdx].prev = &g.VertexNodes[e.fromIdx];
      g.VertexNodes[e.toIdx].cost = e.weight;
      // cout << "\t+ "
      //    << g.VertexNodes[e.fromIdx].data << "-->" << g.VertexNodes[e.toIdx].data
      //    << "(" << e.weight << ")" << endl;
 
      sets.unite(e.fromIdx, e.toIdx);
      // sets.printset();
    }
  }
}
   
// backtracking for the path
void PrintMST(Graph& g) {
  int cost = 0;
  // MST always starts from 0
  for(int i=g.vertexNum-1; i>=0; i--) {
    if(g.VertexNodes[i].prev != NULL) {
      // cout << "\t+ "
      //    << g.VertexNodes[i].data << "<--" << g.VertexNodes[i].prev->data
      //    << "(" << g.VertexNodes[i].cost << ")" << endl;

      printf("\t+%d<--%d(%d)\n", g.VertexNodes[i].data,
                                 g.VertexNodes[i].prev->data,
                                 g.VertexNodes[i].cost);
       cost += g.VertexNodes[i].cost;
    }
  }
  cout << "   cost: " << cost << endl;
}
  
int main(int argc, const char** argv) {
  freopen("in", "r", stdin);
  clock_t t1 = clock (), t2 = clock ();
  
  Graph g;
  CreateGraph(g);
  cout << ((float)clock () - t1) / CLOCKS_PER_SEC << endl;
    t1 = clock ();
  // PrintAdjList(g);
  // cout << ((float)clock () - t1) / CLOCKS_PER_SEC << endl;
  //   t1 = clock ();
  
  Kruskal(g);
  cout << ((float)clock () - t1) / CLOCKS_PER_SEC << endl;
    t1 = clock ();
   
  cout << endl;
  cout << "Minimum Spanning Tree: " << endl;
  PrintMST(g);
  cout << ((float)clock () - t1) / CLOCKS_PER_SEC << endl;
  cout << ((float)clock () - t2) / CLOCKS_PER_SEC << endl;
   
  DeleteGraph(g);
  return 0;
}