#include <vector>
#include <array>
#include <algorithm>
#include "maze.hpp"
#include "common.hpp"

maze::maze(int initHeight, int initLength, int initDropoutRate, float initGenerationRate){
  height = initHeight;
  length = initLength;
  dropoutRate = initDropoutRate;
  generationRate = initGenerationRate;
}

void maze::generateMaze(){
  std::vector<int> activeIndices;

  int newIndex;

  for( int i = 0; i < int(generationRate * height); i ++){
    newIndex = randomInt(height);
    activeIndices.push_back(newIndex);
    coordinates.push_back(std::array<float, 2>() = {newIndex, 0});
    paths.push_back(std::vector< std::array<float, 2> >());
    paths[i].push_back(std::array<float, 2>() = {newIndex, 0});
  }

  int activeIndicesCount = int(generationRate * height);
  std::vector<int>::iterator activeIndicesIterator;
  std::vector< std::vector< std::array<float, 2> >>::iterator activePathsIterator;
  int deletionIndex;

  for( int i = 1; i < length; i ++){

    for( int j = 0; j < dropoutRate && activeIndicesCount > 1; j ++){
      activeIndicesIterator = activeIndices.begin();
      activePathsIterator = paths.begin();

      deletionIndex = randomInt(activeIndicesCount);

      std::advance(activeIndicesIterator, deletionIndex);
      std::advance(activePathsIterator, deletionIndex);

      activeIndices.erase(activeIndicesIterator);
      paths.erase(activePathsIterator);

      activeIndicesCount --;
    }

    std::for_each(activeIndices.begin(), activeIndices.end(),
    [this](int &index){
      if(index == 0)
        index += randomInt(2);
      else if(index == height - 1)
        index += randomInt(0, -2);
      else
        index += randomInt(2, -2);
    });

    for( int j = 0; j < activeIndicesCount; j ++){
      coordinates.push_back(std::array<float, 2>() = {activeIndices[j], i});
      coordinates.push_back(std::array<float, 2>() = {activeIndices[j], i - 1});
      paths[j].push_back(std::array<float, 2>() = {activeIndices[j], i});
      paths[j].push_back(std::array<float, 2>() = {activeIndices[j], i - 1});
    }

    for( int j = 0; j < generationRate * height; j ++){
      newIndex = randomInt(height);
      coordinates.push_back(std::array<float, 2>() = {newIndex, i});
    }
  }
}

void maze::resetMaze(int initHeight, int initLength, int initDropoutRate, float initGenerationRate){
  height = initHeight;
  length = initLength;
  dropoutRate = initDropoutRate;
  generationRate = initGenerationRate;
  std::vector< std::array<float, 2> > ().swap(coordinates);
  std::vector< std::vector< std::array<float, 2> >> ().swap(paths);
}

maze::~maze(){}
