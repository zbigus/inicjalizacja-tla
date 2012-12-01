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
blok::blok(int _size){
	size=_size;
	licznik =0;
}

blok::blok(){
	size=20;
	licznik =0;
}

blok::blok(Mat input_block, int _size){
	//content = vector<unsigned int>(size,0);
	unsigned char *input = (unsigned char*)(input_block.data);
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		content.push_back(input[input_block.step1()*i+j]); 
	weight=1;
	size=_size;
	licznik =0;
}

void blok::insert(unsigned int i){
	content.at(licznik % size)=i;
}


int blok::operator()(int x, int y){
	return content.at(x+y*size);
}
blok blok::operator-(int _x){

	transform(content.begin(),content.end(),content.begin(),[_x](unsigned int x) { return x - _x; });
	return *this;
}
Mat& blok::devectorize(){ //TODO: DOPISAC OBSLUGE WYJATKU GDY ROZMIARY CONTENT I MAT SIE NIE ZGADZAJA
	Mat *tmp=new Mat(size,size,CV_8UC1);
	
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			tmp->at<uchar>(j,i) = content.at(i+size*j);
	return *tmp;
}
int blok::getSize(){
return content.size();
}
int blok::getSqrtSize(){
	return sqrt((double)content.size());
}
double blok::mean(){
	double total = std::accumulate(content.begin(), content.end(), 0);
	double mean = total / content.size();
	return mean;

}

double blok::median()
{
	double median;
	size_t size = content.size();

	sort(content.begin(), content.end());
	if(size>1){
		if (size  % 2 == 0)
		{
			median = (content[size / 2 - 1] + content[size / 2]) / 2;
		}
		else 
		{
			median = content[size / 2];
		}
	}else{
		median = content[0];
	}

	return median;
}


double blok::deviation(){
	double total = std::accumulate(content.begin(), content.end(), 0);
	double mean = total / content.size();
	vector<unsigned int> zero_mean( content );
	transform( zero_mean.begin(), zero_mean.end(), zero_mean.begin(),bind2nd( minus<double>(), mean ) );

	double deviation = inner_product( zero_mean.begin(),zero_mean.end(), zero_mean.begin(), 0.0 );
	deviation = sqrt( deviation / ( content.size() - 1 ) );
	return deviation;
}
double blok::corelation(blok &blk){
	double mean_inner=this->mean();
	double mean_outer=blk.mean();
	double sigma_inner=0;
	double sigma_outter=0;
	double covariance=0;
	vector<unsigned int>::iterator itin;
	vector<unsigned int>::iterator itout;
	for(itin = content.begin();itin !=content.end();itin++)
		sigma_inner+=pow((*itin)-mean_inner,2);
	sigma_inner=sqrt(sigma_inner);
	for(itout = blk.content.begin();itout !=blk.content.end();itout++)
		sigma_outter+=pow((*itout)-mean_outer,2);
	sigma_outter=sqrt(sigma_outter);
	for(itin = content.begin(),itout=blk.content.begin();itin !=content.end();itin++,itout++)
		covariance+=(*itin-mean_inner)*(*itout-mean_outer);
	return covariance/(sigma_inner*sigma_outter);
}
double blok::mad(blok& blk)
{
	double sum=0;
	vector<unsigned int>::iterator itin;
	vector<unsigned int>::iterator itout;
	for(itin = content.begin(),itout=blk.content.begin();itin !=content.end();itin++,itout++)
		sum+=abs((int)*itin-(int)*itout);
	sum=sum/(size*size);
	return sum;
}
boolean blok::similar(blok &blk, double T1, double T2){
	double corr=this->corelation(blk);
	double mad=this->mad(blk);
	if(corr>=T1&& mad<=T2)
		return true;
	else return false;
}
void blok::operator*(double x){
	vector<unsigned int>::iterator it;
	for(it = this->content.begin();it!=this->content.end();it++)
		*it=*(it)*x;
}
void blok::setWeight(double x){
	weight=x;
}
double blok::getWeight(){
	return weight;
}
void blok::update(blok& blk)
{
	vector<unsigned int>::iterator itin, itout;
	for(itin = this->content.begin(),itout=blk.content.begin();itin !=this->content.end();itin++,itout++)
		*itin=((*itin)*weight+(*itout))/(weight+1);
	this->weight=this->weight+1;
	
}