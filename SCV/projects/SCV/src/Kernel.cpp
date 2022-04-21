/*

SCV - Simple Components for Visual
Developed at Federal University of Santa Maria - UFSM
LaCA - Computer Applied Laboratory - Laboratório de Computação Aplicada
webpage: www.inf.ufsm.br/~pozzer/scv
email: pozzer@inf.ufsm.br
2007-2012 

*/

 

#include "stdafx.h"
#include "Kernel.h"

#include "FontTahoma.h"

#include "MenuHolder.h"
#include "InternalFrameHolder.h"
#include "Component.h"

#include "Keyboard.h"
#include "GlslShader.h"

#include "util.h"

#include "FileOpen.h"

#include "Mathematic.h"

#include <algorithm>
#include <cstring>

namespace scv {

const std::string Kernel::s_defaultTitle = "SCV - Simple Components for Visual - http://www-usr.inf.ufsm.br/~pozzer/scv/";
const unsigned int Kernel::s_defaultWidth  = 1280;
const unsigned int Kernel::s_defaultHeight = 720;
const unsigned int Kernel::s_defaultFramesPerSecond = 60;

Kernel::Kernel(void)
	: isRunning(false), _filterType(NEAREST), _allowResizing(true), _reshapeOnNextFrame(false), _focusedComponent(NULL), _contextMenu(NULL), _componentRequestFocus(false)
{
   for (int i = 0; i < Component::NOFWIDGETS; ++i)
      _loadedWidgets[i] = 0;

   Mouse.locked = false;

   _windowTitle = s_defaultTitle;
   FrameRate.fps = s_defaultFramesPerSecond;
   FrameRate.currFps = s_defaultFramesPerSecond;

   Display.currSize[0] = Display.userSize[0] = s_defaultWidth;
   Display.currSize[1] = Display.userSize[1] = s_defaultHeight;

   Display.isFullScreen = false;

   Mouse.clicked = false;
   Mouse.lastButton = MouseEvent::NBUTTON;

   Mouse.lastClickPosition = Point(-1, -1);

   #ifdef _WIN32
      Mouse.doubleClickTime = GetDoubleClickTime();
   #else
      Mouse.doubleClickTime = 500;
   #endif // _WIN32

   Keyboard::getInstance();

   showCopyrights();

   initOpenGL(0, NULL);
   GlslShader::init();

   FrameRate.baseTime = FrameRate.prevTime = FrameRate.currTime = (int)(glfwGetTime() / 1000.0);				// Glut used milliseconds but GLFW uses senconds.
   FrameRate.count = 0;

   Mouse.componentRequestUse = NULL;

   srand((unsigned int)time(NULL));
}

void Kernel::setCallbacks()
{
	// Keyboard
	glfwSetKeyCallback(glfwWindow, cbKeyboard);
	glfwSetCharModsCallback(glfwWindow, cbCharacter);

	// Mouse
	glfwSetCursorPosCallback(glfwWindow, cbCursorPosition);
	glfwSetCursorEnterCallback(glfwWindow, cbCursorEnter);
	glfwSetMouseButtonCallback(glfwWindow, cbMouseButton);
	glfwSetScrollCallback(glfwWindow, cbScroll);

	// Window
	glfwSetWindowCloseCallback(glfwWindow, cbWindowClose);
	glfwSetWindowSizeCallback(glfwWindow, cbWindowSize);
	glfwSetFramebufferSizeCallback(glfwWindow, cbFramebufferSize);
	glfwSetWindowPosCallback(glfwWindow, cbWindowPosition);

	glfwSetWindowRefreshCallback(glfwWindow, cbWindowRefresh);
}
//! Start the SCV event loop. Call this after setting up your form layout to run the GUI.
void Kernel::run(void)
{
	glfwShowWindow(glfwWindow);
	setCallbacks();

	int width, height;
	glfwGetFramebufferSize(glfwWindow, &width, &height);
	Display.framebufferSize[0] = width;
	Display.framebufferSize[1] = height;



	isRunning = true;

	while (!glfwWindowShouldClose(glfwWindow))
	{
		display();
		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();
	}

	glfwTerminate();
}


//! Returns the current contents of the clipboard.
std::string Kernel::getClipBoardString(void) const {
   #ifdef _WIN32
      if (OpenClipboard(NULL)) {
         HANDLE clip = GetClipboardData(CF_TEXT);
         GlobalLock(clip);
         CloseClipboard();
         if (clip == NULL) return std::string("");
         std::string clipBoard = std::string(static_cast<char*>(clip));
         size_t found;
         while (true) {
            found = clipBoard.find((char)(13));
            if (found != std::string::npos) clipBoard.erase(found,1);
            else break;
         }
         return clipBoard;
      } else {
         return std::string("null");
      }
   #else // UNIX
      return std::string("null");
   #endif // _WIN32
}

//! Replaces the clipboard's contents with the string \c strData.
void Kernel::setClipBoardString(const std::string strData) {
   #ifdef _WIN32
      if (OpenClipboard(NULL)) {
         EmptyClipboard();
         HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, strData.size() + 1);
         char *pchData = static_cast<char*>(GlobalLock(hClipboardData));
         strcpy(pchData, LPCSTR(strData.c_str()));
         GlobalUnlock(hClipboardData);
         SetClipboardData(CF_TEXT, hClipboardData);
         CloseClipboard();
      }
   #else // UNIX
   #endif // _WIN32
}

