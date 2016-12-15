#complie qtwebengine from source on macOS Sierra 10.12.1

As we known, H264 and MP3 is not enabled by default in QtWebEngine. So we have to explicitly enable prorietary codecs when compiling Qt WebEngine.

####1. Download QtWebEngine source from [here](http://download.qt.io/official_releases/qt/5.6/5.6.2/submodules/qtwebengine-opensource-src-5.6.2.tar.xz).

####2. cd path-to-qtwebengine-src-dir/ execute:

    qmake -r CONFIG+=release WEBENGINE_CONFIG+=use_proprietary_codecs

####3. make

####4. Try fix some issue that might break the make action:

-  Cannot define category for undefined class

vi base/mac/sdk_forward_declarations.h

Add these two lines below to compile:

```
#import <CoreBluetooth/CBPeripheral.h>
#import <CoreBluetooth/CBUUID.h>
```

- issue with CBAdvertisementDataServiceDataKey or something else:

Add `#import <CoreBluetooth/CBAdvertisementData.h>` to src/3rdparty/chromium/device/bluetooth/bluetooth_low_energy_device_mac.mm

- issue with bluetooth:

Add `#import <CoreBluetooth/CoreBluetooth.h>` to base/mac/sdk_forward_declarations.h

###5. sudo make install


####NOTE:

The build directory would be very large (about 45 GB), make sure you have enough disk space.
