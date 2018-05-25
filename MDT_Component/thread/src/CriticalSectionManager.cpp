#include "mdt_component/thread/inc/CriticalSectionManager.h"
#include "mdt_component/error_handler/inc/GCTrace.h"


CriticalSectionManager::CriticalSectionManager()
{
    m_p_thread = NULL;
    m_is_any_thread_doing_usb_dl = false;
    
    InitializeCriticalSection(&_threads_cs);
}

CriticalSectionManager::~CriticalSectionManager()
{
    DeleteCriticalSection(&_threads_cs);
}

bool CriticalSectionManager::can_entry_critic_usb_dl(void * p_thread)
{
    bool ret;
    
    EnterCriticalSection(&_threads_cs);
#ifdef CRITICAL_SECTION_MANAGER_DEBUG__
    GC_TRACE_EX("p_thread: 0x%08X Critical Section==>",p_thread);
#endif
    if(!m_is_any_thread_doing_usb_dl)
    {
#ifdef CRITICAL_SECTION_MANAGER_DEBUG__
        GC_TRACE_EX("m_p_thread :m_p_thread: 0x%08X p_thread: 0x%08X",m_p_thread,p_thread);        
#endif
        m_p_thread = p_thread;
        m_is_any_thread_doing_usb_dl = true;
        
        GC_TRACE_EX("m_p_thread: 0x%08X Enter critical section===>",p_thread);
        
        ret = true;
    }
    else
    {
        GC_TRACE("p_thread: 0x%08X is in critical section",p_thread);
        ret = false;
    }
#ifdef CRITICAL_SECTION_MANAGER_DEBUG__
    GC_TRACE_EX("p_thread: 0x%08X <==Critical Section",p_thread);
#endif
    LeaveCriticalSection(&_threads_cs);
    
    return ret;
}

bool CriticalSectionManager::is_in_critic_process(void * p_thread)
{
#ifdef CRITICAL_SECTION_MANAGER_DEBUG__    
    GC_TRACE_EX("m_p_thread: 0x%08X p_thread: 0x%08X ,%d",m_p_thread,p_thread,m_is_any_thread_doing_usb_dl); 
#endif
    if((m_is_any_thread_doing_usb_dl) && (m_p_thread == p_thread))
    {
        return true;
    }
    else
    {
      return false;
    }
    
}


void CriticalSectionManager::leave_critic_usb_dl(void * p_thread)
{
    EnterCriticalSection(&_threads_cs);

#ifdef CRITICAL_SECTION_MANAGER_DEBUG__
    GC_TRACE_EX("p_thread: 0x%08X Critical Section==>",p_thread);
#endif

    if((m_is_any_thread_doing_usb_dl) && (m_p_thread == p_thread))
    {
        GC_TRACE_EX("m_p_thread: 0x%08X Leave critical section<===",p_thread);
        m_p_thread = NULL;        
        m_is_any_thread_doing_usb_dl = false;
    }
    else
    {
        GC_TRACE("Other thread want to leave thread, exit");
    }
#ifdef CRITICAL_SECTION_MANAGER_DEBUG__
    GC_TRACE_EX("p_thread: 0x%08X <==Critical Section",p_thread);
#endif
    LeaveCriticalSection(&_threads_cs);
}
