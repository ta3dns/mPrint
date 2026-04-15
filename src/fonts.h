#ifndef FONTS_H
#define FONTS_H

typedef enum{
    MOVE,
    LINE,

#ifdef BEZIER
    CURVE,
#endif
} stepType;

typedef struct{
    float x;
    float y;
} point;

typedef struct{
    point dest;
} moveTo;

typedef struct{
    point dest;
} lineSegment;


#ifdef BEZIER
typedef struct{
    point dest;
    point c1; 
    point c2;
} bezierSegment;
// Don't forget to use -DBEZIER when compiling to include bezier support.

#endif


typedef struct { // A single movement
    stepType type;
    union {
        moveTo move;
        lineSegment line;

        #ifdef BEZIER
        bezierSegment curve;
        #endif

    } data;
} fontStep;

typedef struct { // A character
    int asciiCode;
    int stepCount;
    fontStep* steps;
    float width; 
} glyph;

// Actually useful stuf
typedef struct{
    const char* name;
    glyph** glyphs; // an array of glyphs probably
    float capHeight; // Size of a capital letter
} vectorFont;

typedef struct{
    vectorFont* (*loadFont)(void);
    void* context; // For any font-loader-specific data
} fontLoader;

#endif
