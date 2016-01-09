
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
    print("Sample Startup")

    local label = cc.Label:createWithSystemFont("QUIT", "sans", 32)
    local quit = cc.MenuItemLabel:create(label)
    quit:onClicked(function()
        os.exit(0)
    end)
    local size = label:getContentSize()
    local menu = cc.Menu:create(quit)
    menu:setPosition(display.right - size.width / 2 - 16, display.bottom + size.height / 2 + 16)
    self:addChild(menu)

    self:setupTestMenu()
end

function MainScene:setupTestMenu()
    local size = cc.Director:getInstance():getWinSize()

    cc.MenuItemFont:setFontName('sans')
    cc.MenuItemFont:setFontSize(32)

    local menu = cc.Menu:create(
        cc.MenuItemFont:create("requestInterstitial"):onClicked(handler(self, self.requestInterstitial)),
        cc.MenuItemFont:create("showOfferWall"):onClicked(handler(self, self.showOfferWall)),
        cc.MenuItemFont:create("request offers"):onClicked(handler(self, self.requestOffers)),
        cc.MenuItemFont:create("requestDeltaOfCoins"):onClicked(handler(self, self.requestDeltaOfCoins))
    )
    menu:setPosition(size.width / 2, size.height / 2)
    menu:alignItemsVerticallyWithPadding(20)
    self:addChild(menu)

    local coinsLabel = cc.Label:createWithSystemFont("0 coins", "Arial", 64)
    coinsLabel:setPosition(size.width / 2, 100)
    self:addChild(coinsLabel)

    -- fyber init
    local coins = 0
    sdkbox.PluginFyber:init()
    sdkbox.PluginFyber:setListener(function(args)
        dump(args)
        if args.name == "onVirtualCurrencyConnectorFailed" then
        elseif args.name == "onVirtualCurrencyConnectorSuccess" then
            coins = coins + args.deltaOfCoins
            coinsLabel:setString(coins .. " " .. currencyName)
        elseif args.name == "onCanShowInterstitial" then
            if args.canShowInterstitial then
                sdkbox.PluginFyber:showInterstitial()
            end
        elseif args.name == "onInterstitialDidShow" then
        elseif args.name == "onInterstitialDismiss" then
        elseif args.name == "onInterstitialFailed" then
        elseif args.name == "onBrandEngageClientReceiveOffers" then
            if args.areOffersAvailable then
                sdkbox.PluginFyber:showOffers()
            end
        elseif args.name == "onBrandEngageClientChangeStatus" then
        elseif args.name == "onOfferWallFinish" then
        end
    end)
end

function MainScene:requestInterstitial()
    print("sdkbox-fyber: requestInterstitial")
    sdkbox.PluginFyber:requestInterstitial()
end

function MainScene:showOfferWall()
    print("sdkbox-fyber: showOfferWall")
    sdkbox.PluginFyber:showOfferWall()
end

function MainScene:requestOffers()
    print("sdkbox-fyber: requestOffers")
    sdkbox.PluginFyber:requestOffers("rmb")
end

function MainScene:requestDeltaOfCoins()
    print("sdkbox-fyber: requestDeltaOfCoins")
    sdkbox.PluginFyber:requestDeltaOfCoins("rmb")
end

return MainScene
