g++ -std=c++11 -O2 -I/usr/include/opencv /usr/lib/arm-linux-gnueabihf/libopencv_calib3d.so -lopencv_calib3d /usr/lib/arm-linux-gnueabihf/libopencv_contrib.so -lopencv_contrib /usr/lib/arm-linux-gnueabihf/libopencv_core.so -lopencv_core /usr/lib/arm-linux-gnueabihf/libopencv_features2d.so -lopencv_features2d /usr/lib/arm-linux-gnueabihf/libopencv_flann.so -lopencv_flann /usr/lib/arm-linux-gnueabihf/libopencv_gpu.so -lopencv_gpu /usr/lib/arm-linux-gnueabihf/libopencv_highgui.so -lopencv_highgui /usr/lib/arm-linux-gnueabihf/libopencv_imgproc.so -lopencv_imgproc /usr/lib/arm-linux-gnueabihf/libopencv_legacy.so -lopencv_legacy /usr/lib/arm-linux-gnueabihf/libopencv_ml.so -lopencv_ml /usr/lib/arm-linux-gnueabihf/libopencv_objdetect.so -lopencv_objdetect /usr/lib/arm-linux-gnueabihf/libopencv_ocl.so -lopencv_ocl /usr/lib/arm-linux-gnueabihf/libopencv_photo.so -lopencv_photo /usr/lib/arm-linux-gnueabihf/libopencv_stitching.so -lopencv_stitching /usr/lib/arm-linux-gnueabihf/libopencv_superres.so -lopencv_superres /usr/lib/arm-linux-gnueabihf/libopencv_ts.so -lopencv_ts /usr/lib/arm-linux-gnueabihf/libopencv_video.so -lopencv_video /usr/lib/arm-linux-gnueabihf/libopencv_videostab.so -lopencv_videostab  VideoClient.cpp MainClient.cpp AudioClient.cpp AudioInterface.cpp -o avconfclient -pthread -lasound
