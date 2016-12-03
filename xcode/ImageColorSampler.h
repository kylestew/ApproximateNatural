#ifndef ImageColorSampler_h
#define ImageColorSampler_h

#include "cinder/Perlin.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;

class ImageColorSampler {
public:
    ImageColorSampler(const fs::path &assetPath) {
        surface = loadImage(loadAsset(assetPath));
        w = surface.getWidth();
        h = surface.getHeight();
        perlin = Perlin();
        perlin.setSeed((int)clock());
        random = Rand();
        random.seed((int)clock());
    }
    
    ColorA randomSample() {
        double x = random.nextFloat(0, w);
        double y = random.nextFloat(0, h);
        return surface.getPixel(vec2(x, y));
    }
    
    ColorA perlinSample(vec2 p) {
        p = perlin.dfBm(p * 0.005f) * vec2(w, h);
        return surface.getPixel(p);
    }
    
private:
    Surface32f surface;
    Perlin perlin;
    Rand random;
    float w, h;
};

#endif /* ImageColorSampler_h */