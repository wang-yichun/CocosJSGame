//
//  jsb_kenko_auto.h
//  CocosJSGame
//
//  Created by LeadProgrammer on 1/27/15.
//
//

#ifndef __CocosJSGame__jsb_kenko_auto__
#define __CocosJSGame__jsb_kenko_auto__

#include "cocos2d.h"
#include "ScriptingCore.h"

std::string os_info();
bool jsb_os_info(JSContext *cx, uint32_t argc, JS::Value *vp);
bool jsb_callback(JSContext *cx, uint32_t argc, JS::Value *vp);
void register_jsb_kenko_all(JSContext* cx, JSObject* obj);

#endif /* defined(__CocosJSGame__jsb_kenko_auto__) */
