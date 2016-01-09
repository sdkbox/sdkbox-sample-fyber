#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PluginFyber/PluginFyber.h"

class HelloWorld : public cocos2d::Layer, public sdkbox::FyberListener
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    void createTestMenu();
    
    // fyber callback
    void onVirtualCurrencyConnectorFailed(int error,
                                          const std::string& errorCode,
                                          const std::string& errorMsg);
    void onVirtualCurrencyConnectorSuccess(double deltaOfCoins,
                                           const std::string& currencyId,
                                           const std::string& currencyName,
                                           const std::string& transactionId);
    void onCanShowInterstitial(bool canShowInterstitial);
    void onInterstitialDidShow();
    void onInterstitialDismiss(const std::string& reason);
    void onInterstitialFailed();
    void onBrandEngageClientReceiveOffers(bool areOffersAvailable);
    void onBrandEngageClientChangeStatus(int status, const std::string& msg);
    void onOfferWallFinish(int status);
    
    cocos2d::Label *_coinLabel;
    double _coins;
};

#endif // __HELLOWORLD_SCENE_H__
