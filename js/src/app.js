
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        cc.log("Sample Startup")

        this.createTestMenu();

        var winsize = cc.winSize;

        var logo = new cc.Sprite("res/Logo.png");
        var logoSize = logo.getContentSize();
        logo.x = logoSize.width / 2;
        logo.y = winsize.height - logoSize.height / 2;
        this.addChild(logo);

        var quit = new cc.MenuItemLabel(new cc.LabelTTF("QUIT", "sans", 32), function() {
            cc.log("QUIT");
        });
        var menu = new cc.Menu(quit);
        var size = quit.getContentSize();
        menu.x = winsize.width - size.width / 2 - 16;
        menu.y = size.height / 2 + 16;
        this.addChild(menu);

        return true;
    },

    createTestMenu:function() {
        var size = cc.winSize;

        // ui
        cc.MenuItemFont.setFontName('sans');
        cc.MenuItemFont.setFontSize(32);

        var menu = new cc.Menu(
            new cc.MenuItemFont("requestInterstitial", this.requestInterstitial, this),
            new cc.MenuItemFont("showOfferWall", this.showOfferWall, this),
            new cc.MenuItemFont("request offers", this.requestOffers, this),
            new cc.MenuItemFont("requestDeltaOfCoins", this.requestDeltaOfCoins, this)
        );
        menu.setPosition(size.width/2, size.height/2);
        menu.alignItemsVerticallyWithPadding(20);
        this.addChild(menu);

        var coinsLabel = cc.Label.createWithSystemFont("0 coins", "Arial", 64);
        coinsLabel.setPosition(size.width/2, 100);
        this.addChild(coinsLabel);

        // fyber init
        coins = 0;
        sdkbox.PluginFyber.init();
        sdkbox.PluginFyber.setListener({
            onVirtualCurrencyConnectorFailed : function (error, errorCode, errorMsg) {
                var msg =   " error=" + error +
                            " errorCode=" + errorCode +
                            " errorMsg=" + errorMsg;
                console.log("sdkbox-fyber cb [onVirtualCurrencyConnectorFailed]" + msg);
            },
            onVirtualCurrencyConnectorSuccess : function (deltaOfCoins, currencyId, currencyName, transactionId) {
                var msg = " deltaOfCoins=" + deltaOfCoins +
                          " currencyId=" + currencyId +
                          " currencyName=" + currencyName +
                          " transactionId=" + transactionId;
                console.log("sdkbox-fyber cb [onVirtualCurrencyConnectorSuccess]" + msg);

                coins += deltaOfCoins;
                if (coinsLabel) coinsLabel.setString(coins + " " + currencyName);
            },
            onCanShowInterstitial : function (canShowInterstitial) {
                var msg = " canShowInterstitial=" + canShowInterstitial;
                console.log("sdkbox-fyber cb [onCanShowInterstitial]" + msg);

                // show ad
                if (canShowInterstitial) {
                    sdkbox.PluginFyber.showInterstitial();
                }
            },
            onInterstitialDidShow : function () {
                console.log("sdkbox-fyber cb [onInterstitialDidShow]");
            },
            onInterstitialDismiss : function (reason) {
                var msg = " reason=" + reason;
                console.log("sdkbox-fyber cb [onInterstitialDismiss]" + msg);
            },
            onInterstitialFailed : function () {
                console.log("sdkbox-fyber cb [onInterstitialFailed]");
            },
            onBrandEngageClientReceiveOffers : function (areOffersAvailable) {
                var msg = " offer is " + (areOffersAvailable ? "available" : "not available");
                console.log("sdkbox-fyber cb [onBrandEngageClientReceiveOffers]" + msg);

                // show ad
                if (areOffersAvailable) {
                    sdkbox.PluginFyber.showOffers();
                }
            },
            onBrandEngageClientChangeStatus : function (status, msg) {
                var msg = " status=" + status +
                            " msg=" + msg;
                console.log("sdkbox-fyber cb [onBrandEngageClientChangeStatus]" + msg);
            },
            onOfferWallFinish : function (status) {
                var msg = " status=" + status;
                console.log("sdkbox-fyber cb [onOfferWallFinish]" + msg);
            }
        });
        return true;
    },
    requestInterstitial:function(sender) {
        console.log("sdkbox-fyber: requestInterstitial");
        sdkbox.PluginFyber.requestInterstitial();
    },
    showOfferWall:function(sender) {
        console.log("sdkbox-fyber: showOfferWall");
        sdkbox.PluginFyber.showOfferWall();
    },
    requestOffers:function(sender) {
        console.log("sdkbox-fyber: requestOffers");
        sdkbox.PluginFyber.requestOffers("rmb");
    },
    requestDeltaOfCoins:function(sender) {
        console.log("sdkbox-fyber: requestDeltaOfCoins");
        sdkbox.PluginFyber.requestDeltaOfCoins("rmb");
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

