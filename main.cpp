/* 
 * File:   main.cpp
 * Author: mglitzos
 *
 * Created on September 28, 2012, 11:37 AM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    long total = 0;
    long inside = 0;
    double pi;

    time_t start = time(0);
    time_t end; 

    for (long index = 0; index < 500000000; index ++) 
    {
        // Random numbers from -.5 to .5
        double x = -.5 + (double)rand()/(double)RAND_MAX;
        //cout << x << endl;
        double y = -.5 + (double)rand()/(double)RAND_MAX;
        //cout << y << endl;

        total ++;
        if ((x * x) + (y * y) < (.5 * .5))
        {
                inside ++;
        }
    }

    pi = 4.0 * static_cast<double>(inside)/static_cast<double>(total);
    end = time(0);
    cout << "It took " << end-start << "  seconds"  << endl;
    cout << "pi is about: " << pi << endl;
    return 0;
}

