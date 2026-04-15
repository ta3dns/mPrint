# include "renderer.h"
# include "printer.h"
# include "fonts.h"
#  include <stdio.h>
# include "config.h"

// Takes the fonts and passes it to the printer. As pointers. 
// Uses absolute positions
#ifndef BEZIER // Only for hersher code 
// This file is intended to render the text and generate X Y coordinates for the letters. 
// Establish Global coorinates
#define START_X 0.0f
#define START_Y 0.0f

extern fontLoader FONT_LOADER;

float currentX = START_X;
float currentY = START_Y;

int penDown = 0; 

// I need to initialise the printer here

int renderGlyph(glyph* g, const char chr, printerHardware* hardware){
    if (g == NULL ||  hardware == NULL){
        fprintf(stderr, "Failed to render glyph. One or more arguments are NULL");
        return -1;
    }
    printf("Rendering %c (ASCII %d)\n", chr, (int)chr);
    for (int i = 0; i < g->stepCount; i++){
        fontStep step = g->steps[i];
        switch (step.type){
            case MOVE:
                penDown = 0; 
                currentX = step.data.move.dest.x;
                currentY = step.data.move.dest.y;

                break;
            case LINE:
                penDown = 1; 
                currentX = step.data.move.dest.x;
                currentY = step.data.move.dest.y;  
                break;
        }

        hardware->setPen(&penDown);
        hardware->move(&currentX, &currentY, &penDown); 


    }
    return 0; 
}



void renderString(const char* str, printerHardware* hardware, vectorFont* font, fontLoader* loader, const char* fontFileName){
    if (loader != NULL && loader->loadFont != NULL && fontFileName != NULL){
        loader->context = (void*)fontFileName; // Set the context to the font file name
        loader->loadFont(); // Load the font using the provided loader
        printf("Font loaded: %s\n", font->name);
    } else {
        fprintf(stderr, "Font loader or font file name not provided. Cannot load font.\n");
        return;
    }


    for (int i = 0; str[i] != '\0'; i++){

        char currentChar = str[i];
        int asciiValue = (int)currentChar;

        glyph* g = font->glyphs[asciiValue];
        
        if (g != NULL) {
            // Pass the pointer and the character by value
            if (renderGlyph(g, currentChar, hardware) != 0) {
                fprintf(stderr, "An error occurred drawing %c.\n", currentChar);
            }
        } else {
            // If the user typed a weird character not in the .jhf file
            printf("Skipping '%c' - No glyph found in font map.\n", currentChar);
        }

    }
}


#endif

#ifdef BEZIER
// Bezier rendering code will go here.
#endif
