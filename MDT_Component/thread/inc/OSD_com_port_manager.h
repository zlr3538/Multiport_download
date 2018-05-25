#ifndef ONE_STATION_DOWNLOAD_USB_COM_PORT_NUMBER_MANAGER_H__
#define ONE_STATION_DOWNLOAD_USB_COM_PORT_NUMBER_MANAGER_H__

#include <vector>
#include "efusewriter/inc/mdt_handle_rwlock.h"

class OSD_USB_Com_Port_Number_Manager
{
public:
  OSD_USB_Com_Port_Number_Manager()
  {
    m_usb_com_port_array.clear();
	m_thread_waiting_for_usb_comport_number=0;
  }

  virtual int get_available_comport()
  {
    int comport;
    vector<int>::iterator Iter;
	if( m_usb_com_port_array.size()<=0)
    {
      GC_TRACE_EX("m_usb_com_port_array Error: size: %d ",m_usb_com_port_array.size());
      return 0;
	}
	else
	{
	  Iter = m_usb_com_port_array.begin();
      comport=*Iter;
	  m_usb_com_port_array.erase(Iter);
	  
	  if(m_usb_com_port_array.size() > 0)
	  {
	    //GC_TRACE_EX("Set Event: One_Station_Download_USB_Insert_Event");
		//SetEvent(One_Station_Download_USB_Insert_Event);
	  }
	  GC_TRACE_EX("Get com port Number: %d",comport);
	  return comport;
	}
  }
  virtual void Insert(int comportNumber)
  {
    m_usb_com_port_array.push_back(comportNumber);
	//GC_TRACE_EX("Set Event: One_Station_Download_USB_Insert_Event:");
	GC_TRACE_EX("Insert com port Number: %d",comportNumber);
	//SetEvent(One_Station_Download_USB_Insert_Event);
  }
  vector<int> m_usb_com_port_array;
  MDT_Handle_Rwlock m_rw_lock;
  int m_thread_waiting_for_usb_comport_number;  
};


#endif
