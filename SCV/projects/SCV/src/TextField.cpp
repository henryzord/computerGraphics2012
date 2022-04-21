#include "stdafx.h"
#include "TextField.h"
#include "Kernel.h"
#include "Keyboard.h"
#include "StaticLabel.h"

namespace scv {

TextField::TextField(const scv::Point &p1, unsigned int width, const std::string &str) : TextBox(p1, width, str) {
   _isVResizable = false;
   _filter.allowAll();
   _currChar    = -1;
   _selectStart = 0;
   _selectEnd   = 0;

   refreshText();

   _type = TEXTFIELD;

   setMaximumSize(Point(-1, getPreferredSize().y));

   createTexture();
}

void TextField::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static Cursor *cursor = Cursor::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false) return;

   Point currPosition = getAbsolutePosition();
   
   _cTexture->enable();
   scheme->applyColor(ColorScheme::TEXTFIELD);
      _cTexture->display(currPosition.x, currPosition.y, 1, getWidth(), getHeight());
      _cTexture->display(currPosition.x + 1, currPosition.y + 1, 0, getWidth() - 2, getHeight() - 2);
   _cTexture->disable();

   scissor->pushScissor(Scissor::Info(currPosition.x + 3, kernel->getHeight() - (getHeight() + currPosition.y), getWidth() - 6, getHeight()));
   StaticLabel::display(currPosition.x + s_borderWidth / 2 - _deslocString, currPosition.y + 1 + s_borderHeight, 
      _str, _selectStart, _selectEnd, scheme->getColor(ColorScheme::TEXT));
   scissor->popScissor();

   if (isFocused() && _receivingCallbacks) {
      cursor->display(Point (currPosition.x + (s_borderWidth / 2 - 1) + _deslocCursor, currPosition.y + (s_borderHeight - 1)));
   } else {
      _deslocString =  0;
      _selectStart  =  0;
      _selectEnd    =  0;
   }
}

void TextField::refreshText(void) {
   static FontTahoma *font = FontTahoma::getInstance();
   static Kernel *kernel = Kernel::getInstance();

   if (_currChar == -1) {
      _deslocString = 0;
      _deslocCursor = 0;
      return;
   }

   _deslocCursor = font->getStringLength(_str.substr(0, _currChar + 1)) - _deslocString;

   if (font->getStringLength(_str) < (getWidth()-s_borderWidth)) {
      _deslocString = 0;
      _deslocCursor = font->getStringLength(_str.substr(0,_currChar + 1));
   }

   if (_deslocCursor > getWidth() - s_borderWidth) {
      _deslocString = font->getStringLength(_str.substr(0,_currChar + 1)) - (getWidth()-s_borderWidth);
      _deslocCursor = font->getStringLength(_str.substr(0,_currChar + 1)) - _deslocString;
   }

   if (_deslocCursor < 0) {
      if (_currChar + 1 >= 6) {
         _deslocString -= font->getStringLength(_str.substr(_currChar - 5, 6));
      } else {
         _deslocString = 0;
      }
      _deslocCursor = font->getStringLength(_str.substr(0, _currChar + 1)) - _deslocString;
   }
}

void TextField::processMouse(const scv::MouseEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();
   static FontTahoma *font = FontTahoma::getInstance();
   static Cursor *cursor = Cursor::getInstance();

   Component::processMouse(evt);

   if(!_receivingCallbacks) return;

   if (!isEditable()) return;

   if (isInside(evt.getPosition()) && kernel->requestMouseUse(this)) {
	   cursor->setCursor(kernel->glfwWindow, GLFW_IBEAM_CURSOR);
   }
   if ((evt.getState() == MouseEvent::CLICK || evt.getState() == MouseEvent::HOLD) && isFocused()) {
      cursor->cursorInMovement();
      int size = 0, menor = getWidth(), menorDesloc = 0, index = 0;
      index = (evt.getPosition().x-getAbsolutePosition().x);
      for (int i = 0 ; i <= _str.size() ; i++) {
         size = abs(font->getStringLength(_str.substr(0,i)) - (index + _deslocString));
         if (size < menor) {
            menor = size;
            menorDesloc = i;
         }
      }
      _currChar = menorDesloc - 1;

      if (evt.getState() == MouseEvent::CLICK) {
         _selectStart = _currChar;
         _selectEnd = _currChar;
      }

      if (isFocused()) {
         if (evt.getState() == MouseEvent::HOLD) {
            _selectEnd = _currChar;
         }
      }

      _isDragging = false;
      refreshText();
   }

   //if (isDragging())
	//   cursor->setGlutCursor(GLUT_CURSOR_CYCLE);
		

   if (evt.getPosition() >= getAbsolutePosition() && evt.getPosition() <= (getSize() + getAbsolutePosition()) && getParentScissor().isInside(evt.getInversePosition())) {
      if (evt.doubleClick()) {

         if (_currChar==_str.size()-1 || _str.size()==0 || _currChar==-1)
            return;

         _selectStart = _currChar;
         _selectEnd   = _currChar;
         while (_str[_selectStart+1]!=' ' && _selectStart!=(-1))
            _selectStart--;
         if (_str[_selectStart+1]==' ')
            _selectStart++;
         while (_str[_selectEnd]!=' ' && _selectEnd!=_str.size()-1)
            _selectEnd++;
         if (_str[_selectEnd]==' ')
            _selectEnd--;
         _currChar = _selectEnd;
      }

   }
}

