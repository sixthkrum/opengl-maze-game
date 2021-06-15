#include <vector>
#include <array>
#include "var.hpp"

namespace character{
  int y;
  int ymax;
  int ymin;
  int x;
  int xmax;
  int xmin;
  float *rgb;
  unsigned long timeElapsed; //milliseconds
  int gameState = 0;
  unsigned long score = 0;
  unsigned short level = 1;
  std::vector< std::array<float, 2> > coordinates;
};

namespace currentVectorScene{
  int *startingCoordinates;
  std::vector< std::vector< std::array<float, 2> >* > displayVectors;
  std::vector< float* > sceneColours;
};

unsigned short _windowLength;
unsigned short _windowHeight;
unsigned short _pointSize;
unsigned short _mazeLength = 100;
unsigned short _mazeHeight = 50;
unsigned short _dropoutRate = 2; //25
float _generationRate = 1.0; //1.2
maze* _currentMaze;
