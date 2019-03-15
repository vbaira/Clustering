#include "utility.h"
#include "clustering.h"
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <fstream>

using namespace std;

int main(int argc,char* argv[]){
	/*parse command line options*/
	string input_file,conf_file,output_file,metric="eucledian";
	Utility::parse_options(argc,argv,input_file,conf_file,output_file,metric);
	//cout << input_file+" "+conf_file+" "+output_file+" "+metric+"\n";

	/*read configuration file*/
	int cluster_num=1,k=4,L=5;
	Utility::read_conf_file(conf_file,&cluster_num,&k,&L);
	//cout<< cluster_num << " " << k << " " << L <<"\n";

	/*Determine setup*/
	int setup[3];
	Utility::setup(setup);
	//cout << setup[0] << " " << setup[1] << " " << setup[2] << "\n";

	/*read input file*/
	int dimension,train_set_sz;
	vector<data_point> train_set;
	Utility::read_input_file(input_file,train_set);
	dimension = train_set[0].p.size();
	train_set_sz = train_set.size();

	/*do the clustering*/
	Clustering clustering(setup,cluster_num,k,L,train_set,metric);
	clustering.start();
	clustering.output(output_file);
}