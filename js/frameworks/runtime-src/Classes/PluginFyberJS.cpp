#include "PluginFyberJS.hpp"
#include "PluginFyber/PluginFyber.h"
#include "SDKBoxJSHelper.h"
#include "sdkbox/Sdkbox.h"


#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 52
#elif MOZJS_MAJOR_VERSION >= 33
template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS_ReportErrorUTF8(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}
#else
template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        JS_AddObjectRoot(cx, &pp->obj);
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    vp.set(BOOLEAN_TO_JSVAL(true));
    return true;
}
#endif
#elif defined(JS_VERSION)
template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    TypeTest<T> t;
    T* cobj = new T();
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    assert(p);
    JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
    js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

    return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return JS_FALSE;
}
#endif
JSClass  *jsb_sdkbox_PluginFyber_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_PluginFyber_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setZipcode(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setZipcode : Error processing arguments");
        sdkbox::PluginFyber::setZipcode(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setZipcode : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setZipcode(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setZipcode(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_showInterstitial(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::PluginFyber::showInterstitial();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_showInterstitial : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_showInterstitial(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::PluginFyber::showInterstitial();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setNumberOfSessions(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setNumberOfSessions : Error processing arguments");
        sdkbox::PluginFyber::setNumberOfSessions(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setNumberOfSessions : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setNumberOfSessions(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setNumberOfSessions(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setNumberOfChildren(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setNumberOfChildren : Error processing arguments");
        sdkbox::PluginFyber::setNumberOfChildren(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setNumberOfChildren : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setNumberOfChildren(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setNumberOfChildren(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setLocation(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= sdkbox::js_to_number(cx, args.get(0), &arg0);
        ok &= sdkbox::js_to_number(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setLocation : Error processing arguments");
        sdkbox::PluginFyber::setLocation(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setLocation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setLocation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= sdkbox::js_to_number(cx, argv[0], &arg0);
        ok &= sdkbox::js_to_number(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setLocation(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setIap(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        bool arg0;
        ok &= sdkbox::js_to_bool(cx, args.get(0), (bool *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setIap : Error processing arguments");
        sdkbox::PluginFyber::setIap(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setIap : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setIap(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        bool arg0;
        ok &= sdkbox::js_to_bool(cx, argv[0], (bool *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setIap(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setVersion(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setVersion : Error processing arguments");
        sdkbox::PluginFyber::setVersion(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setVersion : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setVersion(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_requestInterstitial(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::PluginFyber::requestInterstitial();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_requestInterstitial : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_requestInterstitial(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::PluginFyber::requestInterstitial();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_showOfferWall(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 0) {
        sdkbox::PluginFyber::showOfferWall();
        args.rval().setUndefined();
        return true;
    }
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_showOfferWall : Error processing arguments");
        sdkbox::PluginFyber::showOfferWall(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_showOfferWall : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_showOfferWall(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 0) {
        sdkbox::PluginFyber::showOfferWall();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::showOfferWall(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_requestOffers(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 0) {
        sdkbox::PluginFyber::requestOffers();
        args.rval().setUndefined();
        return true;
    }
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_requestOffers : Error processing arguments");
        sdkbox::PluginFyber::requestOffers(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_requestOffers : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_requestOffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 0) {
        sdkbox::PluginFyber::requestOffers();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::requestOffers(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_init(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 0) {
        sdkbox::PluginFyber::init();
        args.rval().setUndefined();
        return true;
    }
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_init : Error processing arguments");
        sdkbox::PluginFyber::init(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        const char* arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_init : Error processing arguments");
        sdkbox::PluginFyber::init(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_init : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 0) {
        sdkbox::PluginFyber::init();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::init(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 2) {
        std::string arg0;
        const char* arg1;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::init(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setDevice(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setDevice : Error processing arguments");
        sdkbox::PluginFyber::setDevice(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setDevice : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setDevice(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setDevice(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setLastSession(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        double arg0;
        ok &= sdkbox::js_to_number(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setLastSession : Error processing arguments");
        sdkbox::PluginFyber::setLastSession(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setLastSession : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setLastSession(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        double arg0;
        ok &= sdkbox::js_to_number(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setLastSession(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setAnnualHouseholdIncome(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setAnnualHouseholdIncome : Error processing arguments");
        sdkbox::PluginFyber::setAnnualHouseholdIncome(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setAnnualHouseholdIncome : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setAnnualHouseholdIncome(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setAnnualHouseholdIncome(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setMaritalStatus(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setMaritalStatus : Error processing arguments");
        sdkbox::PluginFyber::setMaritalStatus(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setMaritalStatus : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setMaritalStatus(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setMaritalStatus(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_showOffers(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 0) {
        sdkbox::PluginFyber::showOffers();
        args.rval().setUndefined();
        return true;
    }
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_showOffers : Error processing arguments");
        sdkbox::PluginFyber::showOffers(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_showOffers : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_showOffers(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 0) {
        sdkbox::PluginFyber::showOffers();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::showOffers(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_cleanLocation(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::PluginFyber::cleanLocation();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_cleanLocation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_cleanLocation(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::PluginFyber::cleanLocation();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setSexualOrientation(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setSexualOrientation : Error processing arguments");
        sdkbox::PluginFyber::setSexualOrientation(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setSexualOrientation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setSexualOrientation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setSexualOrientation(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setGender(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setGender : Error processing arguments");
        sdkbox::PluginFyber::setGender(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setGender : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setGender(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setGender(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setBirthdate(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setBirthdate : Error processing arguments");
        sdkbox::PluginFyber::setBirthdate(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setBirthdate : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setBirthdate(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setBirthdate(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setAge(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setAge : Error processing arguments");
        sdkbox::PluginFyber::setAge(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setAge : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setAge(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setAge(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setConnectionType(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setConnectionType : Error processing arguments");
        sdkbox::PluginFyber::setConnectionType(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setConnectionType : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setConnectionType(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setConnectionType(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_addCustomParameters(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_addCustomParameters : Error processing arguments");
        sdkbox::PluginFyber::addCustomParameters(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_addCustomParameters : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_addCustomParameters(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::addCustomParameters(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setInterests(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::vector<std::string> arg0;
        ok &= jsval_to_std_vector_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setInterests : Error processing arguments");
        sdkbox::PluginFyber::setInterests(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setInterests : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setInterests(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::vector<std::string> arg0;
        ok &= jsval_to_std_vector_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setInterests(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_requestDeltaOfCoins(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 0) {
        sdkbox::PluginFyber::requestDeltaOfCoins();
        args.rval().setUndefined();
        return true;
    }
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_requestDeltaOfCoins : Error processing arguments");
        sdkbox::PluginFyber::requestDeltaOfCoins(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_requestDeltaOfCoins : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_requestDeltaOfCoins(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 0) {
        sdkbox::PluginFyber::requestDeltaOfCoins();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::requestDeltaOfCoins(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setPsTime(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        double arg0;
        ok &= sdkbox::js_to_number(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setPsTime : Error processing arguments");
        sdkbox::PluginFyber::setPsTime(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setPsTime : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setPsTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        double arg0;
        ok &= sdkbox::js_to_number(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setPsTime(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_cleanCustomParameters(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        sdkbox::PluginFyber::cleanCustomParameters();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_cleanCustomParameters : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_cleanCustomParameters(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        sdkbox::PluginFyber::cleanCustomParameters();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setIapAmount(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        double arg0;
        ok &= sdkbox::js_to_number(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setIapAmount : Error processing arguments");
        sdkbox::PluginFyber::setIapAmount(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setIapAmount : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setIapAmount(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        double arg0;
        ok &= sdkbox::js_to_number(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setIapAmount(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setEthnicity(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setEthnicity : Error processing arguments");
        sdkbox::PluginFyber::setEthnicity(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setEthnicity : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setEthnicity(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setEthnicity(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginFyberJS_PluginFyber_setEducation(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginFyberJS_PluginFyber_setEducation : Error processing arguments");
        sdkbox::PluginFyber::setEducation(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginFyberJS_PluginFyber_setEducation : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginFyberJS_PluginFyber_setEducation(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginFyber::setEducation(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginFyberJS_PluginFyber_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginFyber)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginFyberJS_PluginFyber(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "PluginFyber",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_PluginFyber_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_PluginFyber_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginFyber_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_PluginFyber_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginFyber_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginFyber_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginFyber_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginFyber_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginFyber_class->finalize = js_PluginFyberJS_PluginFyber_finalize;
    jsb_sdkbox_PluginFyber_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("setZipcode", js_PluginFyberJS_PluginFyber_setZipcode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showInterstitial", js_PluginFyberJS_PluginFyber_showInterstitial, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setNumberOfSessions", js_PluginFyberJS_PluginFyber_setNumberOfSessions, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setNumberOfChildren", js_PluginFyberJS_PluginFyber_setNumberOfChildren, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLocation", js_PluginFyberJS_PluginFyber_setLocation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIap", js_PluginFyberJS_PluginFyber_setIap, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVersion", js_PluginFyberJS_PluginFyber_setVersion, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestInterstitial", js_PluginFyberJS_PluginFyber_requestInterstitial, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showOfferWall", js_PluginFyberJS_PluginFyber_showOfferWall, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestOffers", js_PluginFyberJS_PluginFyber_requestOffers, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginFyberJS_PluginFyber_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDevice", js_PluginFyberJS_PluginFyber_setDevice, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLastSession", js_PluginFyberJS_PluginFyber_setLastSession, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnnualHouseholdIncome", js_PluginFyberJS_PluginFyber_setAnnualHouseholdIncome, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaritalStatus", js_PluginFyberJS_PluginFyber_setMaritalStatus, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showOffers", js_PluginFyberJS_PluginFyber_showOffers, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("cleanLocation", js_PluginFyberJS_PluginFyber_cleanLocation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSexualOrientation", js_PluginFyberJS_PluginFyber_setSexualOrientation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setGender", js_PluginFyberJS_PluginFyber_setGender, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBirthdate", js_PluginFyberJS_PluginFyber_setBirthdate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAge", js_PluginFyberJS_PluginFyber_setAge, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setConnectionType", js_PluginFyberJS_PluginFyber_setConnectionType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addCustomParameters", js_PluginFyberJS_PluginFyber_addCustomParameters, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInterests", js_PluginFyberJS_PluginFyber_setInterests, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestDeltaOfCoins", js_PluginFyberJS_PluginFyber_requestDeltaOfCoins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPsTime", js_PluginFyberJS_PluginFyber_setPsTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("cleanCustomParameters", js_PluginFyberJS_PluginFyber_cleanCustomParameters, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIapAmount", js_PluginFyberJS_PluginFyber_setIapAmount, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEthnicity", js_PluginFyberJS_PluginFyber_setEthnicity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEducation", js_PluginFyberJS_PluginFyber_setEducation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_PluginFyber_class,
        dummy_constructor<sdkbox::PluginFyber>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::PluginFyber>(cx, jsb_sdkbox_PluginFyber_class, proto);
#else
    jsb_register_class<sdkbox::PluginFyber>(cx, jsb_sdkbox_PluginFyber_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::PluginFyber> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_PluginFyber_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "PluginFyber");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginFyberJS_PluginFyber(JSContext *cx, JSObject *global) {
    jsb_sdkbox_PluginFyber_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_PluginFyber_class->name = "PluginFyber";
    jsb_sdkbox_PluginFyber_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginFyber_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_PluginFyber_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginFyber_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginFyber_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginFyber_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginFyber_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginFyber_class->finalize = js_PluginFyberJS_PluginFyber_finalize;
    jsb_sdkbox_PluginFyber_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("setZipcode", js_PluginFyberJS_PluginFyber_setZipcode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showInterstitial", js_PluginFyberJS_PluginFyber_showInterstitial, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setNumberOfSessions", js_PluginFyberJS_PluginFyber_setNumberOfSessions, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setNumberOfChildren", js_PluginFyberJS_PluginFyber_setNumberOfChildren, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLocation", js_PluginFyberJS_PluginFyber_setLocation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIap", js_PluginFyberJS_PluginFyber_setIap, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVersion", js_PluginFyberJS_PluginFyber_setVersion, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestInterstitial", js_PluginFyberJS_PluginFyber_requestInterstitial, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showOfferWall", js_PluginFyberJS_PluginFyber_showOfferWall, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestOffers", js_PluginFyberJS_PluginFyber_requestOffers, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginFyberJS_PluginFyber_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDevice", js_PluginFyberJS_PluginFyber_setDevice, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLastSession", js_PluginFyberJS_PluginFyber_setLastSession, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnnualHouseholdIncome", js_PluginFyberJS_PluginFyber_setAnnualHouseholdIncome, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaritalStatus", js_PluginFyberJS_PluginFyber_setMaritalStatus, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showOffers", js_PluginFyberJS_PluginFyber_showOffers, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("cleanLocation", js_PluginFyberJS_PluginFyber_cleanLocation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSexualOrientation", js_PluginFyberJS_PluginFyber_setSexualOrientation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setGender", js_PluginFyberJS_PluginFyber_setGender, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBirthdate", js_PluginFyberJS_PluginFyber_setBirthdate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAge", js_PluginFyberJS_PluginFyber_setAge, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setConnectionType", js_PluginFyberJS_PluginFyber_setConnectionType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addCustomParameters", js_PluginFyberJS_PluginFyber_addCustomParameters, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInterests", js_PluginFyberJS_PluginFyber_setInterests, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestDeltaOfCoins", js_PluginFyberJS_PluginFyber_requestDeltaOfCoins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPsTime", js_PluginFyberJS_PluginFyber_setPsTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("cleanCustomParameters", js_PluginFyberJS_PluginFyber_cleanCustomParameters, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIapAmount", js_PluginFyberJS_PluginFyber_setIapAmount, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEthnicity", js_PluginFyberJS_PluginFyber_setEthnicity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEducation", js_PluginFyberJS_PluginFyber_setEducation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_PluginFyber_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_PluginFyber_class,
        dummy_constructor<sdkbox::PluginFyber>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "PluginFyber", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::PluginFyber> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_PluginFyber_class;
        p->proto = jsb_sdkbox_PluginFyber_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginFyberJS_PluginFyber(JSContext *cx, JSObject *global) {
    jsb_sdkbox_PluginFyber_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_PluginFyber_class->name = "PluginFyber";
    jsb_sdkbox_PluginFyber_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginFyber_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_PluginFyber_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginFyber_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginFyber_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginFyber_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginFyber_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginFyber_class->finalize = js_PluginFyberJS_PluginFyber_finalize;
    jsb_sdkbox_PluginFyber_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("setZipcode", js_PluginFyberJS_PluginFyber_setZipcode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showInterstitial", js_PluginFyberJS_PluginFyber_showInterstitial, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setNumberOfSessions", js_PluginFyberJS_PluginFyber_setNumberOfSessions, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setNumberOfChildren", js_PluginFyberJS_PluginFyber_setNumberOfChildren, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLocation", js_PluginFyberJS_PluginFyber_setLocation, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIap", js_PluginFyberJS_PluginFyber_setIap, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVersion", js_PluginFyberJS_PluginFyber_setVersion, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestInterstitial", js_PluginFyberJS_PluginFyber_requestInterstitial, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showOfferWall", js_PluginFyberJS_PluginFyber_showOfferWall, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestOffers", js_PluginFyberJS_PluginFyber_requestOffers, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginFyberJS_PluginFyber_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDevice", js_PluginFyberJS_PluginFyber_setDevice, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLastSession", js_PluginFyberJS_PluginFyber_setLastSession, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnnualHouseholdIncome", js_PluginFyberJS_PluginFyber_setAnnualHouseholdIncome, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaritalStatus", js_PluginFyberJS_PluginFyber_setMaritalStatus, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showOffers", js_PluginFyberJS_PluginFyber_showOffers, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("cleanLocation", js_PluginFyberJS_PluginFyber_cleanLocation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSexualOrientation", js_PluginFyberJS_PluginFyber_setSexualOrientation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setGender", js_PluginFyberJS_PluginFyber_setGender, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBirthdate", js_PluginFyberJS_PluginFyber_setBirthdate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAge", js_PluginFyberJS_PluginFyber_setAge, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setConnectionType", js_PluginFyberJS_PluginFyber_setConnectionType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addCustomParameters", js_PluginFyberJS_PluginFyber_addCustomParameters, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInterests", js_PluginFyberJS_PluginFyber_setInterests, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestDeltaOfCoins", js_PluginFyberJS_PluginFyber_requestDeltaOfCoins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPsTime", js_PluginFyberJS_PluginFyber_setPsTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("cleanCustomParameters", js_PluginFyberJS_PluginFyber_cleanCustomParameters, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIapAmount", js_PluginFyberJS_PluginFyber_setIapAmount, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEthnicity", js_PluginFyberJS_PluginFyber_setEthnicity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEducation", js_PluginFyberJS_PluginFyber_setEducation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_PluginFyber_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_PluginFyber_class,
        dummy_constructor<sdkbox::PluginFyber>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "PluginFyber", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::PluginFyber> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_PluginFyber_class;
        p->proto = jsb_sdkbox_PluginFyber_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginFyberJS(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "sdkbox", &ns);

    js_register_PluginFyberJS_PluginFyber(cx, ns);

    sdkbox::setProjectType("js");
}
#else
void register_all_PluginFyberJS(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "sdkbox", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "sdkbox", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_PluginFyberJS_PluginFyber(cx, obj);

    sdkbox::setProjectType("js");
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginFyberJS(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    jsval nsval;
    JSObject *ns;
    JS_GetProperty(cx, obj, "sdkbox", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "sdkbox", &nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_PluginFyberJS_PluginFyber(cx, obj);

    sdkbox::setProjectType("js");
}
#endif