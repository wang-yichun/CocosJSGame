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

#include "CCNativeCoreService.h"
#include "CCNdkBridge.h"
#include "CCSoomlaUtils.h"

namespace soomla {
    
    USING_NS_CC;
    
    #define TAG "SOOMLA NativeCoreService"
    
    bool CCNativeCoreService::init() {
        bool result = CCCoreService::init();
        
        if (!result) {
            return result;
        }
        
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::init"), "method");
        CCNdkBridge::callNative(params, NULL);
        
        return true;
    }

    int CCNativeCoreService::getTimesGiven(CCReward *reward) {
        CCError *error = NULL;
        
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::getTimesGiven"), "method");
        params->setObject(reward->getId(), "reward");
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
            return -1;
        }
        
        if (retParams == NULL) {
            return -1;
        }
        
        CCInteger *retValue = (CCInteger *) retParams->objectForKey("return");
        if (!retValue) {
            return -1;
        }
        
        return retValue->getValue();
    }

    void CCNativeCoreService::setRewardStatus(CCReward *reward, bool give, bool notify) {
        CCError *error = NULL;
        
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::setRewardStatus"), "method");
        params->setObject(reward->getId(), "reward");
        params->setObject(CCBool::create(give), "give");
        params->setObject(CCBool::create(notify), "notify");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    int CCNativeCoreService::getLastSeqIdxGiven(CCSequenceReward *sequenceReward) {
        CCError *error = NULL;
        
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::getLastSeqIdxGiven"), "method");
        params->setObject(sequenceReward->getId(), "reward");
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
            return -1;
        }
        
        if (retParams == NULL) {
            return -1;
        }
        
        CCInteger *retValue = (CCInteger *) retParams->objectForKey("return");
        if (!retValue) {
            return -1;
        }
        
        return retValue->getValue();
    }

    void CCNativeCoreService::setLastSeqIdxGiven(CCSequenceReward *sequenceReward, unsigned int idx) {
        CCError *error = NULL;
        
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::setLastSeqIdxGiven"), "method");
        params->setObject(sequenceReward->getId(), "reward");
        params->setObject(CCInteger::create(idx), "idx");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    const char *CCNativeCoreService::kvStorageGetValue(const char *key) const {
        CCError *error = NULL;
        
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::getValue"), "method");
        params->setObject(CCString::create(key), "key");
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
            return NULL;
        }
        
        if (retParams == NULL) {
            return NULL;
        }
        
        CCString *retValue = (CCString *) retParams->objectForKey("return");
        if (!retValue) {
            return NULL;
        }
        
        return retValue->getCString();
    }

    void CCNativeCoreService::kvStorageSetValue(const char *key, const char *val) {
        CCError *error = NULL;
        
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::setValue"), "method");
        params->setObject(CCString::create(key), "key");
        params->setObject(CCString::create(val), "val");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    void CCNativeCoreService::kvStorageDeleteKeyValue(const char *key) {
        CCError *error = NULL;
        
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::deleteKeyValue"), "method");
        params->setObject(CCString::create(key), "key");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    void CCNativeCoreService::kvStoragePurge() {
        CCError *error = NULL;
        
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::purge"), "method");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }
}