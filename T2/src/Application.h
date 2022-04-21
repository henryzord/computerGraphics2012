/**
Henry Cagnini
201010352
*/

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SCV/SCV.h>

#include "Widget.h"

class Application : public scv::Kernel {
private:
protected:
   static const int s_defaultWindowWidth = 1000; 
   static const int s_defaultWindowHeight = 500;
   scv::Panel *_mainPanel;

public:

   ///////////////////////////////////////////////////////////
   Application(void);
   virtual ~Application(void);
   ///////////////////////////////////////////////////////////

   void init(void);

   //SCVCallbacks
   ///////////////////////////////////////////////////////////
   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold (const scv::MouseEvent &evt);
   virtual void onMouseOver (const scv::MouseEvent &evt);
   virtual void onMouseUp   (const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp     (const scv::KeyEvent &evt);

   virtual void onSizeChange(void);
   virtual void onPositionChange(void);
   ///////////////////////////////////////////////////////////
};

#endif //__APPLICATION_H__
