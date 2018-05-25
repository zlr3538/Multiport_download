/*******************************************************************************
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of MediaTek Inc. (C) 2003
 *
 *******************************************************************************/
#include "efusewriter/inc/mdt_handle_rwlock.h"
#include "mdt_component/error_handler/inc/gctrace.h"

#define QUEUE_MAX	1000

MDT_Handle_Rwlock::MDT_Handle_Rwlock(std::string  name)
{
	init(name);
}

MDT_Handle_Rwlock::~MDT_Handle_Rwlock()
{
	if(ok()) {
		CloseHandle(m_hStateMutex);
		CloseHandle(m_hReaderQueue);
		CloseHandle(m_hWriterQueue);
	}
}

void MDT_Handle_Rwlock::init(const std::string &name) {

	m_bOk = false;
	m_name = name.c_str();

	m_hStateMutex = CreateMutex(NULL, FALSE, NULL);
	m_hReaderQueue = CreateSemaphore(NULL, 0, QUEUE_MAX, NULL);
	m_hWriterQueue = CreateSemaphore(NULL, 0, QUEUE_MAX, NULL);

	if( m_hStateMutex == NULL || m_hReaderQueue == NULL || m_hWriterQueue == NULL )	{
		if( m_hStateMutex != NULL )
			CloseHandle(m_hStateMutex);
		if( m_hReaderQueue != NULL )
			CloseHandle(m_hReaderQueue);
		if( m_hWriterQueue != NULL )
			CloseHandle(m_hWriterQueue);
	}
	else {
		m_iReading = 0;
		m_iWriting = 0;
		m_iReaderInQueue = 0;
		m_iWriterInQueue = 0;

		m_bOk = true;		
	}
}

const char *MDT_Handle_Rwlock::name(void) {
	return m_name.c_str();
}

int MDT_Handle_Rwlock::rd_lock(void)
{
	if(!ok()) {
		return 1;
	}

    WaitForSingleObject(m_hStateMutex, INFINITE);

	if( m_iWriting > 0 ) {
		m_iReaderInQueue++;
		ReleaseMutex(m_hStateMutex);
		WaitForSingleObject(m_hReaderQueue, INFINITE);
	} else {
		m_iReading++;
		ReleaseMutex(m_hStateMutex);
	}

	return 0;
}

int MDT_Handle_Rwlock::rd_trylock()
{
	if(!ok()) {
		return 1;
	}

    WaitForSingleObject(m_hStateMutex,INFINITE);

	if( m_iWriting > 0 )	{
		ReleaseMutex(m_hStateMutex);
		return 2;

	} else {
		m_iReading++;
		ReleaseMutex(m_hStateMutex);
		return 0;
	}
}

int MDT_Handle_Rwlock::rd_unlock(void)
{
	int ret;
	
	if(!ok()) {
		return 1;
	}

	WaitForSingleObject(m_hStateMutex,INFINITE);
	
	if( m_iReading > 0 && m_iWriting == 0 ) {
		m_iReading--;
	    if( m_iReading == 0 ) {
			if( m_iWriterInQueue > 0 ) {
				m_iWriting=1;
				m_iWriterInQueue--;
				ReleaseSemaphore(m_hWriterQueue, 1, NULL);
			}
	    }
	    ret = 0;
    }
    else {
    	ret = 2;
    }
    
    ReleaseMutex(m_hStateMutex);

	return ret;
}

int MDT_Handle_Rwlock::wr_lock(void)
{
	if(!ok()) {
		return 1;
	}

	WaitForSingleObject(m_hStateMutex,INFINITE);

	if( m_iReading==0 && m_iWriting==0 ) {
		m_iWriting=1;
        ReleaseMutex(m_hStateMutex);
    } else {
		m_iWriterInQueue++;
		ReleaseMutex(m_hStateMutex);
		WaitForSingleObject(m_hWriterQueue,INFINITE);
    }

	return 0;
}

int MDT_Handle_Rwlock::wr_trylock()
{
	if(!ok()) {
		return 1;
	}

	WaitForSingleObject(m_hStateMutex,INFINITE);

	if( m_iReading==0 && m_iWriting==0 ) {
		m_iWriting=1;
		ReleaseMutex(m_hStateMutex);
		return 0;
    } else {
		ReleaseMutex(m_hStateMutex);
		return 2;
    }
}

