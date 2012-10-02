/* 
 * File:   main.cpp
 * Author: mglitzos
 *
 * Created on September 28, 2012, 11:37 AM
 */

#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

/*
 * Print Thread IDs
 */
void *printThread(void *threadid){
    long tid = (long) threadid;
    cout<<"Thread "<<tid<<endl;
    pthread_exit(NULL);
}

/*
 * 
 */
int main(int argc, char** argv) {
    // TODO: generate random numbers in one thread
    // TODO: partition generated array of random numbers
    // TODO: run partitions in separate threads
    time_t start = time(0);             //Start time
    time_t end;                             //End time
    
    /*
     * Define the number of threads to be an array of unchangeable constants.
     * NUM_THREADS is an array that contains the number of cores we're modeling
     * To keep things simple, I'm going to make the specification for dual, triple, and quad cores.
     * Hence the elements contained in the array { 2, 3, 4}
     */
    const int NUM_THREADS[] = { 2, 3, 4};
    
    //Get the size of the NUM_THREADS array
    int size = sizeof(NUM_THREADS)/sizeof(int);
    
    //DEBUG STATEMENT
    cout<<size<<endl<<endl;
    
    /*
     * Create Threads
     * First loop: the array of cores we're testing
     */
    for(long i = 0; i < size; i ++){
        cout<<"Number of cores: "<<NUM_THREADS[i]<<endl;
        
        pthread_t threads[NUM_THREADS[i]];
        int rc;
        for(long j = 0; j < NUM_THREADS[i]; j++){
            rc = pthread_create(&threads[j], NULL, printThread,(void *)j);
            if(rc){
                cout<<"ERROR:\tReturn code from pthread_create() is:\t"<<rc<<endl;              //print out error message
                exit(-1);               //return failure
            }
        }
    }
//    long total = 0;
//    long inside = 0;
//    double pi;
//
//
//    for (long index = 0; index < 500000000; index ++) 
//    {
//        // Random numbers from -.5 to .5
//        double x = -.5 + (double)rand()/(double)RAND_MAX;
//        //cout << x << endl;
//        double y = -.5 + (double)rand()/(double)RAND_MAX;
//        //cout << y << endl;
//
//        total ++;
//        if ((x * x) + (y * y) < (.5 * .5))
//        {
//                inside ++;
//        }
//    }
//
//    pi = 4.0 * static_cast<double>(inside)/static_cast<double>(total);
//    end = time(0);
    cout << "It took " << end-start << "  seconds"  << endl;
//    cout << "pi is about: " << pi << endl;
    return EXIT_SUCCESS;
}

