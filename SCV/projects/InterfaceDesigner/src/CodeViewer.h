#ifndef __CODE_VIEWER_H__
#define __CODE_VIEWER_H__

#include "GroupPanelWrapper.h"

class CodeViewer : public scv::Panel {
public:
   ///////////////////////////////////////////////////////////
   CodeViewer(void);
   virtual ~CodeViewer(void);
   ///////////////////////////////////////////////////////////

   void display(void);

   void setText(std::string text);

protected:
   ///////////////////////////////////////////////////////////
   scv::TextBox *_textbox;
   scv::MenuBar *_menuBar;
   GroupObjectWrapper *_wrappedFrame;
   scv::Group *hGroupLayout, *vGroupLayout;
};

#endif //__CODE_VIEWER_H__