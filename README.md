
# How to run sdkbox samples

Steps:

~~~bash
mkdir samples
cd samples

# must clone this repo
git clone --depth 1 https://github.com/sdkbox/sdkbox-cocos2d-x-binary.git

# clone sample repo
git clone --depth 1 https://github.com/sdkbox/sdkbox-sample-fyber.git

# run sample with specified language and platform
# eg: cpp and ios
./sdkbox-cocos2d-x-binary/run_sample.sh fyber cpp ios
# javascript and android
./sdkbox-cocos2d-x-binary/run_sample.sh fyber js android

# <optional> if exists "download-depends.sh" in sample repo, execute it
# ./sdkbox-sample-fyber/download-depends.sh

~~~

Memo:

1.  Sample repo and cocos2dx repo must be in same level directory

~~~
+-- sdkbox-cocos2d-x-binary
+-- sdkbox-sample-fyber
| +-- cpp
| +-- lua
| \-- js
~~~

## More information
SDKBox:
[http://cocos2d-x.org/sdkbox](http://cocos2d-x.org/sdkbox)

Forum:
[http://discuss.cocos2d-x.org/](http://discuss.cocos2d-x.org/)

Fyber:
[http://www.fyber.com/](http://www.fyber.com/)
