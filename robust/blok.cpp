#include "blok.h"
#include <numeric>
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
			cout<<content.at(i)<<" ";
		}
}
blok::blok(){
	size=0;
}
blok::blok(Mat input_block, int _size){ 
	unsigned char *input = (unsigned char*)(input_block.data);
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		content.push_back(input[input_block.step1()*i+j]); 
	weight=0;
	size=_size;
}
int blok::operator()(int x, int y){
	return content.at(x+y*size);
}
blok blok::operator-(int _x){

	transform(content.begin(),content.end(),content.begin(),[_x](unsigned int x) { return x - _x; });
	return *this;
}
double blok::operator*(blok blk){
	double product=inner_product(this->content.begin(),this->content.end(),blk.content.begin(),0);
	return product;
}
Mat& blok::devectorize(){ //TODO: DOPISAC OBSLUGE WYJATKU GDY ROZMIARY CONTENT I MAT SIE NIE ZGADZAJA
	Mat *tmp=new Mat(size,size,CV_8UC1);
	
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			tmp->at<uchar>(i,j) = content.at(i*size+j);
	return *tmp;
}
int blok::getSize(){
return content.size();
}
double blok::mean(){
	double total = std::accumulate(content.begin(), content.end(), 0);
	double mean = total / content.size();
	return mean;

}
double blok::deviation(){
	double total = std::accumulate(content.begin(), content.end(), 0);
	double mean = total / content.size();
	vector<unsigned int> zero_mean( content );
	transform( zero_mean.begin(), zero_mean.end(), zero_mean.begin(),bind2nd( minus<double>(), mean ) );

	double deviation = inner_product( zero_mean.begin(),zero_mean.end(), zero_mean.begin(), 0.0f );
	deviation = sqrt( deviation / ( content.size() - 1 ) );
	return deviation;
}
double blok::corelation(blok &blk){
	double mean_inner=this->mean();
	double mean_outer=blk.mean();
	blok blk2(blk);
	std::reverse(blk.content.begin(),blk.content.end());
	cout<<"inn"<<mean_inner;
	cout<<"out"<<mean_outer;
	double a=inner_product(this->content.begin(),this->content.end(),blk2.content.begin(),0,[](double acc, double wyr){return acc+wyr;},[mean_inner,mean_outer](double x, double y){return (double)abs(((double)x-mean_inner)*((double)y-mean_outer));});
	double b=this->deviation()*blk.deviation();
	cout<<"a:"<<a<<endl;
	cout<<"b:"<<b<<endl; 
	return a/b;
}