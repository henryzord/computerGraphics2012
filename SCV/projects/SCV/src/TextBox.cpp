#include "stdafx.h"
#include "TextBox.h"
#include "Kernel.h"
#include "Keyboard.h"
#include "util.h"
#include "StaticLabel.h"

namespace scv {

TextBox::TextBox(const scv::Point &p, unsigned int width, unsigned int lines, const std::string &str) :
Component(p, Point(p.x + width, p.y + s_lineSpacing * lines + s_borderHeight + 1)) {
    _str = str;
    _isHResizable = _isVResizable = true;
    _firstLine = 0;
    _currChar = -1;
    _selectStart = 0;
    _selectEnd = 0;
    _nLines = lines;
    refreshText();
    _type = TEXTBOX;

    _editable = true;

    createTexture();
}

TextBox::TextBox(const scv::Point &p, unsigned int width, const std::string &str) :
Component(p, Point(p.x + width, p.y + s_lineSpacing + s_borderHeight + 1)) {
    _str = str;
    _isHResizable = _isVResizable = true;
    _firstLine = 0;
    _currChar = -1;
    _selectStart = 0;
    _selectEnd = 0;
    _nLines = 1;
    refreshText();
    _type = TEXTBOX;

    _editable = true;

    createTexture();
}

TextBox::TextBox(const scv::Point &p1, const scv::Point &p2, const std::string &str) :
Component(p1, Point(p2.x, p2.y + s_lineSpacing + s_borderHeight + 1)) {
    _str = str;
    _isHResizable = _isVResizable = true;
    _firstLine = 0;
    _currChar = -1;
    _selectStart = 0;
    _selectEnd = 0;

    setHeight(p2.y - p1.y);
    setWidth(p2.x - p1.x);
    _type = TEXTBOX;

    _editable = true;

    createTexture();
}

Point TextBox::getInternalSize() {
   Point p;
   p.y = getRelativePosition().y + getHeight() - s_lineSpacing - s_borderHeight;
   p.x = getRelativePosition().x + getWidth();

   return p;
}

void TextBox::display(void) {
    static Kernel *kernel = Kernel::getInstance();
    static Cursor *cursor = Cursor::getInstance();
    static Scissor *scissor = Scissor::getInstance();
    static ColorScheme *scheme = ColorScheme::getInstance();

    if (_cTexture == NULL || _isVisible == false) return;

    Point currPosition = getAbsolutePosition();

    _cTexture->enable();
    scheme->applyColor(ColorScheme::TEXTFIELD);
    _cTexture->display(currPosition.x, currPosition.y, 1, getWidth(), getHeight());
    _cTexture->display(currPosition.x + 1, currPosition.y + 1, 0, getWidth() - 2, getHeight() - 2);
    _cTexture->disable();

    scissor->pushScissor(Scissor::Info(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y) + 2, getWidth(), getHeight() - 4));
    for (int i = _firstLine; i < (_nLines+_firstLine) && i < (_lineIndex.size() - 1); i++)
        StaticLabel::display(currPosition.x + s_borderWidth / 2 , currPosition.y + 1 + s_borderHeight + (i - _firstLine) * s_lineSpacing, 
        _str.substr(_lineIndex[i], _lineIndex[i + 1] - _lineIndex[i]), _selectStart - _lineIndex[i], _selectEnd - _lineIndex[i], scheme->getColor(ColorScheme::TEXT));


    if (isFocused() && _receivingCallbacks) {
        cursor->display(Point(currPosition.x + (s_borderWidth / 2 - 1) + _desloc.x, currPosition.y + (s_borderHeight-1) + ((_desloc.y - _firstLine) * s_lineSpacing)));
    } else {
        _currChar     = -1;
        _selectStart  =  0;
        _selectEnd    =  0;
        refreshCursor();
    }

    scissor->popScissor();
}

