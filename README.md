# K-means_K-medoid_Clustering
Implementation of K-means and K-medoids Clustering algorithms using various techniques for Cluster Initialization and Assignment.  
The program also calculates average silhouette score for each cluster and for all the data points.


## Compilation
~~~
make
~~~

## Execution
To execute the program :
~~~
./cluster –i <input file> –c <configuration file> -o <output file> -d <metric>
~~~
- Execution can also be performed without all or some of the arguments.In that case the missing argument either takes a default value ( metric=eucledian ) or the user is prompted to enter the value at runtime (input,output and configuration files).

At runtime , the user is prompted to choose between the supported techniques for each stage of the Clustering.  
Supported techiques are :  
- **Initialization**     
  - Random selection of k points (simplest)  
  - K-means++  
- **Assignment** 
  - Lloyd’s assignment 
  - Assignment by Range search with LSH
  - Assignment by Range search with Hypercube 
- **Update** 
  - K-means 
  - Partitioning Around Medoids (PAM) improved like Lloyd’s
