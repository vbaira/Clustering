/*************************************/
/*		File:utility.cpp             */
/*                                   */
/* Definition of  utility class      */
/*     member functions              */
/*                                   */
/*************************************/


#include "utility.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <vector> 
#include <stdio.h> 
#include <iterator> 
#include <fstream>
#include <sstream>
#include <regex>


using namespace std;


/*Parse command line options */
void Utility::parse_options(int argc , char* argv[],std::string& in,std::string& conf,std::string& out,std::string& metric){
	string s="USAGE : $ ./cluster –i <input file> –c <configuration file> -o <output file> -d <cosine/eucledian>\n";
	if (argc>9 || (argc%2 != 1) ){
		cerr << "Wrong number of arguments : "+s ;
		exit(EXIT_FAILURE);
	}
	int opt;
	while ( (opt = getopt(argc,argv,"i:c:o:d:")) != -1 ){
		switch(opt){
			case 'i':
				in = optarg;
				break;
			case 'c':
				conf = optarg;
				break;
			case 'o':
				out = optarg;
				break;
			case 'd':
				metric = optarg;
				break;
			default:
				cerr << s ;
				exit(EXIT_FAILURE);	
		}
	}
	if ( (metric!="cosine") && (metric!="eucledian") ){
		cerr << "Metric arguments supported are cosine and eucledian : " + s;
		exit(EXIT_FAILURE);
	}
	if ( in.empty() ){
		cout << "Please enter path for input file\n";
		cin >> in; 
	}
	if ( conf.empty() ){
		cout << "Please enter path for configuration file\n";
		cin >> conf;
	}
	if ( out.empty() ){
		cout << "Please enter path for output file\n";
		cin >> out;
	}
}



/*Function to read vectors from input file  and place them in  list */
void Utility::read_input_file(string& in,vector<data_point>& l){
	ifstream fs;
	fs.open(in.c_str());
	if ( ! fs.is_open() ){
		cerr << "Unable to open input file\n";
		exit(EXIT_FAILURE);
	} 
	/*tokenize input vectors by using a regular expreassion iterator*/
	regex delim("[^\\s,]+");
	/*read file line by line and insert data*/
	string buf;
	while( getline(fs,buf) ){
		if (buf.empty()){
			continue; 	//ignore empty lines
		}
		data_point dp;
		sregex_iterator start(buf.begin(),buf.end(),delim);
		sregex_iterator end;
		for (sregex_iterator i=start; i!=end; i++){
			if (i==start){
				dp.id=(*i).str();
			}
			else{
				dp.p.push_back( stod((*i).str()) );
			}
		}
		l.push_back(dp);
	}
	fs.close();		
}



/*Function to read configuration parameters from configuration file*/
void Utility::read_conf_file(std::string& conf,int* clusters,int* k, int* L){
	ifstream fs;
	fs.open(conf.c_str());
	if ( ! fs.is_open() ){
		cerr << "Unable to open configuration file\n";
		exit(EXIT_FAILURE);
	}
	string buf;
	while( getline(fs,buf) ){
		if (buf.empty()){
			continue; 	//ignore empty lines
		}
		size_t pos = buf.find(":");
		int value=stoi( buf.substr(pos+1) );
		if ( buf.find("number_of_clusters") != string::npos ){
			*clusters = value;
		}
		else if( buf.find("number_of_hash_functions") != string::npos ){
			*k = value;
		}
		else if ( buf.find("number_of_hash_tables") != string::npos ){
			*L = value;
		}
		else{
			continue;
		}
	}
	if (*clusters <= 1 || *k <= 0 || *L <= 0){
		cerr<< "Configuration arguments number_of_clusters, number_of_hash_functions, number_of_hash_tables must be >1 , >0 , >0 accordingly\n";
		exit(EXIT_FAILURE);
	} 
	fs.close(); 
}



/*Function to communicate with user to determine the methods used for the clustering*/
void Utility::setup(int* setup){
	int temp;

	do{
		cout << "Choose Initialization method\n";
		cout << "1. Random selection of k points\n";
		cout << "2. K-means++\n";
		cin  >> temp;
	}while(temp!=1 && temp!=2);
	setup[0]=temp;

	do{
		cout << "Choose Assignment method\n";
		cout << "1. Lloyd’s assignment\n";
		cout << "2. Assignment by Range search with LSH\n";
		cout << "3. Assignment by Range search with Hypercube\n";
		cin  >> temp;
	}while(temp!=1 && temp!=2 && temp!=3);
	setup[1]=temp;
	
	do{
		cout << "Choose Update method\n";
		cout << "1. K-means\n";
		cout << "2. Partitioning Around Medoids (PAM) improved like Lloyd’s\n";
		cin  >> temp;	
	}while(temp!=1 && temp!=2);
	setup[2]=temp;
}

