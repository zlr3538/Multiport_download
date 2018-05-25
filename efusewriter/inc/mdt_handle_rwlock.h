/*******************************************************************************
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of MediaTek Inc. (C) 2003
 *
 *******************************************************************************/
#ifndef MDT_HANDLE_RWLOCK_H__
#define MDT_HANDLE_RWLOCK_H__

#include <windows.h>
#include <string>

class MDT_Handle_Rwlock {

public:

	MDT_Handle_Rwlock(std::string  name="");
	~MDT_Handle_Rwlock();

	friend class rwlock_reader_sentry;
	friend class rwlock_writer_sentry;

	MDT_Handle_Rwlock(const MDT_Handle_Rwlock &src) { init(src.m_name); }
	MDT_Handle_Rwlock & operator = (const MDT_Handle_Rwlock &src) { return *this; /*bypass copy*/ }

	const char *name(void);

	int	rd_lock(void);
	int rd_trylock(void);
	int	rd_unlock(void);

	int wr_lock(void);
	int wr_trylock(void);
	int wr_unlock(void);

	bool ok(void);

private:

	void init(const std::string &name);

	std::string		m_name;
	bool	m_bOk;

	HANDLE m_hStateMutex;
	HANDLE m_hReaderQueue;
	HANDLE m_hWriterQueue;
	int m_iReading;
	int m_iReaderInQueue;
	int m_iWriting;
	int m_iWriterInQueue;
};

class rwlock_reader_sentry {

public:

	rwlock_reader_sentry( MDT_Handle_Rwlock & rwlock, std::string  prefix="", bool trylock=false, bool bEnableDebugLog=true);
	~rwlock_reader_sentry();
	
	inline bool is_locked() { return m_is_locked; }

private:

	MDT_Handle_Rwlock	&m_rwlock;
	std::string		m_prefix;
	bool	m_is_locked;
	bool	m_trylock;
	bool	m_debuglog;
};

class rwlock_writer_sentry {

public:

	rwlock_writer_sentry( MDT_Handle_Rwlock & rwlock, std::string  prefix="", bool trylock=false, bool bEnableDebugLog=true);
	~rwlock_writer_sentry();
	
	inline bool is_locked() { return m_is_locked; }

private:

	MDT_Handle_Rwlock	&m_rwlock;
	std::string		m_prefix;
	bool	m_is_locked;
	bool	m_trylock;
	bool	m_debuglog;
};

#endif