void TextBox::createTexture(void) {
    Kernel *kernel = Kernel::getInstance();
    if ((_cTexture = kernel->getWidgetTexture(TEXTBOX)) != NULL) return;

    // create texture object
    _cTexture = new ComponentTexture(2, 2);
    kernel->setWidgetTexture(TEXTBOX, _cTexture);

    _cTexture->setTextureEnvMode(GL_MODULATE);

    // middle
    _cTexture->addTexture(Point(0,0), MatrixTemplate<ColorRGBA>(1, 1, ColorRGBA(255,255,255,255)));

    // lines
    _cTexture->addTexture(Point(1,0),  MatrixTemplate<ColorRGBA>(1, 1, ColorRGBA(100,100,100,255)));

    _cTexture->createTexture();
}


void TextBox::refreshCursor(void) {
    static Kernel *kernel = Kernel::getInstance();
    static FontTahoma *font = FontTahoma::getInstance();

    if(isFocused()){
        int translateLine = 0;

        if (_str.size()==0 || _currChar == -1) {
            _desloc.x = 0;
            _desloc.y = 0;
            _firstLine = 0;
            return;
        }

        for (int i = 0 ; i < _lineIndex.size()-1 ; i++) {
            if (_currChar+1 > _lineIndex[i] && _currChar+1 <= _lineIndex[i+1]) {
                translateLine = i;
                break;
            }
        }

        _desloc.x = font->getStringLength(_str.substr(_lineIndex[translateLine],_currChar-_lineIndex[translateLine]+1));
        _desloc.y = translateLine;

        if (((_desloc.y + 1) - _firstLine) > _nLines) {
            _firstLine = (_desloc.y + 1) - _nLines;
        } else if ((_desloc.y - _firstLine) < 0) {
            _firstLine = _desloc.y;
        }
    }
}


void TextBox::refreshText(void) {
    static FontTahoma *font = FontTahoma::getInstance();

    unsigned int translateLine = 0;
    unsigned int firstCharLine = 0;
    unsigned int lastCharLine = 0;

    _lineIndex.clear();
    _lineIndex.push_back(0);

    for (int i = 0 ; i < _str.size() ; i++) {
        lastCharLine = i;
        if (font->getStringLength(_str.substr(firstCharLine,(lastCharLine-firstCharLine)+1)) > getWidth()-s_borderWidth || _str[i]=='\n') {
            firstCharLine = i;
            lastCharLine = i;
            translateLine++;
            _lineIndex.push_back(i);
        }
    }

    _lineIndex.push_back(_str.size());

    if(isEditable())
        refreshCursor();
}

void TextBox::removeSelectedText(void) {
    if (hasSelectedText()) {
        if (_selectStart>_selectEnd)
            std::swap(_selectStart,_selectEnd);
        _str.erase(_selectStart+1,_selectEnd-_selectStart);
        _currChar = _selectStart;
        _selectEnd = _selectStart;
        refreshText();
    }
}


void TextBox::removeSelection(void) {
    if (hasSelectedText()) {
        _selectEnd = _selectStart;
        refreshCursor();
    }
}

void TextBox::upLine(void) {
    static FontTahoma *font = FontTahoma::getInstance();
    int desloc = 0;
    int menorDesloc = 0;
    int menor = getWidth();
    int size = 0;

    for (int i = _lineIndex[_desloc.y - 1] , desloc = 0 ; i <= _lineIndex[_desloc.y] ; i++ , desloc++) {
        size = abs(font->getStringLength(_str.substr(_lineIndex[_desloc.y - 1],desloc)) - _desloc.x);
        if (size < menor) {
            menor = size;
            menorDesloc = desloc;
        }
    }
    _currChar = _lineIndex[_desloc.y-1] + menorDesloc - 1;
    if (menorDesloc==0){
        _currChar++;
    }
}

void TextBox::downLine(void) {
    static FontTahoma *font = FontTahoma::getInstance();
    int desloc = 0;
    int menorDesloc = 0;
    int menor = getWidth();
    int size = 0;

    for (int i = _lineIndex[_desloc.y + 1] , desloc = 0 ; i <= _lineIndex[_desloc.y + 2] ; i++ , desloc++) {
        size = abs(font->getStringLength(_str.substr(_lineIndex[_desloc.y + 1],desloc)) - _desloc.x);
        if (size < menor) {
            menor = size;
            menorDesloc = desloc;
        }
    }
    _currChar = _lineIndex[_desloc.y+1] + menorDesloc - 1;
    if (_currChar == _lineIndex[_desloc.y+1]-1)
        _currChar++;
}

