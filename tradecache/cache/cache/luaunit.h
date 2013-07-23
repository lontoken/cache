/**********************************************************************
* 封装与Lua交互的相关头文件和类型
* Auth: ganlong
* Build: 2013.07.23
**********************************************************************/
#ifndef _CACHE_LUAUTIL_H
#define _CACHE_LUAUTIL_H

#pragma once

#include <windows.h>
#include <lua.hpp>

#define CACHE_LIB_API extern "C" int

#define PAI(L, n) (long)(lua_isnumber(L, n) ? luaL_checknumber((L), (n)) : 0)           //取整数的参数

#define PAS(L, n) (lua_isstring(L, n) ? luaL_checkstring((L), (n)) : "")            //取字符串参数

#define PASL(L, n) (lua_isstring(L, n) ? lua_strlen(L, n) : 0)              //取字符串的长度

#define PAD(L, n) (double)(lua_isnumber(L, n) ? luaL_checknumber((L), (n)) : 0.0)          //取浮点型参数

#define CS(f, L, n) memcpy(f, PAS(L, n), min(sizeof(f), PASL(L, n)));

#endif