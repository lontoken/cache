/**********************************************************************
* 成交信息信息 business
* Auth: ganlong
* Build: 2013.07.23
**********************************************************************/
#ifndef _CACHE_BASE_H
#define _CACHE_BASE_H

#pragma once

#include <cassert>

#if defined(_WINDOWS) || defined(WIN32) || defined(_WIN32)
#include <windows.h>
#else
#include <linux/kernel.h>
#endif


#define MIN(x, y) min(x, y)
#define MAX(x, y) max(x, y)

//----------字符操作相关---------------
#if defined(_WINDOWS) || defined(WIN32) || defined(_WIN32)
#define snprintf _snprintf
#endif

//----------线程同步相关---------------
#if defined(_WINDOWS) || defined(WIN32) || defined(_WIN32)
    typedef CRITICAL_SECTION CriticalSection;
    #define CriticalSectionLock(x) EnterCriticalSection((x))
    #define CriticalSectionUnLock(x) LeaveCriticalSection((x))
#else
    #define int CriticalSection
    #define CriticalSectionLock(x) (x)
    #define CriticalSectionUnLock(x) (x)
#endif

#define ASSERT assert

#endif