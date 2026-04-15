#ifndef PRINTER_H
#define PRINTER_H
// This is a generic printer Hardware to configure later.

typedef struct printerHardware{
    void (*move)(float* x, float* y, int* penDown);
    void (*setPen)(int* penDown);
    void (*home)(void);
    void (*feed)(void);
    void* privateData; // For any hardware-specific data
} printerHardware;

typedef struct{
    float* x;
    float* y;
    int* penDown;
} printerState;

int printer_printString(printerHardware* hardware, const char* str);

#endif 