#include "stdafx.h"
#include "Timer.h"

namespace scv {

Timer::Timer(void) {
   _running = false;
}

void Timer::start(void) {
   _running = true;
   _startTime = _currTime = (int)(glfwGetTime() / 1000.0);				// Glut used milliseconds but GLFW uses senconds.
}

void Timer::pause(void) {
   _running = false;
   _currTime = (int)(glfwGetTime() / 1000.0);				// Glut used milliseconds but GLFW uses senconds.
}

void Timer::unpause(void) {
   if (_running == false) {
	   _startTime += ((int)(glfwGetTime() / 1000.0)) - _currTime;
	   _currTime = (int)(glfwGetTime() / 1000.0);				// Glut used milliseconds but GLFW uses senconds.
   }
   _running = true;
}

void Timer::stop(void) {
   _running = false;
   _startTime = _currTime = 0;
}

int Timer::getSeconds(void) {
	if (_running) _currTime = (int)(glfwGetTime() / 1000.0);				// Glut used milliseconds but GLFW uses senconds.
   return (_currTime - _startTime) / 1000;
}

int Timer::getMilliseconds(void) {
	if (_running) _currTime = (int)(glfwGetTime() / 1000.0);				// Glut used milliseconds but GLFW uses senconds.
   return _currTime - _startTime;
}

bool Timer::isRunning(void) const {
   return _running;
}

} // namespace scv