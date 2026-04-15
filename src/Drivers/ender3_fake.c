#include "printer.h"
#include <stdio.h>

# define SPEED_XY 1500.0f
# define SPEED_Z 300.0f

void ender3_fakeMove(float* x, float* y, int* penDown) {
    if (*penDown){
    printf("G1 X%.2f Y%.2f F%.0f\n", *x, *y, SPEED_XY); // Move to (x,y) at speed 1500
   } else{
    printf("G0 X%.2f Y%.2f F%.0f\n", *x, *y, SPEED_XY); // Rapid move to (x,y) at speed 1500
   }

}


void ender3_fakeSetPen(int* down){
    if (*down){
        printf("G1 Z0.2 F%.0f\n", SPEED_Z); // Pen down
    } else {
        printf("G1 Z2.0 F%.0f\n", SPEED_Z); // Pen up
    }
}

void ender3_fakeHome(void){
    printf("G28\n"); // Home all axes
}

void ender3_initialize(void){
    ender3_fakeHome();
    printf("G21\n"); // Set units to millimeters
    printf("G90\n"); // Use absolute positioning
    printf("G92 Z5.0\n"); // Start with pen up
}


printerHardware ender3_fakeDriver = {
    .move = ender3_fakeMove,
    .setPen = ender3_fakeSetPen,
    .home = ender3_fakeHome,
    .feed = NULL, // Not implemented
    .privateData = ender3_initialize
};

