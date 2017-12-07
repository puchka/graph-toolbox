#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graphviz.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_JPEG_Image.H>

using namespace std;
using namespace boost;

const char* name[] = { "0", "1", "2", "3", "4" };

int main(int argc, char *argv[])
{
  ofstream fout ("graph1.gv");
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
  write_graphviz(fout, g, make_label_writer(name));
  system("dot -Tjpeg graph1.gv -o image.jpg");

  Fl_Window *window = new Fl_Window(1024, 640, "Graph Toolbox");

  Fl_Box *title = new Fl_Box(360, 20, 300, 100, "Graph Toolbox");
  title->box(FL_UP_BOX);
  title->labelfont(FL_BOLD+FL_ITALIC);
  title->labelsize(16);
  
  Fl_JPEG_Image img("image.jpg");
  Fl_Box box(100, 50,img.w(),img.h());
  box.image(img);
  
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
