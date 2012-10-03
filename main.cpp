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
 * Structure for the data being passed into the thread
 */
struct thread_data{
    long tid;    //variable to hold the thread id
    
    //Hold the x and y arrays
    double *x_values;
    double *y_values;
    
    int increments;
    long inside;
    long total;
};

void *calculatePi(void *threadData){
    struct thread_data *currentData = (struct thread_data *)threadData;
    long tid = currentData->tid;
    long inside = currentData->inside;
    long total = currentData->total;
    double *x_values = currentData->x_values;
    double *y_values = currentData->y_values;
    cout<<"Thread "<<tid<<endl;
    for(int i = 0; i < currentData->increments; i++){
        x_values[i] = 0.5 + x_values[i]/(double)RAND_MAX;
        y_values[i] = 0.5 + y_values[i]/(double)RAND_MAX;
        
        total ++;
        if((x_values[i] * x_values[i]) + (y_values[i] * y_values[i]) < (0.5 * 0.5))
            currentData->inside++;
    }
    
    pthread_exit(NULL);
}


/*
 * 
 */
int main(int argc, char** argv) {
    time_t start = time(0);             //Start time
    time_t end;                             //End time
    long total = 0;
    long inside = 0;
    long pi = 0;
    
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
    cout<<"Number of elements in NUMBER_THREADS: "<<size<<endl<<endl;
    
    /*
     * Create Threads
     * First loop: the array of cores we're testing
     */
    for(long i = 0; i < size; i ++){
        int increments = 500000000/NUM_THREADS[i];      //Calculate the increments for the array split
        int start = 0;
        
        // Create an array with 500000000 random numbers
        double x[500000000];        //X values
        double y[500000000];        //Y values
        
        //populate the array
        for(int index = 0; index <500000000; index++){
            x[index] = (double)rand();
//            cout<<x[index]<<endl;
            y[index] = (double)rand();
//            cout<<y[index]<<endl;
        }
        //split up the array
        double x_split[NUM_THREADS[i]][increments];
        double y_split[NUM_THREADS[i]][increments];
        int current = 0;
        for(int index = 0;index < NUM_THREADS[i]; i++){
            for(int j =0; j <increments; j++){
                x_split[index][j] = x[current];
                y_split[index][j] = y[current];
                current++;
            }
        }
        //output the number of cores we're testing
        cout<<"Number of cores: "<<NUM_THREADS[i]<<endl;
        
        //Create an array of threads for the number of cores being tested
        pthread_t threads[NUM_THREADS[i]];
        int rc;
        
        thread_data thread_data_array[NUM_THREADS[i]];
        
        void *status;           //Pointer to hold the thread's return status
        for(long j = 0; j < NUM_THREADS[i]; j++){
            //Populate the thread data array
            thread_data_array[j].tid = (long)j;
            thread_data_array[j].x_values = x_split[j];
            thread_data_array[j].y_values = y_split[j];
            thread_data_array[j].increments = increments;
            
            rc = pthread_create(&threads[j], NULL, calculatePi,(void *) &thread_data_array[j]);
            if(rc){
                cout<<"ERROR:\tReturn code from pthread_create() is:\t"<<rc<<endl;              //print out error message
                exit(-1);               //return failure
            }
            total = total + thread_data_array[j].total;
            inside = inside + thread_data_array[j].inside;
        }
        //Make sure the main thread waits for the threads to finish before resuming execution
         for(long j = 0; j < NUM_THREADS[i]; j++){
            rc = pthread_join(threads[j], &status);
            if(rc){
                cout<<"ERROR:\tReturn code from pthread_join() is:\t"<<rc<<endl;              //print out error message
                exit(-1);               //return failure
            }
        }
        
    }

    pi = 4.0 * static_cast<double>(inside)/static_cast<double>(total);
    end = time(0);
    cout <<endl<< "It took " << end-start << "  seconds"  << endl;
    cout << "pi is about: " << pi << endl;
    return EXIT_SUCCESS;
}

