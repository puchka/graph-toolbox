#include<iostream>
#include<string>
#include<vector>
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graphviz.hpp"

using namespace std;
using namespace boost;

const char* name[] = { "0", "1", "2", "3", "4" };

int main()
{
  int num_nodes, n;
  typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
  typedef std::pair<int,int> E;
  //vector<E> edges;
  vector<int> weights;
  cin >> num_nodes;
  Graph g(num_nodes);
  for (int i = 0; i < num_nodes; i++)
  {
    for (int j = 0; j < num_nodes; j++)
    {
      cin >> n;
      if (i >= j && n != 0)
      {
	//edges.push_back(E(i, j));
	add_edge(i, j, g);
	weights.push_back(n);
      }
    }
  }
  write_graphviz(std::cout, g, make_label_writer(name));
  /*
  vector<E>::iterator it;
  vector<int>::iterator it2;
  for(it = edges.begin(), it2 = weights.begin(); it != edges.end(); it++, it2++)    {
    cout << "(" << it->first << ", " << it->second << ") : " << *it2 << endl;
  }
  */
}
