#ifndef __SCV_MOUSE_EVENT_H__
#define __SCV_MOUSE_EVENT_H__

#include "Point.h"

namespace scv {

class MouseEvent {
public:
   enum Button {
	   LEFT = GLFW_MOUSE_BUTTON_LEFT,
	   RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
	   MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
	   NBUTTON
   };
   enum State {
	   UP = GLFW_RELEASE,
	   CLICK = GLFW_PRESS,
      HOLD, 
	  MOTION,
      WHELLUP, 
	  WHEELDOWN
   };

   MouseEvent(void);
   MouseEvent(MouseEvent::Button button, MouseEvent::State state, const Point &location, bool doubleClick = false);

   MouseEvent& operator=(const MouseEvent&rhs);

   Point getPosition(void) const;
   Point getInversePosition(void) const;
   MouseEvent::Button getButton(void) const;
   MouseEvent::State getState(void) const;

   inline bool doubleClick(void) const {
      return _doubleClick;
   }

   MouseEvent operator-(const Point &p) const {
      return MouseEvent(_button, _state, _position - p);
   }

private:
   MouseEvent::Button _button;
   MouseEvent::State _state;
   Point _position;
   bool _doubleClick;
};

} // namespace scv

#endif // __SCV_MOUSE_EVENT_H__