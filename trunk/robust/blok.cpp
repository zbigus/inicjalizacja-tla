#include "blok.h"

/*blok(Mat input_block, int _size){ 
	content=input_block;
	weight=0;
	size=_size;
	}*/
void blok::dump(void){
	for(unsigned int i=0;i<content.size();i++)
		{
			if(i%size==0)
				cout<<endl;
			cout<<content.at(i);
		}
}

blok::blok(Mat input_block, int _size){ 
	unsigned char *input = (unsigned char*)(input_block.data);
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		content.push_back(input[input_block.step1()*i+j]); //wywala program
	weight=0;
	size=_size;
}
int blok::operator()(int x, int y){
	return content.at(x+y*size);
}
Mat& blok::operator=(blok&){
	Mat tmp;
	tmp.create(size,size,CV_8UC1);
	return tmp;
}