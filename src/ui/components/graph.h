#ifndef GRAPH_H
#define GRAPH_H 

#include <stdio.h>
#include <functional>
#include <complex.h>

// Normal functions
typedef struct {
  std::function<float(float x)> f;
  float min;
  float max;
  float step;
  const char* label;
  // color; // fixme
} GraphFunction;


typedef struct {
  float x, y;
   // color; // fixme
  const char* label;
  float size;
} GraphPoint;

// Imagary
typedef struct{
  float real;
  float imag;
} IGraphPoint;

typedef struct{
  std::function<IGraphPoint(IGraphPoint X)> f;
  const char* label;
  // color; // fixme
} IGraphFunction;


// Structs

typedef struct {
  std::vector<GraphFunction> functions;
  const char* title;
  const char* xLabel;
  const char* yLabel;
} GraphData;

typedef struct {
  std::vector<IGraphFunction> functions;
  const char* title;
  const char* xLabel;
  const char* yLabel;
} IGraphData;



typedef struct {
  float x, y;
  float width, height;
  float xMin, xMax, yMin, yMax;
  float xStep, yStep;
  const char* title;
  const char* xLabel;
  const char* yLabel;
  std::vector<GraphFunction> functions;
  std::vector<GraphPoint> points;

} GraphConfig;

typedef struct {
  GraphData data;


} Graph;



namespace UI {
    class XYGraph {
    public:
        
        static void Show(bool* open);
    };
}

#endif // GRAPH_H



// 
//
//
// todo {sultan}:
// some reading to do later, byeee
//man complex.h 
//date of writting: 16-01-2025
//
//
// /* check that exp(i * pi) == -1 */
// #include <math.h>        /* for atan */
// #include <stdio.h>
// #include <complex.h>
//
// int main(void) {
//   double pi = 4 * atan(1.0);
//   double complex z = cexp(I * pi);
//   printf("%f + %f * i\n", creal(z), cimag(z));
// }

