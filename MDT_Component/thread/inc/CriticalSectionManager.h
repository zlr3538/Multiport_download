#ifndef CRITICAL_SECTION_MANAGER_H__
#define CRITICAL_SECTION_MANAGER_H__
#include <Classes.hpp>

//#define CRITICAL_SECTION_MANAGER_DEBUG__

class  CriticalSectionManager
{
public:

     //friend class TBOOT1;
     bool can_entry_critic_usb_dl(void * p_thread);
     void leave_critic_usb_dl(void * p_thread);

     bool is_in_critic_process(void * p_thread);

     CriticalSectionManager();
     ~CriticalSectionManager();

private:

     void * m_p_thread;

     bool   m_is_any_thread_doing_usb_dl;

     CRITICAL_SECTION _threads_cs;
};


#endif
