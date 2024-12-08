#ifndef COLOR_H
#define COLOR_H

typedef struct Color {
	float r, g, b, a;
} Color;


/**
 * @brief Returns a Color Struct;
 *
 * @param r Color red value range 0.0-1.0.
 * @param g Color green value range 0.0-1.0.
 * @param b Color blue value range 0.0-1.0.
 * @param a Color alpha value range 0.0-1.0.
 */
static inline Color Colorf(float r, float g, float b, float a) {
	return (Color) {r, g, b, a};
}



/**
 * @brief Returns a Color Struct;
 *
 * @param r Color red value range 0-255.
 * @param g Color green value range 0-255.
 * @param b Color blue value range 0-255.
 * @param a Color alpha value range 0-255.
 */
static inline Color Colori(int r, int g, int b, int a) {
	return 
	(Color) {
		(float)r/255.0f, 
		(float)g/255.0f, 
		(float)b/255.0f, 
		(float)a/255.0f
	};
}


#endif // COLOR_H
