/*************************************/
/*     File:utility.h                */
/*	                                 */
/*    Definition of utility class    */
/*                                   */
/*************************************/

#ifndef USAGE_H
#define USAGE_H

#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <cmath>

#define MAX_D  numeric_limits<double>::max()
#define MIN_D  numeric_limits<double>::min()


/***********************
Structure to represent
input data points
************************/
struct data_point{
	std::string id;
	std::vector<double> p;
	bool is_centroid=false;

	bool is_assigned=false;
	std::vector<int> contenders;

	void print(){
		//std::cout.precision(std::numeric_limits<double>::digits);
		std::cout << id << "\n";
		for (auto i=p.begin(); i!=p.end(); i++){
			std::cout << *i << " ";
		}
		std::cout << "\n";
	}
};



/********************************************
Utility class. 
Consists of static member functions for various 
utility tasks like i/o.
*********************************************/
class Utility{
public:
	static void parse_options(int argc , char* argv[],std::string& in,std::string& conf,std::string& out,std::string& metric);

	static void read_input_file(std::string& in,std::vector<data_point>& l);

	static void read_conf_file(std::string& conf,int* clusters,int* k, int* L);

	static void setup(int* setup);
};


/****************************************
Calculate the dot product of two vectors
*****************************************/
template <typename T,typename V>
T inner_product(std::vector<T>& a, std::vector<V>& b){ 
	if (a.size() != b.size()){
		std::cerr << "Inner product:vectors dont have the same dimension\n";
		exit(EXIT_FAILURE);
	}

    T product = 0;  
    for (int i = 0; i < a.size(); i++){
		product += (a[i] * b[i]); 
    }

    return product; 
}



#endif