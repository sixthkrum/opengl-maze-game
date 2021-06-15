#include <GL/glut.h>
#include <array>
#include <vector>
#include <cstring>
#include "common.hpp"
#include "scenes.hpp"
#include "maze.hpp"
#include "var.hpp"

void setGameState(){
  if(character::x == character::xmax){
    character::gameState = 1;
  }
}

void timer(int gameState) {
  switch (gameState) {
    case 0:
      character::timeElapsed += 20;
      break;

    case 1:
      break;

    case 2:
      break;

    default:
      break;
  }

  glutPostRedisplay();
  glutTimerFunc(20, timer, character::gameState);
}

void keyPress(unsigned char key, int x, int y){
  switch(key){
    case 27:
      exit(0);
    break;
  }

  if(character::gameState == 0){
    switch(key){
      case 'w':
        if(character::y < character::ymax && moveAllowed(character::x, character::y + 1))
          character::y ++;
      break;

      case 's':
        if(character::y > character::ymin && moveAllowed(character::x, character::y - 1))
          character::y --;
      break;

      case 'd':
        if(character::x < character::xmax && moveAllowed(character::x + 1, character::y))
          character::x ++;
      break;

      case 'a':
        if(character::x > character::xmin && moveAllowed(character::x - 1, character::y))
          character::x --;
      break;
    }
  }
  setGameState();
  //glutPostRedisplay();
}

void initScreen(){
  glClearColor(0, 0, 0, 0);
  glPointSize(_pointSize);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, _mazeLength + 1, 0, _mazeHeight + 1);
}

void resizeFunc(int length, int height){
  float lc = length / (_mazeLength);
  float lh = height / (_mazeHeight + 30); //buffer space for text
  _windowLength = length;
  _windowHeight = height;
  _pointSize = lc < lh ? lc : lh;
  glPointSize(_pointSize);
}

void setVariablesForArgs(int argc, char** argv){
  if(argc == 5){
    if(strcmp(argv[1], "-l") == 0 && strcmp(argv[3], "-h") == 0){
      if(atoiCheck(argv[2]) && atoiCheck(argv[4])){
        _mazeLength = atoui(argv[2]);
        _mazeHeight = atoui(argv[4]);
      }
    }
  }
}

int main(int argc, char** argv){
  setVariablesForArgs(argc, argv);

  maze m(_mazeHeight, _mazeLength, _dropoutRate, _generationRate); //height, length, dropoutRate, generationRate
  _currentMaze = &m;

  m.generateMaze();

  character::coordinates = m.coordinates;

  currentVectorScene::displayVectors.push_back(&m.coordinates);
  currentVectorScene::sceneColours.push_back(new float[3]{1, 1, 1});

  currentVectorScene::startingCoordinates = new int[2]{1, 1}; // y, x

  character::x = m.paths[0][0][1] + currentVectorScene::startingCoordinates[1];
  character::y = m.paths[0][0][0] + currentVectorScene::startingCoordinates[0];
  character::xmax = _mazeLength;//length
  character::xmin = 1;
  character::ymax = _mazeHeight;//height
  character::ymin = 1;
  character::rgb = new float[3]{0, 0, 1};

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);

  _windowLength = glutGet(GLUT_SCREEN_WIDTH) / 2;
  _windowHeight = glutGet(GLUT_SCREEN_HEIGHT) / 2;

  glutInitWindowSize(_windowLength, _windowHeight);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("maze");
  glutKeyboardFunc(keyPress);
  glutTimerFunc(20, timer, 0);
  glutReshapeFunc(resizeFunc);

  glutDisplayFunc(displayFunc);
  initScreen();
  glutMainLoop();
}
