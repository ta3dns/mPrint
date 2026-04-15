#include "fonts.h"
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

vectorFont* setupFont(void);

fontLoader fontParser = {
    .loadFont = (vectorFont* (*)(void))setupFont,
    .context = NULL
};

glyph* fontMap[128]; // ASCII map to glyphs, populated at runtime
    
int hersheyToAscii(int hersheyCode){

    int id;
    if (hersheyCode >= 501 && hersheyCode <=526){
        id = 'A' + (hersheyCode - 501);
    } else if (hersheyCode >= 601 && hersheyCode <= 626){
        id = 'a' + (hersheyCode - 601);
    } else if (hersheyCode >= 701 && hersheyCode <= 730){
        id = '0' + (hersheyCode - 701);
    } else if (hersheyCode == 710){
        id = '.';
    } else if (hersheyCode == 711){
        id = ',';
    } else if (hersheyCode == 712){
        id = ':';
    } else if (hersheyCode == 713){
        id = ';';
    } else if (hersheyCode == 699){
        id = '!';
    } else if (hersheyCode == 715){
        id = '?';
    } else {
        id = -1; // Invalid code
    }
    return id;
}

int parseId(char* line){
    int id; 
    if (sscanf(line, "%d5", &id) == 1){
        return hersheyToAscii(id);
    } else {
        return -1; // Invalid line
    }
}

int parseHersheyLine(char* line, glyph* glyphPtr){ // Okay this is what edits the glyph struct. 
    char countStr[4];
    strncpy(countStr, line + 5, 3);
    countStr[3] = '\0';
    int numVertices = atoi(countStr);

    if (numVertices <= 1){
        glyphPtr->asciiCode = ' '; // Space character for empty glyphs
        glyphPtr->width = 16.0f; 
        glyphPtr->stepCount = 0;
        glyphPtr->steps = NULL;
        return 0;
    }
    int maxMoves = numVertices - 1; // Maximum possible moves (worst case)
    glyphPtr->steps = malloc(sizeof(fontStep) * maxMoves);

    int leftBound = line[8] - 'R';
    int rightBound = line[9] - 'R';
    glyphPtr->width = (float)(rightBound - leftBound);

    int stepIndex = 0;
    int penUp = 1; 

    for (int i = 10; line[i] != '\n' && line[i] != '\r' && line[i] != '\0'; i += 2) {
        if (line[i+1] == '\n' || line[i+1] == '\r' || line[i+1] == '\0') {
            break; 
        }
        if (line[i] == ' ' && line[i+1] == 'R') {
            penUp = 1; 
            continue;
        }

        float x = (float)(line[i] - 'R');
        float y = (float)-(line[i+1] - 'R');

        if (penUp){
            glyphPtr->steps[stepIndex].type = MOVE;
            glyphPtr->steps[stepIndex].data.move.dest = (point){x, y};
            penUp = 0;
        } else{
            glyphPtr->steps[stepIndex].type = LINE;
            glyphPtr->steps[stepIndex].data.line.dest = (point){x, y};
        }

        stepIndex++;

    }
    glyphPtr->stepCount = stepIndex;
    return 0;

}

// it just loops through the file and just edits the data inside the ascii structs to the correct instructions and steps

int loadFont(const char* fileName){
    FILE* fp = fopen(fileName, "r");
    if (!fp){
        fprintf(stderr, "Error opening font file: %s\n", fileName);
        return -1;
    }
    char line[512];
    while (fgets(line, sizeof(line), fp)){
        int asciiCode = parseId(line);
        if (asciiCode < 0 || asciiCode >= 128){
            continue; // Skip invalid lines
        }
        fontMap[asciiCode] = malloc(sizeof(glyph)); // Okay, so it allocates the asciiCode'th glyph in the list. 
        if (parseHersheyLine(line, fontMap[asciiCode]) != 0) {
            fprintf(stderr, "Error parsing Hershey line: %s\n", line);
            return -1;
        }
    }
    return 0;
}

vectorFont* setupFont(void){

    char* fileName = (char*)fontParser.context; // Get the file name from the context

    if (fileName == NULL){
        fprintf(stderr, "Font file name not provided in context.\n");
        return NULL;
    }

    vectorFont* currentFont = malloc(sizeof(vectorFont));

    if (loadFont(fileName) != 0){
        fprintf(stderr, "Failed to load font: %s\n", fileName);
        return NULL;
    }
    
    currentFont = malloc(sizeof(vectorFont));
    currentFont->name = fileName;
    currentFont->glyphs = fontMap;
    currentFont->capHeight = 21.0f; // Simplex cap height,
    
    return currentFont; 
}