void TextField::processKey(const scv::KeyEvent &evt) {

	static Kernel *kernel = Kernel::getInstance();
	static FontTahoma *font = FontTahoma::getInstance();
	static Cursor *cursor = Cursor::getInstance();

	if (!isEditable()) return;

	if (!isFocused()) return;

    Component::processKey(evt);

    if(!_receivingCallbacks) return;

    //if (!_filter.checkFilter(evt.keycode) && !evt.special) return;

	//@afrasson
    /*if (evt.state == KeyEvent::UP) {
        onKeyUp(evt);
        return;
    }
    onKeyPressed(evt);*/

	onKey(evt);
	if (evt.state == KeyEvent::RELEASE)
		return;
	
    cursor->cursorInMovement();

    /*if (evt.keycode >= 33 && evt.keycode <= 126 && !evt.special) {
        if (hasSelectedText()) {
        removeSelectedText();
        }
        if (cursor->isInsertActive()) {
        if ( (_currChar + 1) > static_cast<int> (_str.size()-1)) {
            _str.insert(_currChar+1,1,static_cast<char>(evt.keycode));
        } else {
            _str[_currChar + 1] = static_cast<char>(evt.keycode);
        }
        } else {
        _str.insert(_currChar + 1,1,static_cast<char>(evt.keycode));
        }
        _currChar++;
        refreshText();
        onStringChange();
        return;
    }*/
	std::string clipBoard;
    switch (evt.keycode) 
	{

	// CTRL+V
	case GLFW_KEY_V:
	{
		if (evt.modifiers != GLFW_MOD_CONTROL)
			break;

		if (hasSelectedText())
			removeSelectedText();
		//_str.insert(_currChar + 1, kernel->getClipBoardString());
		//_currChar += kernel->getClipBoardString().size();
		clipBoard = glfwGetClipboardString(kernel->glfwWindow);
		_str.insert(_currChar + 1, clipBoard);
		_currChar += clipBoard.size();
		onStringChange();
		break;
	}
	// CTRL+C
	case GLFW_KEY_C:
	{
		if (evt.modifiers != GLFW_MOD_CONTROL)
			break;

		if (hasSelectedText()) {
			if (_selectStart > _selectEnd)
				std::swap(_selectStart, _selectEnd);
			//kernel->setClipBoardString(_str.substr(_selectStart + 1, _selectEnd - _selectStart));
			glfwSetClipboardString(kernel->glfwWindow, _str.substr(_selectStart + 1, _selectEnd - _selectStart).c_str());
		}
		break;
	}
	// CTRL+X
	case GLFW_KEY_X:
	{
		if (evt.modifiers != GLFW_MOD_CONTROL)
			break;

		if (hasSelectedText()) {
			if (_selectStart > _selectEnd)
				std::swap(_selectStart, _selectEnd);
			//kernel->setClipBoardString(_str.substr(_selectStart + 1, _selectEnd - _selectStart));
			glfwSetClipboardString(kernel->glfwWindow, _str.substr(_selectStart + 1, _selectEnd - _selectStart).c_str());
			removeSelectedText();
			onStringChange();
		}
		break;
	}
	// CTRL+A
	case GLFW_KEY_A:
	{
		if (evt.modifiers != GLFW_MOD_CONTROL)
			break;

		_selectStart = -1;
		_selectEnd = _str.size() - 1;
		_currChar = _str.size() - 1;
		break;
	}

    //case GLUT_KEY_LEFT:
	case GLFW_KEY_LEFT:
		if (evt.modifiers == GLFW_MOD_SHIFT) {
        if (_currChar>=0) {
            if (!hasSelectedText()) {
                _selectStart = _currChar;
                _currChar--;
                _selectEnd = _currChar;
            } else {
                _currChar--;
                _selectEnd = _currChar;
            }
        }
		}
		else if (evt.modifiers == (GLFW_MOD_SHIFT | GLFW_MOD_CONTROL)) {

        } else {
        if (_currChar > (-1))
            _currChar--;
        removeSelection();
        }
        break;

	case GLFW_KEY_RIGHT:
		if (evt.modifiers == GLFW_MOD_SHIFT) {
        if (_currChar < static_cast<int> (_str.size()-1)) {
            if (!hasSelectedText()) {
                _selectStart = _currChar;
                _currChar++;
                _selectEnd = _currChar;
            } else {
                _currChar++;
                _selectEnd = _currChar;
            }
        }
		}
		else if (evt.modifiers == (GLFW_MOD_SHIFT | GLFW_MOD_CONTROL)) {

        } else {
        if (_currChar < static_cast<int> (_str.size()-1))
            _currChar++;
        removeSelection();
        }
        break;

	case GLFW_KEY_HOME:
		if (evt.modifiers == GLFW_MOD_SHIFT) {
        if (!hasSelectedText()) {
            _selectStart = _currChar;
            _currChar = -1;
            _selectEnd = _currChar;
        } else {
            _currChar = -1;
            _selectEnd = _currChar;
        }
		}
		else if (evt.modifiers == GLFW_MOD_CONTROL) {
        _currChar = -1;
        removeSelection();
		}
		else if (evt.modifiers == (GLFW_MOD_SHIFT | GLFW_MOD_CONTROL)) {
        if (!hasSelectedText()) {
            _selectStart = _currChar;
            _currChar = -1;
            _selectEnd = _currChar;
        } else {
            _currChar = -1;
            _selectEnd = _currChar;
        }
        } else {
        _currChar = -1;
        removeSelection();
        }
        break;

	case GLFW_KEY_END:
		if (evt.modifiers == GLFW_MOD_SHIFT) {
        if (!hasSelectedText()) {
            _selectStart = _currChar;
            _currChar = _str.size()-1;
            _selectEnd = _currChar;
        } else {
            _currChar = _str.size()-1;
            _selectEnd = _currChar;
        }
		}
		else if (evt.modifiers == GLFW_MOD_CONTROL) {
        removeSelection();
        _currChar = _str.size()-1;
		}
		else if (evt.modifiers == (GLFW_MOD_SHIFT | GLFW_MOD_CONTROL)) {
        if (!hasSelectedText()) {
            _selectStart = _currChar;
            _currChar = _str.size()-1;
            _selectEnd = _currChar;
        } else {
            _currChar = _str.size()-1;
            _selectEnd = _currChar;
        }
        } else {
        _currChar = _str.size()-1;
        removeSelection();
        }
        break;


	case GLFW_KEY_BACKSPACE:
        if (hasSelectedText()) {
        removeSelectedText();
        onStringChange();
        } else if (_currChar > -1) {
        _str.erase(_currChar,1);
        _currChar--;
        onStringChange();
        }
        break;

	/*case GLFW_KEY_SPACE:
        if (hasSelectedText()) {
			removeSelectedText();
        }
        _str.insert(_currChar+1," ");
        _currChar++;
        onStringChange();
        break;*/
	
	case GLFW_KEY_DELETE:
        if (hasSelectedText()) {
        removeSelectedText();
        onStringChange();
        } else if (_currChar < static_cast<int> (_str.size()-1)) {
        _str.erase(_currChar + 1,1);
        onStringChange();
        }
        break;
    }
	//@afrasson
    refreshText();
}

void TextField::selectLine(int line) {
   selectAll();
}

void TextField::setString(const std::string& str) {
   if (_currChar > str.size() - 1)
      _currChar = str.size() - 1;
   _selectStart = _selectEnd = 0;
   TextBox::setString(str);
   refreshText();
}

void TextField::setHeight(const int height) {
   /*none*/
}

} // namespace scv

