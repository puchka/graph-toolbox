default:
	g++ -std=c++11 `fltk-config --cxxflags` fltk.cpp  `fltk-config --ldflags` -lfltk -lfltk_images -ljpeg -o fltk
boost:
	g++ -I boost_1_65_1 main.cpp -o test
