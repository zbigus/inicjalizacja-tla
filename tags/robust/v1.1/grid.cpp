#include"grid.h"



grid::grid(int _width, int _height){ 

width=_width;
height=_height;

}
std::vector<blok>& grid::operator()(int x, int y){
	return content.at(x+y*width);
}


int grid::getWidth(){
	return width;
}
int grid::getHeight(){
	return height;
}
void grid::setWidth(int _width){
	width=_width;
}
void grid::setHeight(int _height){
	height=_height;
}
void grid::insertAt(int x,int y,blok &blk)
{
	vector<vector<blok>>::iterator it;

	it = content.begin();
	for(int i=0;i<y*width+x;i++)
		++it;
	it->push_back(blk);
	//content.insert ( it , y*width+x,blk );
}
void grid::reserve(int n){
	content=vector<vector<blok>>(n);
}