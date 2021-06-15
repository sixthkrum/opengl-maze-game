#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <array>
#include <cmath>

class maze{
  public:

    maze(int initHeight, int initLength, int initDropoutRate, float initGenerationRate);

    int height;
    int length;
    int dropoutRate;
    float generationRate;

    std::vector< std::array<float, 2> > coordinates;
    std::vector< std::vector< std::array<float, 2> >> paths;

    void generateMaze();
    void resetMaze(int initHeight, int initLength, int initDropoutRate, float initGenerationRate);

    ~maze();
};

#endif
