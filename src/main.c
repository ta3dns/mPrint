// 
// mPrint 
// An easy to use, open source print utility,
// designed to create gcode files from text for plotting. 
// Marinum @2026-04-12 OH5DLD (TA3DNS)

# include "printer.h"
# include "config.h"
# include "renderer.h"
#include "fonts.h"
# include <stdio.h>
#include <string.h>

extern printerHardware PRINTER;
extern fontLoader FONT_LOADER;


void getStringInput(char* prompt, char* buffer, size_t bufferSize){

    if (prompt == NULL){
        printf("Please enter input: ");
    } else {
        printf("%s", prompt);
    }

    if (fgets(buffer, bufferSize, stdin) != NULL){

        buffer[strcspn(buffer, "\n")] = '\0'; 
    } else{
        buffer[0] = '\0'; 
    }

    
}

int main(void){

    char fontName[FILENAME_MAX];
    char textInput[256];

    getStringInput("Please enter name of the font you'd like to load: ", fontName, sizeof(fontName)); 
    if (fontName[0] == '\0'){
        fprintf(stderr, "Invalid font name!\n");
        return -1; 
    }

    getStringInput("Please enter the string you'd like to be passed to the printer: ", textInput, sizeof(textInput)); 

    if (textInput[0] == '\0'){
        fprintf(stderr, "Invalid input!\n");
        return -1; 
    }
    
    vectorFont* currentFont; 

    FONT_LOADER.context = fontName; 
    currentFont = FONT_LOADER.loadFont();

    if (currentFont == NULL){
        fprintf(stderr, "Failed to load the font into memory.\n");
        return -1;
    }

    renderString(textInput, &PRINTER, currentFont, &FONT_LOADER, fontName); 

    return 0;
}

