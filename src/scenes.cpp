#include <GL/glut.h>
#include <stack>
#include <vector>
#include <array>
#include <cstring>
#include <cmath>
#include <thread>
#include "scenes.hpp"
#include "var.hpp"
#include "common.hpp"
#include "maze.hpp"

void displayCharacter(){
  glViewport((_windowLength - (_mazeLength + 1) * _pointSize) / 2, (_windowHeight - (_mazeHeight + 1) * _pointSize) / 2, (_mazeLength + 1)* _pointSize, (_mazeHeight + 1) * _pointSize);
  glBegin(GL_POINTS);

  glColor3f(character::rgb[0], character::rgb[1], character::rgb[2]);

  glVertex2f(character::x, character::y);

  glEnd();
}

void displayStats(){
  glViewport(0, _windowHeight - ((_windowHeight - (_mazeHeight + 1) * _pointSize) / 2), _windowLength, (_windowHeight - (_mazeHeight + 1) * _pointSize) / 2);
  glColor3f(1, 1, 1);

  unsigned long minutes = character::timeElapsed / 60000;
  unsigned long seconds = (character::timeElapsed % 60000) / 1000;
  unsigned long mseconds = character::timeElapsed % 1000;

  unsigned long timeVal[3] = {minutes, seconds, mseconds};

  static const char timeText[] = "Time Elapsed ";
  static const unsigned char timeTextLen = strlen(timeText);

  glRasterPos2f(0, 0);

  for (int i = 0; i < timeTextLen; i++) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, timeText[i]);
  }

  std::stack<char> *dum;

  for(int i = 0; i < 3; i ++){
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ':');

    dum = uitoas(timeVal[i]);

    while(!dum->empty()){
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13, dum->top());
      dum->pop();
    }
  }

  glRasterPos2f(0, 20);

  static const char scoreText[] = "Score ";
  static const unsigned char scoreTextLen = strlen(scoreText);

  for (int i = 0; i < scoreTextLen; i++) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, scoreText[i]);
  }

  dum = uitoas(character::score);

  while(!dum->empty()){
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, dum->top());
    dum->pop();
  }

  glViewport(0, 0, _windowLength, (_windowHeight - (_mazeHeight + 1) * _pointSize) / 2);
  glRasterPos2f(0, 13);

  static const char levelText[] = "Level ";
  static const unsigned char levelTextLen = strlen(levelText);

  for (int i = 0; i < levelTextLen; i++) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, levelText[i]);
  }

  dum = uitoas(character::level);

  while(!dum->empty()){
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, dum->top());
    dum->pop();
  }
}

void displayVectorScenes(){
  int *startingCoordinates = currentVectorScene::startingCoordinates;
  std::vector< std::vector< std::array<float, 2> >* > *displayVectors = &currentVectorScene::displayVectors;
  std::vector< float* > *sceneColours = &currentVectorScene::sceneColours;
  int sceneNum = 0;

  glViewport((_windowLength - (_mazeLength + 1) * _pointSize) / 2, (_windowHeight - (_mazeHeight + 1) * _pointSize) / 2, (_mazeLength + 1)* _pointSize, (_mazeHeight + 1) * _pointSize);
  //glViewport((600 - 101 * 5) / 2, (600 - 51 * 5) / 2, 101* 5, 51 * 5);
  glBegin(GL_POINTS);

  for(auto i: *displayVectors){
    glColor3f((*sceneColours)[sceneNum][0], (*sceneColours)[sceneNum][1], (*sceneColours)[sceneNum][2]);

    for(auto j: *i)
      glVertex2f(j[1] + startingCoordinates[1], j[0] + startingCoordinates[0]);

    sceneNum ++;
  }

  glEnd();
}

void displayFinishScene(){
  glViewport((_windowLength - (_mazeLength + 1) * _pointSize) / 2, 0, ((_mazeLength + 1) * _pointSize), (_windowHeight - (_mazeHeight + 1) * _pointSize) / 2);
  glColor3f(1, 1, 1);

  static const char finishText[] = "Finish!";
  static const unsigned char finishTextLen = strlen(finishText);

  glRasterPos2f((_mazeLength - finishTextLen) / 2, 18);

  for (int i = 0; i < 9; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, finishText[i]);
  }
}

void displayFunc(){
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  switch (character::gameState) {
    case 0:
      glLoadIdentity();
      displayVectorScenes();
      displayCharacter();
      displayStats();
      break;

    case 1:
      updateScore();
      displayFinishScene();
      displayStats();
      displayVectorScenes();
      displayCharacter();
      character::gameState = 2;
      break;

    case 2:
      {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(700ms);
      }

      if(_dropoutRate < _mazeHeight / 2)
        _dropoutRate ++;

      if(_generationRate < 1.2)
        _generationRate += 0.05;

/*
      _mazeLength += 20;

      _pointSize = _windowLength / (_mazeLength) < _windowHeight / (_mazeHeight + 10) ? _windowLength / (_mazeLength) : _windowHeight / (_mazeHeight + 10);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glClearColor(0, 0, 0, 0);
      glClear(GL_COLOR_BUFFER_BIT);
      glPointSize(_pointSize);
      gluOrtho2D(0, _mazeLength + 1, 0, _mazeHeight + 1);
*/
      _currentMaze->resetMaze(_mazeHeight, _mazeLength, _dropoutRate, _generationRate);
      _currentMaze->generateMaze();
      character::coordinates = _currentMaze->coordinates;

      clearCurrentVectorScene();
      currentVectorScene::displayVectors.push_back(&(_currentMaze->coordinates));
      currentVectorScene::sceneColours.push_back(new float[3]{1, 1, 1});

      character::level += 1;
      character::x = _currentMaze->paths[0][0][1] + currentVectorScene::startingCoordinates[1];
      character::y = _currentMaze->paths[0][0][0] + currentVectorScene::startingCoordinates[0];
      character::timeElapsed = 0;
      character::gameState = 0;
      break;

    default:
      break;
  }

  glEnd();
  glutSwapBuffers();
}

// todo unordered map
bool moveAllowed(int x, int y){
  for(auto e: character::coordinates){
    if((int)e[1] == x - currentVectorScene::startingCoordinates[1] && (int)e[0] == y - currentVectorScene::startingCoordinates[0]){
      return 1;
    }
  }

  return 0;
}

void updateScore(){
  float temp;
  temp = 1000 * 60 / (float)character::timeElapsed;
  temp = temp * (_dropoutRate + 1) * _generationRate * pow(10, 1 + _generationRate);
  character::score += (int)temp;
}

void clearCurrentVectorScene(){
  std::vector< std::vector< std::array<float, 2> >* > ().swap(currentVectorScene::displayVectors);
  std::vector< float* > ().swap(currentVectorScene::sceneColours);
}
