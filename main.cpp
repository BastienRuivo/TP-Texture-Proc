#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "EfrosLeung.h"


int main() {
    EfrosLeung efrosLeung("../img/text1.png", 7, 32, 32, 69);
    efrosLeung.run();
    efrosLeung.show();
    return 0;
}