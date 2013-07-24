/**********************************************************************
* ��װ��Lua���������ͷ�ļ�������
* Auth: ganlong
* Build: 2013.07.23
**********************************************************************/
#ifndef _CACHE_LUAUTIL_H
#define _CACHE_LUAUTIL_H

#pragma once

#include <lua.hpp>
#include "base.h"

#define CACHE_LIB_API extern "C" int

#define PAI(L, n) (long)(lua_isnumber(L, n) ? luaL_checknumber((L), (n)) : 0)           //ȡ�����Ĳ���

#define PAC(L, n) (char)(lua_isnumber(L, n) ? luaL_checknumber((L), (n)) : 0)           //ȡ���ַ��Ĳ���

#define PAS(L, n) (lua_isstring(L, n) ? luaL_checkstring((L), (n)) : "")            //ȡ�ַ�������

#define PASL(L, n) (lua_isstring(L, n) ? lua_strlen(L, n) : 0)              //ȡ�ַ����ĳ���

#define PAD(L, n) (double)(lua_isnumber(L, n) ? luaL_checknumber((L), (n)) : 0.0)          //ȡ�����Ͳ���

#define CS(f, L, n) memcpy(f, PAS(L, n), MIN(sizeof(f), PASL(L, n)))

#define PN(L, f) lua_pushnumber(L, f)

#define PS(L, f) lua_pushlstring(L, f, sizeof(f))

#define PLS(L, f, n) lua_pushlstring(L, f, n)

#endif