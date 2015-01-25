

#include "CCStoreService.h"
#include "CCDomainFactory.h"
#include "CCStoreConsts.h"
#include "CCVirtualItem.h"
#include "CCMarketItem.h"
#include "CCVirtualCategory.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualCurrencyPack.h"
#include "CCEquippableVG.h"
#include "CCSingleUsePackVG.h"
#include "CCUpgradeVG.h"
#include "CCSingleUseVG.h"
#include "CCDomainHelper.h"
#include "CCStoreEventDispatcher.h"
#include "CCVirtualItemReward.h"
#include "CCNativeStoreService.h"
#include "CCSoomlaStore.h"

namespace soomla {
    
    USING_NS_CC;

#define TAG "SOOMLA CCStoreService"

    static CCStoreService *sInstance = NULL;

    CCStoreService *CCStoreService::getInstance() {
        if (!sInstance)
        {
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            sInstance = new CCNativeStoreService();
            #else
            sInstance = new CCStoreService();
            #endif
            sInstance->retain();
        }
        return sInstance;
    }

    void CCStoreService::initShared(CCStoreAssets *storeAssets, cocos2d::CCDictionary *storeParams) {
        CCStoreService *storeService = CCStoreService::getInstance();
        if (!storeService->init(storeAssets, storeParams)) {
            exit(1);
        }
    }

    bool CCStoreService::init(CCStoreAssets *storeAssets, cocos2d::CCDictionary *storeParams) {

        CCStoreEventDispatcher::getInstance();    // to get sure it's inited

        CCDomainFactory *domainFactory = CCDomainFactory::getInstance();
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_MARKET_ITEM, (SEL_DomainCreator)CCMarketItem::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CATEGORY, (SEL_DomainCreator)CCVirtualCategory::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CURRENCY, (SEL_DomainCreator)CCVirtualCurrency::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CURRENCY_PACK, (SEL_DomainCreator)CCVirtualCurrencyPack::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_EQUIPPABLE_VG, (SEL_DomainCreator)CCEquippableVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_LIFETIME_VG, (SEL_DomainCreator)CCLifetimeVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_SINGLE_USE_PACK_VG, (SEL_DomainCreator)CCSingleUsePackVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_SINGLE_USE_VG, (SEL_DomainCreator)CCSingleUseVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_UPGRADE_VG, (SEL_DomainCreator)CCUpgradeVG::createWithDictionary);

        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_ITEM, (SEL_DomainCreator)CCVirtualItemReward::createWithDictionary);
        
        CCSoomlaStore::initialize(storeAssets);

        return true;
    }
}
