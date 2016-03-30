
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace sdkbox;

#define DEFAULT_PLACEMENT_ID "coins"
#define DEFAULT_CURRENCY_NAME "coins"

static const char *BOOL_TO_STRING(bool ok)
{
    return ok ? "yes" : "no";
}

static std::string make_string_with_coins(double coins)
{
    char ret[64] = {0};
    snprintf(ret, sizeof(ret), "%.1lf %s", coins, DEFAULT_CURRENCY_NAME);
    return ret;
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    CCLOG("Sample Startup");

    // add logo
    auto winsize = Director::getInstance()->getWinSize();
    auto logo = Sprite::create("Logo.png");
    auto logoSize = logo->getContentSize();
    logo->setPosition(Vec2(logoSize.width / 2,
                           winsize.height - logoSize.height / 2));
    addChild(logo);

    // add quit button
    auto label = Label::createWithSystemFont("QUIT", "sans", 32);
    auto quit = MenuItemLabel::create(label, [](Ref*){
        exit(0);
    });
    auto labelSize = label->getContentSize();
    quit->setPosition(Vec2(winsize.width / 2 - labelSize.width / 2 - 16,
                           -winsize.height / 2 + labelSize.height / 2 + 16));
    addChild(Menu::create(quit, NULL));

    // add test menu
    createTestMenu();

    return true;
}

void HelloWorld::createTestMenu()
{
    MenuItemFont::setFontName("sans");
    MenuItemFont::setFontSize(64);
    auto size = Director::getInstance()->getWinSize();

    // ui
    {
        Menu* menu = Menu::create(
                                  MenuItemFont::create("requestInterstitial", [](Ref*) {
            CCLOG("[Fyber] requestInterstitial");
            PluginFyber::requestInterstitial();
        }),
                                  MenuItemFont::create("showOfferWall", [](Ref*) {
            CCLOG("[Fyber] showOfferWall");
            PluginFyber::showOfferWall();
        }),
                                  MenuItemFont::create("request offers", [](Ref*) {
            CCLOG("[Fyber] request offers");
            PluginFyber::requestOffers(DEFAULT_PLACEMENT_ID);
        }),
                                  MenuItemFont::create("requestDeltaOfCoins", [](Ref*) {
            CCLOG("[Fyber] requestDeltaOfCoins");
            PluginFyber::requestDeltaOfCoins(DEFAULT_PLACEMENT_ID);
        }),
                                  NULL);
        menu->alignItemsVerticallyWithPadding(20);
        menu->setPosition(size.width/2, size.height/2);
        addChild(menu);

        _coins = 0.0f;
        _coinLabel = Label::createWithSystemFont(make_string_with_coins(_coins), "Arial", 64);
        _coinLabel->setPosition(size.width/2,100);
        addChild(_coinLabel);
    }
    CCLOG("[Fyber] init.");
    PluginFyber::init();
    PluginFyber::setListener(this);
}


// fyber callback

void HelloWorld::onVirtualCurrencyConnectorFailed(int error,
                                                  const std::string& errorCode,
                                                  const std::string& errorMsg)
{
    CCLOG("[Fyber] onVirtualCurrencyConnectorFailed: error(%d)", error);
    CCLOG("[Fyber] onVirtualCurrencyConnectorFailed: errorCode(%s)", errorCode.data());
    CCLOG("[Fyber] onVirtualCurrencyConnectorFailed: errorMsg(%s)", errorMsg.data());
}

void HelloWorld::onVirtualCurrencyConnectorSuccess(double deltaOfCoins,
                                                   const std::string& currencyId,
                                                   const std::string& currencyName,
                                                   const std::string& transactionId)
{
    CCLOG("[Fyber] onVirtualCurrencyConnectorSuccess: deltaOfCoins(%lf)", deltaOfCoins);
    CCLOG("[Fyber] onVirtualCurrencyConnectorSuccess: currencyId(%s)", currencyId.data());
    CCLOG("[Fyber] onVirtualCurrencyConnectorSuccess: currencyName(%s)", currencyName.data());
    CCLOG("[Fyber] onVirtualCurrencyConnectorSuccess: transactionId(%s)", transactionId.data());

    _coins += deltaOfCoins;
    _coinLabel->setString(make_string_with_coins(_coins));
}

void HelloWorld::onCanShowInterstitial(bool canShowInterstitial)
{
    CCLOG("[Fyber] onCanShowInterstitial: canShowInterstitial(%s)",
          BOOL_TO_STRING(canShowInterstitial));

    if (canShowInterstitial)
    {
        PluginFyber::showInterstitial();
    }
}

void HelloWorld::onInterstitialDidShow()
{
    CCLOG("[Fyber] onInterstitialDidShow");
}

void HelloWorld::onInterstitialDismiss(const std::string& reason)
{
    CCLOG("[Fyber] onInterstitialDismiss: reason(%s)", reason.data());
}

void HelloWorld::onInterstitialFailed()
{
    CCLOG("[Fyber] onInterstitialFailed");
}

void HelloWorld::onBrandEngageClientReceiveOffers(bool areOffersAvailable)
{
    CCLOG("[Fyber] onBrandEngageClientReceiveOffers: available(%s)",
          BOOL_TO_STRING(areOffersAvailable));
    if (areOffersAvailable)
    {
        PluginFyber::showOffers();
    }
}

void HelloWorld::onBrandEngageClientChangeStatus(int status, const std::string& msg)
{
    CCLOG("[Fyber] onBrandEngageClientChangeStatus: status(%d)", status);
    CCLOG("[Fyber] onBrandEngageClientChangeStatus: message(%s)", msg.data());
}

void HelloWorld::onOfferWallFinish(int status)
{
    CCLOG("[Fyber] onOfferWallFinish: status(%d)", status);
}
