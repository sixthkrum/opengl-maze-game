#ifndef VAR_H
#define VAR_H

#include <vector>
#include <array>
#include "maze.hpp"

namespace character{
  extern int y;
  extern int ymax;
  extern int ymin;
  extern int x;
  extern int xmax;
  extern int xmin;
  extern float *rgb;
  extern unsigned long timeElapsed; //milliseconds
  extern int gameState;
  extern unsigned long score;
  extern unsigned short level;
  extern std::vector< std::array<float, 2> > coordinates;
};

namespace currentVectorScene{
  extern int *startingCoordinates;
  extern std::vector< std::vector< std::array<float, 2> >* > displayVectors;
  extern std::vector< float* > sceneColours;
};

extern unsigned short _windowLength;
extern unsigned short _windowHeight;
extern unsigned short _pointSize;
extern unsigned short _mazeLength;
extern unsigned short _mazeHeight;
extern unsigned short _dropoutRate;
extern float _generationRate;
extern maze* _currentMaze;

#endif
