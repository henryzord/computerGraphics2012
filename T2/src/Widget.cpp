/**
Henry Cagnini
201010352
*/

#include "Widget.h"

GameCanvas::GameCanvas(const scv::Point p1, const scv::Point p2) : scv::Canvas(p1, p2) {
   sky[0] = 0.6f;
   sky[1] = 0.85f;
   sky[2] = 0.91f;
      
   terrain[0] = 0.77f;
   terrain[1] = 0.92f;
   terrain[2] = 0.30f;

   terrainHeight = getHeight()/5;

   difficulty = 1;
   for(int n = 0; n < tanks_size; n++) {
      tanks[n] = NULL;
   }
   paused = false;
   resetGame();
}

int GameCanvas::getDifficulty(void) {
   return difficulty;
}

void GameCanvas::setDifficulty(int value) {
   if(value > 0 && value < tanks_size) {
      difficulty = value;
      resetGame();
   }
}

void GameCanvas::setPaused(bool paused) {
   this->paused = paused;
}

void GameCanvas::resetGame(void) {
   for(int n = 0; n < tanks_size; n++) {
      if(tanks[n] != NULL) {
         delete tanks[n];
      }
   }
   int c_width = getWidth(), next = c_width - Tank::tire_length;
      
   tanks[0] = new HumanTank((scv::Canvas*)this, scv::Color4f(1, 0, 0), scv::Point(Tank::tire_length, getHeight() - terrainHeight-Tank::tire_length));
   //fazer um laço nisso aqui depois!
   tanks[1] = new CpuTank((scv::Canvas*)this, scv::Color4f(0, 0, 1), scv::Point(next - (rand() % (c_width/4)), getHeight() - terrainHeight-Tank::tire_length), (HumanTank*)tanks[0]); 
   next -= c_width/4;
   tanks[2] = new CpuTank((scv::Canvas*)this,  scv::Color4f(0, 1, 0), scv::Point(next - (rand() % (c_width/4)), getHeight() - terrainHeight-Tank::tire_length), (HumanTank*)tanks[0]); 
   next -= c_width/4;
   tanks[3] = new CpuTank((scv::Canvas*)this,  scv::Color4f(1, 1, 0), scv::Point(next - (rand() % (c_width/4)), getHeight() - terrainHeight-Tank::tire_length), (HumanTank*)tanks[0]); 

   allDead = false;
}
      
void GameCanvas::render(void) {
   //limpa a tela
   clear(sky[0], sky[1], sky[2]);
   clear(terrain[0], terrain[1], terrain[2]);
   //desenha o céu
   color(sky[0], sky[1], sky[2]);
   rectFill(0,0,getWidth(), getHeight());
   //chama a render dos objetos da tela
   for(int n = 0; n <= difficulty; n++) {
      tanks[n]->render();
   }
   if(allDead) {
      color(1, 1, 1);
      char *winner = "YOU WIN!";
      text((getWidth()/2) - strlen(winner), getHeight()/2, winner);
   } else {
      if(!tanks[0]->active) {
         color(0, 0, 0);
         char *loser = "GAME OVER";
         text((getWidth()/2) - strlen(loser), getHeight()/2, loser);
      }
   }
   //desenha o chão
   color(terrain[0], terrain[1], terrain[2]);
   rectFill(0, getHeight()-terrainHeight, getWidth(), getHeight());
   color(0,0,0);
   line(0, getHeight()-terrainHeight, getWidth(), getHeight()-terrainHeight);

   //desenha a mira
   color(0,0,0);
   circle(aim.x, aim.y, 5, 100);
   line(aim.x, aim.y-5, aim.x, aim.y+5);
   line(aim.x-5, aim.y, aim.x+5, aim.y);
}
   
void GameCanvas::update(void) {
   if(!paused) {
      if(tanks[0]->active && !allDead) {
         tanks[0]->update();
         arrows[0] = tanks[0]->getArrow();
         char sample = 1;
         for(int n = 1; n <= difficulty; n++) {
            tanks[n]->update();
            arrows[n] = tanks[n]->getArrow();
         
            tanks[n]->collides(arrows[0]);
            arrows[n]->collides(tanks[0]); //tirar depois
            sample *= !(tanks[n]->active);
            allDead = sample;
         }
      }
   }
}

