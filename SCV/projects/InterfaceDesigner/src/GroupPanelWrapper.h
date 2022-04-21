#ifndef __GROUP_PANEL_WRAPPER_H__
#define __GROUP_PANEL_WRAPPER_H__

#include "GroupPanel.h"
#include "ParallelGroupPanel.h"
#include "SequentialGroupPanel.h"
#include "GroupObjectWrapper.h"

class GroupPanelWrapper;
class GroupPanelWrapperMenu : public scv::ContextMenu {
public:
   ///////////////////////////////////////////////////////////
   GroupPanelWrapperMenu(GroupPanelWrapper *host);
   virtual ~GroupPanelWrapperMenu(void);
   ///////////////////////////////////////////////////////////

   virtual void onMenuAccessed(const std::deque<std::string> &address);
protected:
   GroupPanelWrapper *_host;
private:
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

class GroupPanelWrapper : public scv::Panel {
public:
   typedef std::list<GroupObjectWrapper *> DesignList;

   ///////////////////////////////////////////////////////////
   GroupPanelWrapper(GroupPanel::GroupType type);
   virtual ~GroupPanelWrapper(void);
   ///////////////////////////////////////////////////////////

   void display(void);

   ///////////////////////////////////////////////////////////
   static ParallelGroupPanel *createHorizontalParallelGroupPanel(void);
   static SequetialGroupPanel *createHorizontalSequentialGroupPanel(void);

   static ParallelGroupPanel *createVerticalParallelGroupPanel(void);
   static SequetialGroupPanel *createVerticalSequentialGroupPanel(void);
   ///////////////////////////////////////////////////////////

   //Memory Management
   ///////////////////////////////////////////////////////////
   virtual void addChild(Component *object);
   virtual void removeChild(Component *object);
   virtual void removeAllChild(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline GroupPanel *getGroup(void) const;

   std::string getGroupCode(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   scv::Group *createPreview(void);

   static void prepareDesignPreview(void);
   static GroupObjectWrapper *getDesignObjectWrapper(scv::Component *object);
   static DesignList getDesignObjectWrapperList(void);
   ///////////////////////////////////////////////////////////

   inline GroupPanel::GroupType getType(void) const;

protected:
   GroupPanelWrapperMenu *_contextMenu;
   GroupPanel::GroupType _type;
   GroupPanel *_group;
   scv::Group *_hGroup, *_vGroup;

private:
   static DesignList s_designList;
};

///////////////////////////////////////////////////////////

GroupPanel *GroupPanelWrapper::getGroup(void) const {
   return _group;
}

GroupPanel::GroupType GroupPanelWrapper::getType(void) const {
   return _type;
}

///////////////////////////////////////////////////////////

#endif //__GROUP_PANEL_WRAPPER_H__