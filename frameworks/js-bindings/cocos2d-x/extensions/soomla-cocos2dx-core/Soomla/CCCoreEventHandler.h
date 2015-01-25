/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "CCReward.h"

#ifndef __CCCoreEventHandler__
#define __CCCoreEventHandler__

namespace soomla {
    class CCCoreEventHandler : public cocos2d::CCObject {
    public:
        virtual void onRewardGivenEvent(CCReward *reward) = 0;
        virtual void onRewardTakenEvent(CCReward *reward) = 0;
        virtual void onCustomEvent(cocos2d::CCString *name, cocos2d::CCDictionary *extra) = 0;
    };

};

#endif /* defined(__CCCoreEventHandler__) */
