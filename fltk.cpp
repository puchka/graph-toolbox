#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_JPEG_Image.H>

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(2048,1024);

  Fl_JPEG_Image img("image.jpg");
  Fl_Box box(0,0,img.w(),img.h());
  box.image(img);

  //fl_draw_image(ptr,0,0,width,height,3,0);

  //Fl::visual(FL_RGB);
  
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
