/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "support/user_default/CCUserDefault.h"

#include "CCBridgelessCoreService.h"
#include "CCSoomlaUtils.h"
#include "CCCoreEventDispatcher.h"
#include "CCSoomlaUtils.h"

namespace soomla {
    
    USING_NS_CC;
    
    #define TAG "SOOMLA CCBridgelessCoreService"

    #define DB_KEY_PRFIX "soomla."
    #define KEY_VALUE_STORAGE_KEY "soomla.kvs.keys"
    
    CCBridgelessCoreService::CCBridgelessCoreService() {
        mStoredKeys = CCSet::create();
        mStoredKeys->retain();
        
        loadStoredKeys();
    }
    
    int CCBridgelessCoreService::getTimesGiven(CCReward *reward) {
        const char *key = keyRewardTimesGiven(reward->getId()->getCString());
        const char *val = kvStorageGetValue(key);
        if (val == NULL) {
            return 0;
        }
        return CCString::create(val)->intValue();
    }
    
    void CCBridgelessCoreService::setRewardStatus(CCReward *reward, bool give, bool notify) {
        setTimesGiven(reward, give, notify);
    }
    
    int CCBridgelessCoreService::getLastSeqIdxGiven(soomla::CCSequenceReward *sequenceReward) {
        const char *key = keyRewardIdxSeqGiven(sequenceReward->getId()->getCString());
        const char *val = kvStorageGetValue(key);
        if (val == NULL) {
            return -1;
        }
        return CCString::create(val)->intValue();
    }
    
    void CCBridgelessCoreService::setLastSeqIdxGiven(CCSequenceReward *sequenceReward, unsigned int idx) {
        const char *key = keyRewardIdxSeqGiven(sequenceReward->getId()->getCString());
        kvStorageSetValue(key, CCString::createWithFormat("%d", idx)->getCString());
    }
    
    const char *CCBridgelessCoreService::kvStorageGetValue(const char *key) const {
        std::string defaultValue = "";
        std::string result = CCUserDefault::sharedUserDefault()->getStringForKey(key, defaultValue);
        if (result == defaultValue) {
            return NULL;
        }
        
        // Using this for pooling facilities, so c_str won't go away when returned
        CCString *returnedValue = CCString::create(result);
        return returnedValue->getCString();
    }
    
    void CCBridgelessCoreService::kvStorageSetValue(const char *key, const char *val) {
        CCUserDefault::sharedUserDefault()->setStringForKey(key, val);
        CCUserDefault::sharedUserDefault()->flush();
        
        addStoredKeys(key);
        saveStoredKeys();
    }
    
    void CCBridgelessCoreService::kvStorageDeleteKeyValue(const char *key) {
        CCUserDefault::sharedUserDefault()->setStringForKey(key, "");
        CCUserDefault::sharedUserDefault()->flush();
        
        removeStoredKeys(key);
        saveStoredKeys();
    }
    
    void CCBridgelessCoreService::kvStoragePurge() {
        for(CCSetIterator i = mStoredKeys->begin(); i != mStoredKeys->end(); i++) {
            if (!(*i)) {
                break;
            }
            
            CCString *key = dynamic_cast<CCString *>(*i);
            kvStorageDeleteKeyValue(key->getCString());
        }
        
        mStoredKeys->removeAllObjects();
        
        CCUserDefault::sharedUserDefault()->setStringForKey(KEY_VALUE_STORAGE_KEY, "");
        CCUserDefault::sharedUserDefault()->flush();
    }
    
    void CCBridgelessCoreService::setTimesGiven(CCReward *reward, bool up, bool notify) {
        int total = getTimesGiven(reward) + (up ? 1 : -1);
        if(total<0) total = 0;
        
        const char *key = keyRewardTimesGiven(reward->getId()->getCString());
        kvStorageSetValue(key, CCString::createWithFormat("%d", total)->getCString());
        
        if (up) {
            key = keyRewardLastGiven(reward->getId()->getCString());
            
            time_t currentTime;
            time(&currentTime);
            CCString *val = CCString::createWithFormat("%lld", (long long)(((double)currentTime) * 1000));
            
            kvStorageSetValue(key, val->getCString());
        }
        
        if (notify) {
            if (up) {
                CCCoreEventDispatcher::getInstance()->onRewardGivenEvent(reward);
            } else {
                CCCoreEventDispatcher::getInstance()->onRewardTakenEvent(reward);
            }
        }
    }
    
    void CCBridgelessCoreService::addStoredKeys(const char *key) {
        CCString *wrapKey = CCString::create(key);
        
        if (mStoredKeys->containsObject(wrapKey)) {
            return;
        }
        
        mStoredKeys->addObject(wrapKey);
    }
    
    void CCBridgelessCoreService::removeStoredKeys(const char *key) {
        CCString *wrapKey = CCString::create(key);
        
        mStoredKeys->removeObject(wrapKey);
    }
    
    void CCBridgelessCoreService::saveStoredKeys() {
        std::string joinedKeys = "";
        for(CCSetIterator i = mStoredKeys->begin(); i != mStoredKeys->end(); i++) {
            if (!(*i)) {
                break;
            }
            
            CCString *key = dynamic_cast<CCString *>(*i);
            joinedKeys.append("#").append(key->getCString());
        }
        
        CCUserDefault::sharedUserDefault()->setStringForKey(KEY_VALUE_STORAGE_KEY, joinedKeys);
        CCUserDefault::sharedUserDefault()->flush();
    }
    
    void CCBridgelessCoreService::loadStoredKeys() {
        std::string joinedKeys = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_VALUE_STORAGE_KEY, "");
        
        std::stringstream ss(joinedKeys);
        std::string item;
        while(std::getline(ss, item, '#')) {
            addStoredKeys(item.c_str());
        }
    }
    
    const char* CCBridgelessCoreService::keyRewards(const char* rewardId, const char* postfix) {
        return CCString::createWithFormat("%srewards.%s.%s", DB_KEY_PRFIX, rewardId, postfix)->getCString();
    }
    
    const char* CCBridgelessCoreService::keyRewardIdxSeqGiven(const char* rewardId) {
        return keyRewards(rewardId, "seq.id");
    }
    
    const char* CCBridgelessCoreService::keyRewardTimesGiven(const char* rewardId) {
        return keyRewards(rewardId, "timesGiven");
    }
    
    const char* CCBridgelessCoreService::keyRewardLastGiven(const char* rewardId) {
        return keyRewards(rewardId, "lastGiven");
    }
}