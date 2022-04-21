#include "stdafx.h"
#include "AbstractWindow.h"

AbstractWindow::AbstractWindow(scv::Label *component) : InternalFrame(300, 100, "Component Name") {
   m_component = component;
   m_input = new InputText(this);
   getPanel()->addChild(m_input);
   m_ok = new AcceptButton(this);
   getPanel()->addChild(m_ok);
   m_cancel = new CancelButton(this);
   getPanel()->addChild(m_cancel);
   scv::Kernel::getInstance()->requestComponentFocus(m_input);
   isLabel = true;
}

AbstractWindow::AbstractWindow(scv::TextBox *component) : InternalFrame(300, 100, "Component Content") {
   t_component = component;
   m_input = new InputText(this);
   getPanel()->addChild(m_input);
   m_ok = new AcceptButton(this);
   getPanel()->addChild(m_ok);
   m_cancel = new CancelButton(this);
   getPanel()->addChild(m_cancel);
   scv::Kernel::getInstance()->requestComponentFocus(m_input);
   isLabel = false;
}


AcceptButton::AcceptButton(AbstractWindow * window) : Button(scv::Point(70,65), 75, "Ok") {
   m_window = window;
}

CancelButton::CancelButton(AbstractWindow * window) : Button(scv::Point(155,65), 75, "Cancel") {
   m_window = window;
}

InputText::InputText(AbstractWindow * window) : scv::TextField(scv::Point(20,30), 260, "") {
   m_window = window;
}

void AcceptButton::onMouseUp(const scv::MouseEvent &evt) {
   accept();
}

void AcceptButton::accept(void) {
    if(m_window->isLabel)
    {
        m_window->m_component->setString(m_window->m_input->getString());
    }else{
        m_window->t_component->setString(m_window->m_input->getString());
    }
   m_window->setVisible(false);
}

void CancelButton::onMouseUp(const scv::MouseEvent &evt) {
   m_window->setVisible(false);
}

void InputText::onKey(const scv::KeyEvent &evt) {
   if (evt.keycode == GLFW_KEY_ENTER) {
      m_window->m_ok->accept();
   }
}