void Kernel::cbError(int error, const char* description)
{
	std::cerr << "Error " << error << description << std::endl;
}

void Kernel::initOpenGL(int argc, char* argv[]) 
{
	glfwSetErrorCallback(cbError);

	// GLFW
	if (!glfwInit()){std::cerr << "Failed to initialize GLFW." << std::endl; exit(-1);}

	// Window
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindow = glfwCreateWindow(s_defaultWidth, s_defaultHeight, _windowTitle.c_str(), NULL, NULL);
	if (!glfwWindow){ std::cerr << "Failed to creat GLFW window." << std::endl; glfwTerminate(); exit(-1); }
	glfwMakeContextCurrent(glfwWindow);

	//setCallbacks();

	FontTahoma::getInstance();
	Cursor::getInstance();
}


//! Resizes the window.
void Kernel::setWindowSize(unsigned int width, unsigned int height) 
{
	//if (!isRunning)
	//	return;
   Display.userSize[0] = width;
   Display.userSize[1] = height;   
   Display.currSize[0] = width;
   Display.currSize[1] = height;
   glfwSetWindowSize(glfwWindow, width, height);
   glfwGetFramebufferSize(glfwWindow, &Display.framebufferSize[0], &Display.framebufferSize[1]);
}

//! Enters or exits fullscreen mode.
void Kernel::setFullScreen(bool full) {
   /*if (full == true && Display.isFullScreen == false) {
      Display.userSize[0] = Display.currSize[0];
      Display.userSize[1] = Display.currSize[1];
      glutFullScreen();
   } else if (full == false && Display.isFullScreen == true) {
      glutFullScreenToggle();
      glutPositionWindow(0,0);
      glutReshapeWindow(Display.userSize[0], Display.userSize[1]);
   }
   Display.isFullScreen = full;*/
}

void Kernel::updateFramesPerSecond(void) {
   FrameRate.count++;
   FrameRate.currTime = (int)(glfwGetTime() / 1000.0);				// Glut used milliseconds but GLFW uses senconds.

   int timeInterval;
      
   timeInterval = FrameRate.currTime - FrameRate.prevTime;
   if (timeInterval > 500.f) {
      FrameRate.currFps = FrameRate.count * 1000.f / (timeInterval);
      FrameRate.prevTime = FrameRate.currTime;
      FrameRate.count = 0;
   }

   timeInterval = FrameRate.currTime - FrameRate.baseTime;
   if (timeInterval < (1000.f / FrameRate.fps)) {
      #ifdef _WIN32
         Sleep((DWORD)(1000.f / FrameRate.fps) - timeInterval);
      #else // UNIX
         usleep(((1000.f / FrameRate.fps) - timeInterval) * 1000.f);
      #endif // _WIN32
		 FrameRate.baseTime = (int)(glfwGetTime() / 1000.0);				// Glut used milliseconds but GLFW uses senconds.
   } else {
      FrameRate.baseTime = FrameRate.currTime;
   }
}