void TextBox::processMouse(const scv::MouseEvent &evt) {
    static Kernel *kernel = Kernel::getInstance();
    static Cursor *cursor = Cursor::getInstance();
    static FontTahoma *font = FontTahoma::getInstance();

    Component::processMouse(evt);

    if (_isResizing)
        refreshText();

    if(!_receivingCallbacks) return;
    _refreshCursor = false;

    if (!isEditable())
    {
        if (isFocused()) {
            if (evt.getState() == MouseEvent::WHEELDOWN) {
                if (_str.size() > _lineIndex[_firstLine+1] && _lineIndex.size() > _firstLine+3){//De alguma maneira isso faz sentido
                    _firstLine++;
                    return;
                }
            }
            if (evt.getState() == MouseEvent::WHELLUP) {
                if (_firstLine>0) {
                    _firstLine--;
                    return;
                }
            }
        }
        return;
    }
    
    if (evt.getPosition() >= getAbsolutePosition() && evt.getPosition() < (getSize() + getAbsolutePosition()) && getParentScissor().isInside(evt.getInversePosition()) &&
        kernel->requestMouseUse(this)) {
		cursor->setCursor(kernel->glfwWindow, GLFW_IBEAM_CURSOR);
    }

    if (isFocused()) {
        if (evt.getState() == MouseEvent::WHEELDOWN) {
            if (_str.size()>_lineIndex[_firstLine+1]) {
                _firstLine++;
                return;
            }
        }
        if (evt.getState() == MouseEvent::WHELLUP) {
            if (_firstLine>0) {
                _firstLine--;
                return;
            }
        }
    }
    if ((evt.getState() == MouseEvent::CLICK || evt.getState() == MouseEvent::HOLD) && isFocused()) {
        cursor->cursorInMovement();
        int size = 0, menor = getWidth(), menorDesloc = 0;
        Point index(0,0);
        index.y = _firstLine + ((evt.getPosition().y-(getAbsolutePosition().y+s_borderHeight))/s_lineSpacing);
        if (index.y >= _lineIndex.size()-1) {
            _currChar = _str.size()-1;
            if (evt.getState() == MouseEvent::CLICK) {
                _selectStart = _currChar;
            }
            _selectEnd = _currChar;
            refreshCursor();
            return;
        }
        index.x = (evt.getPosition().x-getAbsolutePosition().x);
        for (int i = _lineIndex[index.y] , desloc = 0 ; i <= _lineIndex[index.y + 1] ; i++ , desloc++) {
            size = abs(font->getStringLength(_str.substr(_lineIndex[index.y],desloc)) - index.x);
            if (size < menor) {
                menor = size;
                menorDesloc = desloc;
            }
        }
        _currChar = _lineIndex[index.y] + menorDesloc - 1;


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
        _refreshCursor = true;
    }

	//if (isDragging())
		//cursor->setGlutCursor(GLUT_CURSOR_CYCLE);


    if (isFocused() && evt.getState() == MouseEvent::HOLD) {
        if (evt.getPosition().y < getAbsolutePosition().y)
            if (_firstLine>0)
                _firstLine--;
        if (evt.getPosition().y > getAbsolutePosition().y + getHeight()) {
            if (_str.size()>_lineIndex[_firstLine+1]) {
                _firstLine++;
            }
        }
    }
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
            _refreshCursor = true;
        }
    }
    if (_refreshCursor)
        refreshCursor();
}

