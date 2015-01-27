//
//  jsb_kenko_auto.cpp
//  CocosJSGame
//
//  Created by LeadProgrammer on 1/27/15.
//
//

#include "jsb_kenko_auto.h"
#include "cocos2d_specifics.hpp"

std::string os_info() {
    CCLOG("it's c++ os_info here");
    return "os_info";
}

bool jsb_os_info(JSContext *cx, uint32_t argc, JS::Value *vp) {
    jsval ret = std_string_to_jsval(cx, os_info());
    JS_SET_RVAL(cx, vp, ret);
    
    return true;
}

void register_jsb_kenko_all(JSContext *cx, JSObject *obj) {
    JS_DefineFunction(cx, obj, "osInfo", jsb_os_info, 0, 0);  //生成名为osInfo的js全局函数
}