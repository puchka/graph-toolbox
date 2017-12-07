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
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
typedef std::pair<int,int> E;

const char* name[] = { "0", "1", "2", "3", "4" };

Fl_Window *window = NULL;
Fl_File_Chooser *G_chooser = NULL;
Fl_Box *box = NULL;
Fl_JPEG_Image *img = NULL;

void generate_graph_image(const string path)
{
  ofstream fout ("graph1.gv");
  ifstream fin (path);
  int num_nodes, n;
  fin >> num_nodes;
  Graph g(num_nodes);
  vector<int> weights;
  for (int i = 0; i < num_nodes; i++)
  {
    for (int j = 0; j < num_nodes; j++)
    {
      fin >> n;
      if (i >= j && n != 0)
      {
	add_edge(i, j, g);
	weights.push_back(n);
      }
    }
  }
  write_graphviz(fout, g, make_label_writer(name));
  system("dot -Tjpeg graph1.gv -o image.jpg");
}

void ChooseFile_CB(Fl_Widget*w, void*data) {
    
  if ( ! G_chooser ) {
    G_chooser = new Fl_File_Chooser("", "", Fl_File_Chooser::SINGLE, "");
  }

  G_chooser->directory(NULL);
  G_chooser->filter(NULL);
  G_chooser->type(Fl_File_Chooser::SINGLE);
  G_chooser->label("Choose input");
  G_chooser->show();

  // Block until user picks something.
  //     (The other way to do this is to use a callback())
  //
  while(G_chooser->shown()) {
    Fl::wait();
  }

  // Print the results
  if ( G_chooser->value() == NULL ) {
    fprintf(stderr, "(User hit 'Cancel')\n");
    return;
  }

  fprintf(stderr, "DIRECTORY: '%s'\n", G_chooser->directory());
  fprintf(stderr, "    VALUE: '%s'\n", G_chooser->value());
  fprintf(stderr, "    COUNT: %d files selected\n", G_chooser->count());
  if ( G_chooser->count() > 1 ) {
    for ( int t=1; t<=G_chooser->count(); t++ ) {
      fprintf(stderr, " VALUE[%d]: '%s'\n", t, G_chooser->value(t));
    }
  }
  fprintf(stderr, "--------------------\n");
  generate_graph_image(G_chooser->value());

  img = new Fl_JPEG_Image("image.jpg");
  box->image(*img);
  
  Fl::lock();
  {
    box->damage();
    box->redraw();
  }
  Fl::unlock();
}

int main(int argc, char *argv[])
{
  if (!window) {
    window = new Fl_Window(1024, 640, "Graph Toolbox");
  }
  Fl_Box *title = new Fl_Box(360, 20, 300, 100, "Graph Toolbox");
  title->box(FL_UP_BOX);
  title->labelfont(FL_BOLD+FL_ITALIC);
  title->labelsize(16);

  Fl_Button *choose_file = new Fl_Button(10, 150, 100, 50, "Read File ...");
  choose_file->callback(ChooseFile_CB);

  if (!img) {
    img = new Fl_JPEG_Image("image.jpg");
  }

  if (!box) {
    box = new Fl_Box(500, 150,  img->w(), img->h());
  }
  box->image(*img);
  
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
