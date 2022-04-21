#include "stdafx.h"
#include "Keyboard.h"

namespace scv {

bool Keyboard::isEmpty(void) {
   return _keyPressed.empty();
}

std::deque<Keyboard::KeyboardControl> Keyboard::clear(void) {
   std::deque<Keyboard::KeyboardControl> keys = _keyPressed;
   _keyPressed.clear();
   return keys;
}

void Keyboard::pop(int key, int modifier/*, bool special*/) {
	std::deque<KeyboardControl>::iterator it = std::find(_keyPressed.begin(), _keyPressed.end(), KeyboardControl(key, modifier/*, special*/));
   if (it != _keyPressed.end()) _keyPressed.erase(it);
}

void Keyboard::push(int key, int modifier/*, bool special*/) {
	_keyPressed.push_back(Keyboard::KeyboardControl(key, modifier/*, special*/));
}

} // namespace scv