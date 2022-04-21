#include "stdafx.h"
#include "InterfaceDesign.h"
#include "MenuDesign.h"
#include "AbstractWindow.h"
#include "Application.h"

InterfaceDesign::InterfaceDesign(scv::Panel *_panel, bool remove) : ContextMenu("InterfaceDesign") {

   m_panel = _panel;
   contButton = contFrame = contTeggleButton = contTextField = contTextBox = contRadioButton = contMenubar = contLabel = contCheckbox = 0;
   contProgressBar = 50;
   ContextMenu * panel = new ContextMenu("Add Panel");
   ContextMenu * component = new ContextMenu("Add Component");

   addMenu(panel);
   addMenu(component);
   if(remove)
      addMenu(new ContextMenu("Remove Component"));

   addMenu(new ContextMenu("------------------------------------------"));
   addMenu(new ContextMenu("Clear Interface"));
   addMenu(new ContextMenu("------------------------------------------"));
   addMenu(new ContextMenu("Generate Code"));
   addMenu(new ContextMenu("Generate Code with Custom Classes"));
   
   panel->addMenu(new ContextMenu("Image"));
   panel->addMenu(new ContextMenu("Internal Frame"));
   panel->addMenu(new ContextMenu("Panel"));
   panel->addMenu(new ContextMenu("Scroll Pane"));
   panel->addMenu(new ContextMenu("Tabbed Pane"));
   
   component->addMenu(new ContextMenu("Button"));
   component->addMenu(new ContextMenu("Canvas"));
   component->addMenu(new ContextMenu("CheckBox"));
   component->addMenu(new ContextMenu("Color Picker"));
   component->addMenu(new ContextMenu("ComboBox"));
   component->addMenu(new ContextMenu("Label"));
   component->addMenu(new ContextMenu("Menu Bar"));
   component->addMenu(new ContextMenu("Progress Bar"));
   component->addMenu(new ContextMenu("Radio Button"));
   ContextMenu * separator = new ContextMenu("Separator");
   separator->addMenu(new ContextMenu("Horizontal"));
   separator->addMenu(new ContextMenu("Vertical"));
   component->addMenu(separator);
   component->addMenu(new ContextMenu("Slider"));
   component->addMenu(new ContextMenu("Spinner"));
   component->addMenu(new ContextMenu("Table"));
   component->addMenu(new ContextMenu("TextBox"));
   component->addMenu(new ContextMenu("TextField"));
   component->addMenu(new ContextMenu("Toggle Button"));
   component->addMenu(new ContextMenu("Generic Tree"));

}


