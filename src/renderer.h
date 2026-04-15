#ifndef RENDERER_H
#define RENDERER_H

# include "fonts.h"
#include "printer.h"


void renderString(const char* str, printerHardware* hardware, vectorFont* font, fontLoader* loader, const char* fontFileName);
int renderGlyph(glyph* g, const char chr, printerHardware* hardware);

#endif