void TextBox::processChar(const unsigned int &character, const int &modifier) {
	static Kernel *kernel = Kernel::getInstance();
	static Cursor *cursor = Cursor::getInstance();
	static FontTahoma *font = FontTahoma::getInstance();

	_refreshCursor = false;
	_refreshText = true;

	if (!isEditable()) return;

	if (!isFocused()) return;

	Component::processChar(character, modifier);

	if (!_receivingCallbacks) return;

	//if (!_filter.checkFilter(evt.keycode) && !evt.special)
	//	return;

	//@afrasson
	/*if (evt.state == KeyEvent::UP) {
	onKeyUp(evt);
	return;
	}

	onKeyPressed(evt);*/

	//onKey(evt);
	//if (evt.state == KeyEvent::RELEASE)
	//	return;
	//@afrasson

	cursor->cursorInMovement();

		if (hasSelectedText())
			removeSelectedText();
		if (cursor->isInsertActive()) {
			if ((_currChar + 1) > static_cast<int> (_str.size() - 1)) {
				_str.insert(_currChar + 1, 1, static_cast<char>(character));
			}
			else {
				_str[_currChar + 1] = static_cast<char>(character);
			}
		}
		else {
			_str.insert(_currChar + 1, 1, static_cast<char>(character));
		}
		_currChar++;
		refreshText();
		onStringChange();
		return;

	if (_refreshText) {
		refreshText();
		onStringChange();
	}
	else if (_refreshCursor) {
		refreshCursor();
	}
}

void TextBox::processKey(const scv::KeyEvent &evt) {
    static Kernel *kernel = Kernel::getInstance();
    static Cursor *cursor = Cursor::getInstance();
    static FontTahoma *font = FontTahoma::getInstance();

    _refreshCursor = false;
    _refreshText = true;

    if (!isEditable()) return;

	if (!isFocused()) return;

    Component::processKey(evt);

    if(!_receivingCallbacks) return;

	//@afrasson
    //if (!_filter.checkFilter(evt.keycode) && !evt.special)
    //    return;

	
    /*if (evt.state == KeyEvent::UP) {
        onKeyUp(evt);
        return;
    }

    onKeyPressed(evt);*/

	onKey(evt);
	if (evt.state == KeyEvent::RELEASE)
		return;

    cursor->cursorInMovement();

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
		//clipBoard = kernel->getClipBoardString();
		clipBoard = glfwGetClipboardString(kernel->glfwWindow);
		_str.insert(_currChar + 1, clipBoard);
		_currChar += clipBoard.size();
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
			//kernel->setClipBoardString(_str.substr(_selectStart+1,_selectEnd-_selectStart));
			glfwSetClipboardString(kernel->glfwWindow, _str.substr(_selectStart + 1, _selectEnd - _selectStart).c_str());
		}
		_refreshCursor = true;
		_refreshText = false;
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
			//kernel->setClipBoardString(_str.substr(_selectStart+1,_selectEnd-_selectStart));
			glfwSetClipboardString(kernel->glfwWindow, _str.substr(_selectStart + 1, _selectEnd - _selectStart).c_str());
			removeSelectedText();
			return;
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
		_refreshCursor = true;
		_refreshText = false;
		break;
	}

    case GLFW_KEY_LEFT:
		if (evt.modifiers == (GLFW_MOD_SHIFT)) {
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
        _refreshCursor = true;
        _refreshText = false;
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
        _refreshCursor = true;
        _refreshText = false;
        break;

	case GLFW_KEY_UP:
		if (evt.modifiers == GLFW_MOD_SHIFT) {
            if (_desloc.y>0) {
                if (!hasSelectedText()) {
                    _selectStart = _currChar;
                    upLine();
                    _selectEnd = _currChar;
                } else {
                    upLine();
                    _selectEnd = _currChar;
                }
            }
        } else {
            if (_desloc.y>0) {
                upLine();
            }
            removeSelection();
        }
        _refreshCursor = true;
        _refreshText = false;
        break;

	case GLFW_KEY_DOWN:
		if (evt.modifiers == GLFW_MOD_SHIFT) {
            if (!(_lineIndex[_desloc.y+1] == _str.size())) {
                if (!hasSelectedText()) {
                    _selectStart = _currChar;
                    downLine();
                    _selectEnd = _currChar;
                } else {
                    downLine();
                    _selectEnd = _currChar;
                }
            }
        } else {
            if (!(_lineIndex[_desloc.y+1] == _str.size())) {
                downLine();
            }
            removeSelection();
        }
        _refreshCursor = true;
        _refreshText = false;
        break;


    case GLFW_KEY_HOME:
		if (evt.modifiers == GLFW_MOD_SHIFT) {
            if (!hasSelectedText()) {
                if (_str.length() == 0) break;

                _selectStart = _currChar;

                if (_lineIndex[_desloc.y] != (-1) && _str[_lineIndex[_desloc.y]] != '\n')
                    _currChar = _lineIndex[_desloc.y]-1;
                else
                    _currChar = _lineIndex[_desloc.y];

                _selectEnd = _currChar;
            } else {

                if (_lineIndex[_desloc.y] != (-1) && _str[_lineIndex[_desloc.y]] != '\n')
                    _currChar = _lineIndex[_desloc.y]-1;
                else
                    _currChar = _lineIndex[_desloc.y];

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
            _currChar = _lineIndex[_desloc.y];
            removeSelection();
        }
        _refreshCursor = true;
        _refreshText = false;
        break;

	case GLFW_KEY_END:
		if (evt.modifiers == GLFW_MOD_SHIFT) {
            if (!hasSelectedText()) {
                _selectStart = _currChar;
                _currChar = _lineIndex[_desloc.y+1]-1;
                _selectEnd = _currChar;
            } else {
                _currChar = _lineIndex[_desloc.y+1]-1;
                _selectEnd = _currChar;
            }
		}
		else if (evt.modifiers == GLFW_MOD_CONTROL) {
            _currChar = _str.size()-1;
            removeSelection();
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
            _currChar = _lineIndex[_desloc.y+1]-1;
            removeSelection();
        }
        _refreshCursor = true;
        _refreshText = false;
        break;

		
	case GLFW_KEY_BACKSPACE:
        if (hasSelectedText()) {
            removeSelectedText();
            return;
        } else if (_currChar > -1) {
            _str.erase(_currChar,1);
            _currChar--;
        }
        break;

    case GLFW_KEY_DELETE:
        if (hasSelectedText()) {
            removeSelectedText();
            return;
        } else if (_currChar < static_cast<int> (_str.size()-1))
            _str.erase(_currChar+1,1);
        break;

    case GLFW_KEY_ENTER:
        if (hasSelectedText()) {
            removeSelectedText();
            return;
        }
        _str.insert(_currChar+1,1,'\n');
        _currChar++;
        break;

    }
	//@afrasson

    if (_refreshText) {
        refreshText();
        onStringChange();
    } else if (_refreshCursor) {
        refreshCursor();
    }
}