void InterfaceDesign::onMenuAccessed(const std::deque<std::string> &address) {

   if (address.size() == 0) {
      return;
   } else if (address.size() == 1) {

   } else  if (address.size() == 2) {
      if (address[1] == "Remove Component") {
		  scv::Kernel::getInstance()->removeComponent(m_panel);
      } else if (address[1] == "Generate Code") {
            Application *kernel = static_cast<Application*>(scv::Kernel::getInstance());
            kernel->generateCode(false);
	  }else if (address[1] == "Generate Code with Custom Classes") {
		   Application *kernel = static_cast<Application*>(scv::Kernel::getInstance());
		   kernel->generateCode(true);
	  }else if (address[1] == "Clear Interface")
      {
         Application *kernel = static_cast<Application*>(scv::Kernel::getInstance());
         kernel->clearInterface();
      }

   } else  if (address.size() == 3) {
      if (address[2] == "Button") {

         scv::Button * button;
         if (m_panel != NULL) button = new scv::Button(getCurrPosition() - m_panel->getAbsolutePosition(), "button " + scv::toString(contButton));
         else                 button = new scv::Button(getCurrPosition() , "button " + scv::toString(contButton));

         contButton++;
         button->setDraggable(true);
         button->setResizable(true);
         button->registerContextMenu(new MenuRename(button));

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(button);
         else m_panel->addChild(button);

         AbstractWindow *win = new AbstractWindow(button);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);


      } else if (address[2] == "Canvas") {

         scv::Canvas * canvas;
         if (m_panel != NULL) canvas = new scv::Canvas(scv::Point(getCurrPosition() - m_panel->getAbsolutePosition()) , scv::Point((getCurrPosition() - m_panel->getAbsolutePosition()) + 200));
         else                 canvas = new scv::Canvas(scv::Point(getCurrPosition()) , scv::Point(getCurrPosition() + 200));

         canvas->setDraggable(true);
         canvas->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(canvas);
         else m_panel->addChild(canvas);

         canvas->registerContextMenu(new RemoveComponent(canvas));

      } else if (address[2] == "CheckBox") {

         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::CheckBox * checkbox;
         if (m_panel != NULL) checkbox = new scv::CheckBox(getCurrPosition() - m_panel->getAbsolutePosition(), true,"checkbox " + scv::toString(contCheckbox));
         else                 checkbox = new scv::CheckBox(getCurrPosition(), true,"checkbox " + scv::toString(contCheckbox));

         contCheckbox++;
         checkbox->setDraggable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(checkbox);
         else panel->addChild(checkbox);

         AbstractWindow *win = new AbstractWindow(checkbox);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);

         checkbox->registerContextMenu(new RemoveComponent(checkbox));

      } else if (address[2] == "Color Picker") {

         scv::ColorPicker * colorpicker;
         if (m_panel != NULL) colorpicker = new scv::ColorPicker(getCurrPosition() - m_panel->getAbsolutePosition());
         else                 colorpicker = new scv::ColorPicker(getCurrPosition());

         colorpicker->setDraggable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(colorpicker);
         else  m_panel->addChild(colorpicker);

         colorpicker->registerContextMenu(new RemoveComponent(colorpicker));

      } else if (address[2] == "ComboBox") {

         scv::ComboBox * combobox;
         if (m_panel != NULL) combobox = new scv::ComboBox(getCurrPosition() - m_panel->getAbsolutePosition(), 100);
         else                 combobox = new scv::ComboBox(getCurrPosition(), 100);

         combobox->setDraggable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(combobox);
         else  m_panel->addChild(combobox);

         combobox->registerContextMenu(new RemoveComponent(combobox));

      } else if (address[2] == "Image") {

         scv::Image *opImage;

         scv::FileOpen::getInstance()->showDialog();

         std::string file_path = scv::FileOpen::getInstance()->getFilePath();
         if(!file_path.empty()) {
            if (m_panel != NULL){
               opImage = new scv::Image(getCurrPosition() - m_panel->getAbsolutePosition(), file_path);
            }else{
               opImage = new scv::Image(getCurrPosition(), file_path);
            }

            if(opImage != NULL) {
               opImage->setDraggable(true);
               opImage->setResizable(true);

               if (m_panel != NULL) m_panel->addChild(opImage);
               else scv::Kernel::getInstance()->addComponent(opImage);
               
               opImage->registerContextMenu(new InterfaceDesign(opImage, true));
            }
         }
     
      } else if (address[2] == "Label") {

         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::Label * label;
         if (m_panel != NULL) label = new scv::Label(getCurrPosition() - m_panel->getAbsolutePosition(), "Label Example" + scv::toString(contLabel));
         else                 label = new scv::Label(getCurrPosition(), "Label Example" + scv::toString(contLabel));

         contLabel++;
         label->setDraggable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(label);
         else panel->addChild(label);

         AbstractWindow *win = new AbstractWindow(label);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);

         label->registerContextMenu(new RemoveComponent(label));

      } else if (address[2] == "Menu Bar") {


         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::MenuBar * menubar;
         if (m_panel != NULL) menubar = new scv::MenuBar(m_panel->getWidth());
         else                 menubar = new scv::MenuBar(scv::Kernel::getInstance()->getWidth());

         menubar->setResizable(true);
         menubar->setDraggable(true);
         menubar->registerContextMenu(new MenuDesign(menubar)); //here is the add menu, and remove menu.

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(menubar);
         else m_panel->addChild(menubar);
         contMenubar++;

      } else if (address[2] == "Progress Bar") {

         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::ProgressBar * progressbar;
         if (m_panel != NULL) progressbar = new scv::ProgressBar(getCurrPosition() - m_panel->getAbsolutePosition(),(float)contProgressBar);
         else                 progressbar = new scv::ProgressBar(getCurrPosition(), (float)contProgressBar);

         progressbar->setDraggable(true);
         progressbar->setResizable(true);
         contProgressBar++; contProgressBar = contProgressBar%101;
         progressbar->setDraggable(true);
         
         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(progressbar);
         else panel->addChild(progressbar);

         progressbar->registerContextMenu(new RemoveComponent(progressbar));

      } else if (address[2] == "Radio Button") {

         scv::RadioButton * radiobutton;
         if (m_panel != NULL) radiobutton = new scv::RadioButton(getCurrPosition() - m_panel->getAbsolutePosition(), true, "radiobutton " + scv::toString(contRadioButton));
         else                 radiobutton = new scv::RadioButton(getCurrPosition(), true, "radiobutton " + scv::toString(contRadioButton));

         contRadioButton++;
         radiobutton->setDraggable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(radiobutton);
         else m_panel->addChild(radiobutton);

         AbstractWindow *win = new AbstractWindow(radiobutton);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);

         radiobutton->registerContextMenu(new RemoveComponent(radiobutton));

      } else if (address[2] == "Slider") {

         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::Slider * slider;
         if (m_panel != NULL) slider = new scv::Slider(getCurrPosition() - m_panel->getAbsolutePosition(), 0.f, 100.f, 50.f, 1.f);
         else                 slider = new scv::Slider(getCurrPosition(), 0.f, 100.f, 50.f, 1.f);

         slider->setEditable(false);
         slider->setDraggable(true);
         slider->setResizable(true);
         

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(slider);
         else panel->addChild(slider);

         slider->registerContextMenu(new RemoveComponent(slider));

      } else if (address[2] == "Spinner") {

         scv::Spinner * spinner;
         if (m_panel != NULL) spinner = new scv::Spinner(getCurrPosition() - m_panel->getAbsolutePosition(), 20, 0.f, 100.f, 50.f, 1.f);
         else                 spinner = new scv::Spinner(getCurrPosition(), 20, 0.f, 100.f, 50.f, 1.f);

         spinner->setEditable(false);
         spinner->setDraggable(true);
         spinner->setResizable(true);
         
         spinner->registerContextMenu(new RemoveComponent(spinner));

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(spinner);
         else m_panel->addChild(spinner);

         

      } else if (address[2] == "Table") {

         scv::Table * table;
         if (m_panel != NULL) table = new scv::Table(getCurrPosition() - m_panel->getAbsolutePosition(), 4, 4, 1, 50);
         else                 table = new scv::Table(getCurrPosition(), 4, 4, 1, 50);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(table);
         else m_panel->addChild(table);

         table->setEditable(false);
         table->setDraggable(true);
         table->setResizable(true);

         table->registerContextMenu(new RemoveComponent(table)); //need to click under the buttons or textbox.

      } else if (address[2] == "TextBox") {

         scv::TextBox * textbox;
         if (m_panel != NULL) textbox = new scv::TextBox(getCurrPosition() - m_panel->getAbsolutePosition(), 100, 4, "TextBox " + scv::toString(contTextBox));
         else                 textbox = new scv::TextBox(getCurrPosition(), 100, 4, "TextBox " + scv::toString(contTextBox));

         textbox->setEditable(false);
         contTextBox++;
         textbox->setDraggable(true);
         textbox->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(textbox);
         else m_panel->addChild(textbox);

         /*AbstractWindow *win = new AbstractWindow(textbox);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addComponent(win);*/

         textbox->registerContextMenu(new RemoveComponent(textbox));

      } else if (address[2] == "TextField") {

         scv::TextField * textfield;
         if (m_panel != NULL) textfield = new scv::TextField(getCurrPosition() - m_panel->getAbsolutePosition(), 100, "TextField " + scv::toString(contTextField));
         else                 textfield = new scv::TextField(getCurrPosition(), 100, "TextField " + scv::toString(contTextField));

         textfield->setEditable(false);
         contTextField++;
         textfield->setDraggable(true);
         textfield->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(textfield);
         else m_panel->addChild(textfield);


         /*AbstractWindow *win = new AbstractWindow(textfield);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);*/

         textfield->registerContextMenu(new RemoveComponent(textfield));

      } else if (address[2] == "Toggle Button") {

         scv::ToggleButton * togglebutton;
         if (m_panel != NULL) togglebutton = new scv::ToggleButton(getCurrPosition() - m_panel->getAbsolutePosition(), false, "toggle button " + scv::toString(contTeggleButton));
         else                 togglebutton = new scv::ToggleButton(getCurrPosition(), false, "toggle button " + scv::toString(contTeggleButton));

         contTeggleButton++;
         togglebutton->setDraggable(true);
         togglebutton->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(togglebutton);
         else m_panel->addChild(togglebutton);

         AbstractWindow *win = new AbstractWindow(togglebutton);
         win->setRelativePosition(scv::Point((scv::Kernel::getInstance()->getWidth() - win->getWidth())/2,(scv::Kernel::getInstance()->getHeight() - win->getHeight())/2));
         scv::Kernel::getInstance()->addWindow(win);

         togglebutton->registerContextMenu(new RemoveComponent(togglebutton));

      } else if (address[2] == "Panel") {

         scv::Panel * newpanel;
         if (m_panel != NULL){
            newpanel = new scv::Panel(scv::Point(getCurrPosition() - m_panel->getAbsolutePosition()),scv::Point((getCurrPosition() - m_panel->getAbsolutePosition()) +200) );
         }else{
            newpanel = new scv::Panel(scv::Point(getCurrPosition()), scv::Point(getCurrPosition()+200));
         }

         newpanel->registerContextMenu(new InterfaceDesign(newpanel, true));
         newpanel->setDraggable(true);
         newpanel->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(newpanel);
         else m_panel->addChild(newpanel);

      } else if (address[2] == "Tabbed Pane") {

         scv::TabbedPane * newtabbedpane;
         if (m_panel != NULL) newtabbedpane = new scv::TabbedPane(scv::Point(getCurrPosition() - m_panel->getAbsolutePosition()),scv::Point((getCurrPosition() - m_panel->getAbsolutePosition()) +200) );
         else                 newtabbedpane = new scv::TabbedPane(scv::Point(getCurrPosition()), scv::Point(getCurrPosition()+200));

         newtabbedpane->setDraggable(true);
         newtabbedpane->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(newtabbedpane);
         else m_panel->addChild(newtabbedpane);

         scv::Panel *panel = new scv::Panel(scv::Point(0,0), scv::Point(200,200));
         newtabbedpane->addChild(panel,"Painel 1");

         panel->registerContextMenu(new InterfaceDesign(panel));

         newtabbedpane->registerContextMenu(new RemoveComponent(newtabbedpane));

      } else if (address[2] == "Scroll Pane") {

         scv::Panel * panel = new scv::Panel(scv::Point(),scv::Point()+500);
         scv::ScrollComponent * newscrollComponent;
         
         if (m_panel != NULL){
            newscrollComponent = new scv::ScrollComponent(scv::Point(getCurrPosition() - m_panel->getAbsolutePosition()), scv::Point((getCurrPosition() - m_panel->getAbsolutePosition())) +300);
         }else{
            newscrollComponent = new scv::ScrollComponent(scv::Point(getCurrPosition()), scv::Point(getCurrPosition()+300));
         }

         newscrollComponent->setComponent(panel);
         newscrollComponent->setDraggable(true);
         newscrollComponent->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(newscrollComponent);
         else m_panel->addChild(newscrollComponent);

         panel->registerContextMenu(new InterfaceDesign(panel));

         newscrollComponent->registerContextMenu(new RemoveComponent(newscrollComponent));

      } else if (address[2] == "Internal Frame") {

         scv::Panel * panel = (scv::Panel*)m_panel;
         scv::InternalFrame * iframe = new scv::InternalFrame(200,200,"internal frame " + scv::toString(contFrame));
         contFrame++;
         iframe->setDraggable(true);
         iframe->setResizable(true);
         scv::Kernel::getInstance()->addComponent(iframe);

         iframe->getPanel()->registerContextMenu(new InterfaceDesign(iframe->getPanel()));

         iframe->registerContextMenu(new RemoveComponent(iframe));

      } else if (address[2] == "Generic Tree") {

         scv::GenericTree *tbTV;

         if (m_panel != NULL) tbTV = new scv::GenericTree(getCurrPosition() - m_panel->getRelativePosition(), (getCurrPosition() - m_panel->getRelativePosition()) + 200, new scv::GenericNode("root") );
         else                 tbTV = new scv::GenericTree(getCurrPosition(), getCurrPosition() + 200, new scv::GenericNode("root"));

         tbTV->setDraggable(true);
         tbTV->setResizable(true);

         if (m_panel == NULL)  scv::Kernel::getInstance()->addComponent(tbTV);
         else m_panel->addChild(tbTV);

         tbTV->registerContextMenu(new RemoveComponent(tbTV));

      }
   } else if (address.size() == 4) {

      scv::Separator * separator;

      if (address[3] == "Horizontal") {

         if (m_panel != NULL) separator = new scv::Separator(getCurrPosition() - m_panel->getAbsolutePosition(), scv::Separator::HORIZONTAL, 200);
         else                 separator = new scv::Separator(getCurrPosition(), scv::Separator::HORIZONTAL, 200);

         separator->setDraggable(true);
         separator->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(separator);
         else m_panel->addChild(separator);

      } else if (address[3] == "Vertical") {

         if (m_panel != NULL) separator = new scv::Separator(getCurrPosition() - m_panel->getAbsolutePosition(),scv::Separator::VERTICAL, 200);
         else                 separator = new scv::Separator(getCurrPosition(), scv::Separator::VERTICAL, 200);

         separator->setDraggable(true);
         separator->setResizable(true);

         if (m_panel == NULL) scv::Kernel::getInstance()->addComponent(separator);
         else m_panel->addChild(separator);

      }

      separator->registerContextMenu(new RemoveComponent(separator));
   }
}