void Kernel::cbKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static Kernel* kernel = Kernel::getInstance();
	static Keyboard *keyboard = Keyboard::getInstance();
	static MenuHolder *menu = MenuHolder::getInstance();
	static InternalFrameHolder *ifh = InternalFrameHolder::getInstance();
	static Cursor* cursor = Cursor::getInstance();

	kernel->_componentRequestFocus = false;

	// Insert
	if (key == GLFW_KEY_INSERT && action == GLFW_PRESS)
		cursor->swapInsertState(); 

	//@afrasson
	KeyEvent::State state;
	if (action == GLFW_PRESS)
		state = KeyEvent::PRESS;
	else if (action == GLFW_REPEAT)
		state = KeyEvent::PRESS;
	else if (action == GLFW_RELEASE)
		state = KeyEvent::RELEASE;

	KeyEvent evt(key, mods, /*false,*/ state);

	if (menu->processKey(evt) == false && ifh->processKey(evt) == false) {
		//kernel callback
		kernel->onKey(evt);
		keyboard->push(key, mods/*, false*/);
		for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
			if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
				(*iter)->processKey(KeyEvent(key, mods, /*false,*/ state));
			}
		}
	}
	//@afrasson
}
void Kernel::cbCharacter(GLFWwindow* window, unsigned int codepoint, int mods)
{
	//@afrasson
	static Kernel* kernel = Kernel::getInstance();
	static Keyboard *keyboard = Keyboard::getInstance();
	static MenuHolder *menu = MenuHolder::getInstance();
	static InternalFrameHolder *ifh = InternalFrameHolder::getInstance();

	kernel->_componentRequestFocus = false;

	//kernel->onChar(codepoint, mods);
	//KeyEvent evt(key, mods, false, state);

	ifh->processChar(codepoint, mods);
	kernel->onChar(codepoint, mods);
	//keyboard->push(key, false);
	for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
		if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
			(*iter)->processChar(codepoint, mods);
		}
	}
	//@afrasson
}
void Kernel::cbCursorPosition(GLFWwindow* window, double xpos, double ypos)
{
	static Kernel *kernel = Kernel::getInstance();
	static Cursor *cursor = Cursor::getInstance();
	static MenuHolder *menu = MenuHolder::getInstance();
	static InternalFrameHolder *ifh = InternalFrameHolder::getInstance();

	kernel->cursorPos.x = (int)xpos;
	kernel->cursorPos.y = (int)ypos;

	kernel->_componentRequestFocus = false;
	if (!kernel->Mouse.locked) {
		kernel->Mouse.componentRequestUse = NULL;
	}

	MouseEvent evt;
	if (kernel->Mouse.clicked) {
		evt = MouseEvent(kernel->Mouse.lastButton, MouseEvent::HOLD, Point((int)xpos, (int)ypos));
	}
	else {
		evt = MouseEvent(MouseEvent::NBUTTON, MouseEvent::MOTION, Point((int)xpos, (int)ypos));
	}

	if (menu->processMouse(evt) == false && ifh->processMouse(evt) == false) {
		//kernel callback
		if (evt.getState() == MouseEvent::HOLD) {
			kernel->onMouseHold(evt);
		}
		else if (evt.getState() == MouseEvent::MOTION) {
			kernel->onMouseOver(evt);
		}
		for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
			if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
				(*iter)->processMouse(evt);
			}
		}
	}

	cursor->setDefaultCursor(kernel->glfwWindow);
}
void Kernel::cbCursorEnter(GLFWwindow* window, int entered)
{
	if (entered)
	{
		// The cursor entered the client area of the window
	}
	else
	{
		// The cursor left the client area of the window
	}
}
void Kernel::cbMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	//	popup_menu();
	static Kernel *kernel = Kernel::getInstance();
	static Cursor *cursor = Cursor::getInstance();
	static MenuHolder *menu = MenuHolder::getInstance();
	static InternalFrameHolder *ifh = InternalFrameHolder::getInstance();

	kernel->_componentRequestFocus = false;
	if (!kernel->Mouse.locked)
		kernel->Mouse.componentRequestUse = NULL;

	MouseEvent evt;
	if (kernel->Mouse.lastClickPosition == Point(kernel->cursorPos.x, kernel->cursorPos.y) && kernel->Mouse.lastTimeClicked.isRunning() &&
		kernel->Mouse.lastTimeClicked.getMilliseconds() <= kernel->Mouse.doubleClickTime && kernel->Mouse.lastButton == button &&
		MouseEvent::State(action) == MouseEvent::CLICK) {

		kernel->Mouse.lastTimeClicked.stop();
		kernel->Mouse.lastButton = MouseEvent::Button(button);
		evt = MouseEvent(kernel->Mouse.lastButton, MouseEvent::CLICK, Point(kernel->cursorPos.x, kernel->cursorPos.y), true);

	}
	else {
		if (MouseEvent::State(action) == MouseEvent::CLICK) {
			kernel->Mouse.lastTimeClicked.start();
			kernel->Mouse.lastClickPosition = Point(kernel->cursorPos.x, kernel->cursorPos.y);
		}
		kernel->Mouse.lastButton = MouseEvent::Button(button);
		evt = MouseEvent(kernel->Mouse.lastButton, MouseEvent::State(action), Point(kernel->cursorPos.x, kernel->cursorPos.y));
	}

	if (evt.getState() == MouseEvent::UP) {
		kernel->Mouse.clicked = false;
		if (menu->processMouse(evt) == false) {
			if (ifh->processMouse(evt) == false) {
				//kernel callback
				kernel->onMouseUp(evt);
				for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
					if ((*iter)->isVisible() && (*iter)->getCallbacksStatus())
						(*iter)->processMouse(evt);
				}
			}
		}
	}
	else {
		kernel->Mouse.clicked = true;

		Component *focusedComponent = kernel->getFocusedComponent();
		ComponentsList::reverse_iterator itUp = kernel->_objects.rbegin();

		if (menu->processMouse(evt) == false) {
			menu->closeAllMenus();
			if (ifh->processMouse(evt) == false) {
				//kernel callback
				kernel->onMouseClick(evt);
				for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
					if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
						(*iter)->processMouse(evt);
						if (focusedComponent != kernel->getFocusedComponent()) {
							focusedComponent = kernel->getFocusedComponent();
							itUp = iter;
						}
					}
				}

				if (kernel->Mouse.componentRequestUse == NULL && kernel->_contextMenu != NULL && kernel->requestMouseUse(NULL) && evt.getButton() == MouseEvent::RIGHT)
					menu->activeMenu(kernel->_contextMenu, evt.getPosition());

				// swap clicked component to end
				if (itUp != kernel->_objects.rbegin() && (*itUp)->isDragging()) {
					kernel->_objects.splice(kernel->_objects.end(), kernel->_objects, (++itUp).base());
				}
			}
		}
	}

	if (evt.getState() == MouseEvent::CLICK && kernel->_componentRequestFocus == false) {
		kernel->Mouse.componentRequestUse = NULL;
		kernel->_focusedComponent = NULL;
		kernel->Mouse.locked = false;
	}

	cursor->setDefaultCursor(kernel->glfwWindow);
}
void Kernel::cbScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	static Kernel* kernel = Kernel::getInstance();
	static Cursor *cursor = Cursor::getInstance();
	static MenuHolder *menu = MenuHolder::getInstance();
	static InternalFrameHolder *ifh = InternalFrameHolder::getInstance();

	kernel->_componentRequestFocus = false;
	if (!kernel->Mouse.locked) {
		kernel->Mouse.componentRequestUse = NULL;
	}

	MouseEvent evt;
	if (yoffset > 0) {
		evt = MouseEvent(MouseEvent::NBUTTON, MouseEvent::WHELLUP, Point(kernel->cursorPos.x, kernel->cursorPos.y));
	}
	else if (yoffset < 0) {
		evt = MouseEvent(MouseEvent::NBUTTON, MouseEvent::WHEELDOWN, Point(kernel->cursorPos.x, kernel->cursorPos.y));
	}

	if (menu->processMouse(evt) == false && ifh->processMouse(evt) == false) {
		//kernel callback
		kernel->onMouseWheel(evt);
		for (ComponentsList::reverse_iterator iter = kernel->_objects.rbegin(); iter != kernel->_objects.rend(); ++iter) {
			if ((*iter)->isVisible() && (*iter)->getCallbacksStatus()) {
				(*iter)->processMouse(evt);
			}
		}
	}
	cursor->setDefaultCursor(kernel->glfwWindow);
}
void Kernel::cbWindowClose(GLFWwindow* window)
{
	//if (!time_to_close)
	//	glfwSetWindowShouldClose(window, GL_FALSE);
}
void Kernel::cbWindowSize(GLFWwindow* window, int width, int height)
{
	static Kernel* kernel = Kernel::getInstance();

	// Check if the window should really be resized
	if (!kernel->_allowResizing)
	{
		glfwSetWindowSize(kernel->glfwWindow, kernel->Display.userSize[0], kernel->Display.userSize[1]);
		return;
	}

	//kernel->onSizeChange();

	kernel->Display.currSize[0] = width;
	kernel->Display.currSize[1] = height;
	kernel->Display.userSize[0] = width;
	kernel->Display.userSize[1] = height;

	/*if (width != kernel->Display.currSize[0] ||
		height != kernel->Display.currSize[1])
	{
		kernel->Display.currSize[0] = width;
		kernel->Display.currSize[1] = height;

		if (!kernel->_allowResizing) {
			kernel->_reshapeOnNextFrame = true;
		}
		else {
			kernel->Display.userSize[0] = width;
			kernel->Display.userSize[1] = height;
		}
		kernel->onSizeChange();
	}

	if (kernel->_reshapeOnNextFrame) {
		glfwSetWindowSize(kernel->glfwWindow, kernel->Display.userSize[0], kernel->Display.userSize[1]);
		kernel->_reshapeOnNextFrame = true;
	}*/
}
void Kernel::cbFramebufferSize(GLFWwindow* window, int width, int height)
{
	//glViewport(0, 0, width, height);
	static Kernel* kernel = Kernel::getInstance();
	kernel->Display.framebufferSize[0] = width;
	kernel->Display.framebufferSize[1] = height;

	kernel->onSizeChange();
}
void Kernel::cbWindowPosition(GLFWwindow* window, int xpos, int ypos)
{
	static Kernel* kernel = Kernel::getInstance();
	kernel->onPositionChange();
}
void Kernel::cbWindowRefresh(GLFWwindow* window)
{
	static Kernel* kernel = Kernel::getInstance();
	// update sizes
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	kernel->Display.framebufferSize[0] = width;
	kernel->Display.framebufferSize[1] = height;



	kernel->display();
	glfwSwapBuffers(window);
}
void Kernel::display(void) 
{
	static Kernel* kernel = Kernel::getInstance();
	static Cursor* cursor = Cursor::getInstance();
	static ColorScheme *scheme = ColorScheme::getInstance();

	static MenuHolder *menu = MenuHolder::getInstance();
	static InternalFrameHolder *window = InternalFrameHolder::getInstance();

	/*int new_width, new_height;
	glfwGetWindowSize(glfwWindow, &new_width, &new_height);

	if (new_width != kernel->Display.currSize[0] ||
		new_height != kernel->Display.currSize[1])
	{
		kernel->Display.currSize[0] = new_width;
		kernel->Display.currSize[1] = new_height;

		if (!kernel->_allowResizing) {
			kernel->_reshapeOnNextFrame = true;
		}
		else {
			kernel->Display.userSize[0] = new_width;
			kernel->Display.userSize[1] = new_height;
		}
		kernel->onSizeChange();
	}*/

	kernel->updateFramesPerSecond();

	cursor->requestResetCursor();
	cursor->refreshMouse();

	scheme->applyColor(ColorScheme::BACKGROUND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	kernel->applyDefaultTransformMatrix();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	kernel->onDisplay();

	for (ComponentsList::iterator iter = kernel->_objects.begin(); iter != kernel->_objects.end(); ++iter)
		if (kernel->willAppearOnScreen(*iter))
			(*iter)->display();

	window->display();
	menu->display();

	glDisable(GL_BLEND);
}


//! Adds component \c object to the window. If \c object already belongs to a panel, does nothing.
void Kernel::addComponent(Component *object) {
   if (std::find(Kernel::getInstance()->_objects.begin(), Kernel::getInstance()->_objects.end(), object) == Kernel::getInstance()->_objects.end()
         && object->getParent() == NULL) {
      _objects.push_back(object);
   }
}

//! Removes \c object from any container it is in.
void Kernel::removeComponent(Component *object) {
   if (std::find(Kernel::getInstance()->_objects.begin(), Kernel::getInstance()->_objects.end(), object) != Kernel::getInstance()->_objects.end()) {
      Kernel::getInstance()->_objects.remove(object);      
   } else if (object->getParent() != NULL) {
      object->getParent()->removeChild(object);
   }
}

bool Kernel::requestComponentFocus(Component* component) {
   if (component == NULL) false;

   static Keyboard *keyboard = Keyboard::getInstance();

   if (_componentRequestFocus == false) {
      if (_focusedComponent != NULL && _focusedComponent != component && keyboard->isEmpty() == false) {
         std::deque<Keyboard::KeyboardControl> keys = keyboard->clear();
         for (int i = 0; i < keys.size(); i++)
			 _focusedComponent->processKey(KeyEvent(keys[i].key, keys[i].modifier/*, keys[i].special*/, KeyEvent::RELEASE));
      }
      _focusedComponent = component;
      _componentRequestFocus = true;
      return true;
   } else {
      return false;
   }
	return false;
}

void Kernel::applyDefaultTransformMatrix(void) 
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //gluOrtho2D(0, Display.currSize[0], Display.currSize[1], 0);
   gluOrtho2D(0, Display.framebufferSize[0], Display.framebufferSize[1], 0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //glViewport(0, 0, Display.currSize[0], Display.currSize[1]);
   glViewport(0, 0, Display.framebufferSize[0], Display.framebufferSize[1]);
}

void Kernel::showCopyrights(void) {
   // scv credits
   std::cout
      << std::endl <<               
      " Cesar Tadeu Pozzer              Project Creator"                   << std::endl <<
      " Cicero Augusto de Lara Pahins   Developer  Documentation"          << std::endl <<
      " Frederico Artur Limberger       Developer  Documentation"          << std::endl <<
      " Yuri Schlesner                  Developer  Documentation  Support" << std::endl <<
      " Leonardo Quatrin Campagnolo     Developer  Documentation  Support" << std::endl <<
      " Tiago Boelter Mizdal            Developer  Documentation  Support" << std::endl <<
      " Bernardo Henz                   Developer  (SCV 2.0)             " << std::endl <<
      " Eduardo Speroni                 Developer  (SCV 2.0)             " << std::endl <<
      " Celito Much Felipetto           Developer  (SCV 1.0)             " << std::endl <<
      " Vinicius Gottin                 Developer  (SCV 1.0)             " << std::endl <<
      " Vitor Conrado Gomes                                              " << std::endl <<
      " Francisco Avelar                                                 " << std::endl <<
	  " Alex Thomas A. Frasson          Developer  (SCV 5.0)             " << std::endl;


   // scv logo and verison
   std::cout << std::endl <<
      " ##############################################################################" << std::endl <<
      " ############################  ################################################" << std::endl <<
      " ###########################  ##############  #################################" << std::endl <<
      " ##############              ##############  ##################################" << std::endl <<
      " #############    ########  #####           ##################  ###############" << std::endl <<
      " ##############   #######  ####    ######  ####################  ##############" << std::endl <<
      " ###############   ##########    #######  ######################  #############" << std::endl <<
      " ################   ########    #######  ###  ##################   ############" << std::endl <<
      " #################   #######   ############  ##################     ###########" << std::endl <<
      " ##################   ######   ###########   #################   ##  ##########" << std::endl <<
      " ###################   #####   ##########     ###############   ####  #########" << std::endl <<
      " ####################   ####   #########  ##   #############   ################" << std::endl <<
      " #####################   ###   ########  ####   ###########   #################" << std::endl <<
      " ######################   ###   ##############   #########   ##################" << std::endl <<
      " #######################   ###   #########  ###   #######   ###################" << std::endl <<
      " #############  #########   ###    ########  ###   #####   ####################" << std::endl <<
      " ############  ##########    ###              ###   ###   #####################" << std::endl <<
      " ###########                  #####            ###   #   ######################" << std::endl <<
      " ##########                  #################  ###     #######################" << std::endl <<
	  " #########  ###################################  ###   ######               ###" << std::endl <<
	  " ########  ##################################################  Version 5.0  ###" << std::endl <<
	  " ############################################################               ###" << std::endl <<
      " ##############################################################################"
      << std::endl;
}

//! Changes the window title.
void Kernel::setWindowTitle(const std::string &title) {
	glfwSetWindowTitle(glfwWindow, title.c_str());
}

void Kernel::addWindow(InternalFrame *window) {
   static InternalFrameHolder *winHolder = InternalFrameHolder::getInstance();
   winHolder->registerFrame(window);
}

bool Kernel::lockMouseUse(Component* component) {
   if (!Mouse.locked || component == Mouse.componentRequestUse) {
      Mouse.locked = true;
      Mouse.componentRequestUse = component;
      return true;
   } else {
      return false;
   }
}

bool Kernel::unlockMouseUse(Component* component) {
   if (component == Mouse.componentRequestUse) {
      Mouse.locked = false;
      return true;
   } else {
      return false;
   }
}

bool Kernel::requestMouseUse(Component* component) {
   if (Mouse.componentRequestUse == NULL) {
      Mouse.componentRequestUse = component;
      return true;
   } else if (Mouse.componentRequestUse == component) {
      return true;
   } else {
      return false;
   }
}

bool Kernel::willAppearOnScreen(Component* component) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();

   if (component->isVisible()) {
      Point absPosition = component->getAbsolutePosition();
      Point invPosition = absPosition.inverse();
      //if (absPosition.x > Display.currSize[0] || absPosition.y > Display.currSize[1] ||   
	  if (absPosition.x > Display.framebufferSize[0] || absPosition.y > Display.framebufferSize[1] ||
            (absPosition.x + component->getWidth()) < 0 || (absPosition.y + component->getHeight()) < 0 ||
            !math::isInside(Point(scissor->currentScissor().x, scissor->currentScissor().y).inverse() - Point(0, scissor->currentScissor().height), Point(scissor->currentScissor().width, scissor->currentScissor().height), absPosition, component->getSize())) {
         return false;
      } else {
         return true;
      }
   } else {
      return false;
   }
}

//! Locks or unlocks the window size, so that the user can not resize it by dragging.
void Kernel::lockWindowSize(bool lock) {
	_allowResizing = !lock;
}

} // namespace scv