void TextBox::setString(const std::string& str) {
    _currChar = _str.size() - 1;
    _selectStart = _selectEnd = 0;
    _str = str;
    refreshText();
}

void TextBox::selectAll(void) {
    static Kernel *kernel = Kernel::getInstance();

    kernel->requestComponentFocus(this);
    _selectStart = -1;
    _selectEnd   = _str.size()-1;
    _currChar = _str.size()-1;
    refreshCursor();
}

void TextBox::selectLine(int line) {
    static Kernel *kernel = Kernel::getInstance();

    if (_lineIndex.size() > line && line > 0) {
        kernel->requestComponentFocus(this);
        _selectStart = _lineIndex[line-1]-1;
        _selectEnd   = _lineIndex[line]-1;
        _currChar = _lineIndex[line]-1;
        refreshCursor();
    }
}

bool TextBox::hasSelectedText(void) {
    return (_selectStart != _selectEnd);
}

void TextBox::setFilter(TextFilter filter) {
    _filter = filter;
}

void TextBox::setCursorPosition(int position) {
    if (position < getString().size()) {
        _currChar = position;
        refreshText();
    }
}

void TextBox::setWidth(const int width) {
    Component::setWidth(width);
    refreshText();
}

void TextBox::setHeight(const int height) {
    Component::setHeight(height);
    _nLines = (int)(getHeight()/s_lineSpacing);
    refreshText();
}

void TextBox::setEditable(bool editable) {
    _currChar = -1;
    _selectStart = 0;
    _selectEnd = 0;

    _editable = editable;
}

} // namespace scv