void GameCanvas::onMouseHold(const scv::MouseEvent &evt) {
   if(!paused && !allDead) {
      for(int n = 0; n <= difficulty; n++) {
         tanks[n]->onMouseHold(evt);
      }
   }
}

void GameCanvas::onMouseClick(const scv::MouseEvent &evt) {
   if(!paused && !allDead) {
      for(int n = 0; n <= difficulty; n++) {
         tanks[n]->onMouseClick(evt);
      }
   }
}

void GameCanvas::onMouseUp(const scv::MouseEvent &evt) {
   if(!paused && !allDead) {
      for(int n = 0; n <= difficulty; n++) {
         tanks[n]->onMouseUp(evt);
      }
   }
}

void GameCanvas::onMouseOver(const scv::MouseEvent &evt) {
   aim = evt.getPosition();
   if(!paused && !allDead) {
      for(int n = 0; n <= difficulty; n++) {
         tanks[n]->onMouseOver(evt);
      }
   }   
}

void GameCanvas::onKeyPressed(const scv::KeyEvent &evt) {
   if(!paused && !allDead) {
      for(int n = 0; n <= difficulty; n++) {
         tanks[n]->onKeyPressed(evt);
      }
   }
}
void GameCanvas::onKeyUp(const scv::KeyEvent &evt) {
   if(!paused && !allDead) {
      for(int n = 0; n <= difficulty; n++) {
         tanks[n]->onKeyUp(evt);
      }
   }
}

GameCanvas::~GameCanvas() {
   //deleta todos os objetos do jogo
   for(int n = 0; n < tanks_size; n++) {
      delete tanks[n];
   }
}

std::string HelpReader::read(char *path) {
   std::ifstream help;
   help.open(path);
   if(help.fail()) {
      return std::string("Erro lendo ajuda. O arquivo de ajuda esta na pasta do executavel?");
   } else {
      int length;
      char *buffer;
      help.seekg(0, std::ios::end);
      length = (int)help.tellg();
      help.seekg(0, std::ios::beg);
      buffer = new char [length];
      help.read(buffer,length);
      std::string helpstr(buffer);
      help.close();
      return helpstr;
   }
}

MainFrame::MainFrame(int width, int height, const std::string &title, GameCanvas *game_canvas) : scv::InternalFrame(width, height, title) {
   this->game_canvas = game_canvas;
}
void MainFrame::onClose(void) {
   game_canvas->setPaused(false);
}

InternalFrameButton::InternalFrameButton(const scv::Point p1, const scv::Point p2, const std::string s1, scv::InternalFrame *fi) : scv::Button(p1, p2, s1) {
   this->fi = fi;
   this->fi->setVisible(false);
}

void InternalFrameButton::onMouseClick(const scv::MouseEvent &evt) {
   this->fi->setVisible(true);
}

MainButton::MainButton(const scv::Point p1, const scv::Point p2, const std::string s1, scv::InternalFrame *fi, GameCanvas *game_canvas) : InternalFrameButton(p1, p2, s1, fi) {
   this->game_canvas = game_canvas;
}
void MainButton::onMouseClick(const scv::MouseEvent &evt) {
   game_canvas->setPaused(true);
   this->fi->setVisible(true);
}

DifficultyButton::DifficultyButton(const scv::Point p1, const scv::Point p2, const std::string s1, GameCanvas *game_canvas) : scv::Button(p1, p2, s1) {
   this->game_canvas = game_canvas;

   levels.push_back("Facil");
   levels.push_back("Medio");
   levels.push_back("Dificil");
}
void DifficultyButton::onMouseClick(const scv::MouseEvent &evt) {
   int new_dif = (game_canvas->getDifficulty() % 3) + 1;
   game_canvas->setDifficulty(new_dif);
   this->setString(levels.at(new_dif-1));
}

ResetButton::ResetButton(const scv::Point p1, const scv::Point p2, const std::string s1, GameCanvas *game_canvas) : scv::Button(p1, p2, s1) {
   this->game_canvas = game_canvas;
}
void ResetButton::onMouseClick(const scv::MouseEvent &evt) {
   game_canvas->resetGame();
}

