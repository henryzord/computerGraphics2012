/**
Henry Cagnini
201010352
*/

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SCV/SCV.h>
#include "Widget.h"

class Application : public scv::Kernel {
public:
   static const int s_defaultWindowWidth = 1024;
   static const int s_defaultWindowHeight = 500;

   Application(void);
   virtual ~Application(void);

   void init(void);
   virtual void onSizeChange(void);

protected:
   scv::Panel *_mainPanel;
};

#endif //__APPLICATION_H__
