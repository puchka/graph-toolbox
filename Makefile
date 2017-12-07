default:
	g++ -std=c++11 `fltk-config --cxxflags` main.cpp  `fltk-config --ldflags` -lfltk -lfltk_images -ljpeg -I ../boost_1_65_1 -o graph-toolbox