int MDT_Handle_Rwlock::wr_unlock(void)
{
	int ret;

	if(!ok()) {
		return 1;
	}

	WaitForSingleObject(m_hStateMutex,INFINITE);
	
	if( m_iWriting == 1 && m_iReading == 0 ) {
	    m_iWriting=0;
		if( m_iReaderInQueue > 0 ) {
			m_iReading = m_iReaderInQueue;
			m_iReaderInQueue = 0;
			ReleaseSemaphore(m_hReaderQueue,m_iReading,NULL);
		}else if( m_iWriterInQueue > 0 ) {
			m_iWriting=1;
	        m_iWriterInQueue--;
	        ReleaseSemaphore(m_hWriterQueue,1,NULL);
	    }
		ret = 0;
	}
	else
		ret = 2;

	ReleaseMutex(m_hStateMutex);

	return ret;
}

bool MDT_Handle_Rwlock::ok(void)
{
	return m_bOk;
}

rwlock_reader_sentry::rwlock_reader_sentry( MDT_Handle_Rwlock & rwlock, std::string  prefix, bool trylock, bool bEnableDebugLog )
: m_rwlock(rwlock), m_prefix(prefix), m_is_locked(false), m_trylock(trylock), m_debuglog(bEnableDebugLog)
{
	if(m_rwlock.ok()) {
		if(trylock) {
			// trylock, return immediately
			if(!m_rwlock.rd_trylock()) {
				m_is_locked = true;
				if(m_debuglog) {
					GC_TRACE_EX("%s%srwlock: READ_TRYLOCK, OK!", m_prefix.c_str(), m_rwlock.name());
				}
			}
			else {
				if(m_debuglog) {
					GC_TRACE_EX("%s%srwlock: READ_TRYLOCK, fail!", m_prefix.c_str(), m_rwlock.name());
				}
			}
		}
		else {
			// wait for lock infinitely
			m_rwlock.rd_lock();
			m_is_locked = true;
			if(m_debuglog) {
				GC_TRACE_EX("%s%srwlock: READ_LOCK ...", m_prefix.c_str(), m_rwlock.name());
			}
		}
	}
	else {
		if(m_debuglog) {
			GC_TRACE_EX("%s%srwlock: rwlock_class::ok() == FALSE!", m_prefix.c_str(), m_rwlock.name());
		}
	}
}

rwlock_reader_sentry::~rwlock_reader_sentry()
{
	if(m_rwlock.ok()) {
		if(is_locked()) {
			if(m_debuglog) {
				GC_TRACE_EX("%s%srwlock: READ_UNLOCK.", m_prefix.c_str(), m_rwlock.name());
			}
			m_rwlock.rd_unlock();
		}
	}
	else {
		if(m_debuglog) {
			GC_TRACE_EX("%s%srwlock: rwlock_class::ok() == FALSE!", m_prefix.c_str(), m_rwlock.name());
		}
	}
}

rwlock_writer_sentry::rwlock_writer_sentry( MDT_Handle_Rwlock & rwlock, std::string  prefix, bool trylock, bool bEnableDebugLog )
: m_rwlock(rwlock), m_prefix(prefix), m_is_locked(false), m_trylock(trylock), m_debuglog(bEnableDebugLog)
{
	if(m_rwlock.ok()) {
		if(trylock) {
			// trylock, return immediately
			if(!m_rwlock.wr_trylock()) {
				m_is_locked = true;
				if(m_debuglog) {
					GC_TRACE_EX("%s%srwlock: WRITE_TRYLOCK, OK!", m_prefix.c_str(), m_rwlock.name());
				}
			}
			else {
				if(m_debuglog) {
					GC_TRACE_EX("%s%srwlock: WRITE_TRYLOCK, fail!", m_prefix.c_str(), m_rwlock.name());
				}
			}
		}
		else {
			// wait for lock infinitely
			m_rwlock.wr_lock();
			m_is_locked = true;
			if(m_debuglog) {
				GC_TRACE_EX("%s%srwlock: WRITE_LOCK ...", m_prefix.c_str(), m_rwlock.name());
			}
		}
	}
	else {
		if(m_debuglog) {
			GC_TRACE_EX("%s%srwlock: rwlock_class::ok() == FALSE!", m_prefix.c_str(), m_rwlock.name());
		}
	}
}

rwlock_writer_sentry::~rwlock_writer_sentry()
{
	if(m_rwlock.ok()) {
		if(is_locked()) {
			if(m_debuglog) {
				GC_TRACE_EX("%s%srwlock: WRITE_UNLOCK.", m_prefix.c_str(), m_rwlock.name());
			}
			m_rwlock.wr_unlock();
		}
	}
	else {
		if(m_debuglog) {
			GC_TRACE_EX("%s%srwlock: rwlock_class::ok() == FALSE!", m_prefix.c_str(), m_rwlock.name());
		}
	}
}

