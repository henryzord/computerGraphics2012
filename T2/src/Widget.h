/**
Henry Cagnini
201010352
*/

#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <SCV/SCV.h>

#ifndef __GAME__CANVAS__H__
#define __GAME__CANVAS__H__

#include <math.h>
#include "HumanTank.h"
#include "CpuTank.h"
#include "Arrow.h"

class GameCanvas : public scv::Canvas {

private:
   const static int tanks_size = 4;
   
   bool paused;
   char allDead;
   float sky[3], terrain[3];
   int difficulty, terrainHeight; 
   scv::Point aim;
   Tank *tanks[tanks_size];
   Arrow *arrows[tanks_size]; //cada tanque só pode lançar uma flecha até ela morrer

public:
   GameCanvas(const scv::Point p1, const scv::Point p2);
   int getDifficulty(void);
   void setDifficulty(int value);
   void setPaused(bool paused);
   void resetGame(void);
   void render(void);
   void update(void);
   void onMouseHold(const scv::MouseEvent &evt);
   void onMouseClick(const scv::MouseEvent &evt);
   void onMouseUp(const scv::MouseEvent &evt);
   void onMouseOver(const scv::MouseEvent &evt);
   void onKeyPressed(const scv::KeyEvent &evt);
   void onKeyUp(const scv::KeyEvent &evt);
   ~GameCanvas();
};

#endif //__GAME__CANVAS__H__

#ifndef __HELP__READER__H__
#define __HELP__READER__H__

#include <string>
#include <fstream>
#include <iostream>

class HelpReader {
public:
   static std::string read(char *path);
};

#endif //__HELP__READER__H__

#ifndef __MAIN__FRAME__H__
#define __MAIN__FRAME__H__

class MainFrame : public scv::InternalFrame {
private:
   GameCanvas *game_canvas;
public:
   MainFrame(int width, int height, const std::string &title, GameCanvas *game_canvas);
   void onClose(void);
};

#endif //__MAIN__FRAME__H__

#ifndef __INTERNAL__FRAME__BUTTON__H__
#define __INTERNAL__FRAME__BUTTON__H__

class InternalFrameButton : public scv::Button {
protected:
   scv::InternalFrame *fi;
public:
   InternalFrameButton(const scv::Point p1, const scv::Point p2, const std::string s1, scv::InternalFrame *fi);

   virtual void onMouseClick(const scv::MouseEvent &evt);
};

#endif //__INTERNAL__FRAME__BUTTON__H__

#ifndef __MAIN__BUTTON__H__
#define __MAIN__BUTTON__H__

class MainButton : public InternalFrameButton {
private:
   GameCanvas *game_canvas;
public:
   MainButton(const scv::Point p1, const scv::Point p2, const std::string s1, scv::InternalFrame *fi, GameCanvas *game_canvas);
   void onMouseClick(const scv::MouseEvent &evt);
};

#endif //__MAIN__BUTTON__H__

#ifndef __DIFFICULTY__BUTTON__H__
#define __DIFFICULTY__BUTTON__H__

class DifficultyButton : public scv::Button {
private:
   GameCanvas *game_canvas;
   std::vector<char *> levels;
public:
   DifficultyButton(const scv::Point p1, const scv::Point p2, const std::string s1, GameCanvas *game_canvas);
   void onMouseClick(const scv::MouseEvent &evt);
};

#endif //__DIFFICULTY__BUTTON__H__

#ifndef __RESET__BUTTON__H__
#define __RESET__BUTTON__H__

class ResetButton : public scv::Button {
private:
   GameCanvas *game_canvas;
public:
   ResetButton(const scv::Point p1, const scv::Point p2, const std::string s1, GameCanvas *game_canvas);
   void onMouseClick(const scv::MouseEvent &evt);
};

#endif //__RESET__BUTTON__H__

#endif //__WIDGET_H__
