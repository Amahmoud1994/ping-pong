#define NUM_LEDS_STRIP_1 270
#define NUM_LEDS_STRIP_2 30

class Strip
{
  public:
    Strip(int startIndex, int endIndex, CRGB* leds);
    void updateLedColor(int pos, int r, int g, int b);
    void updateLedHSV(int pos, int h, int s, int v);
    void clearLeds(int start,int end);
    bool inBounds(int pos);
    CRGB* leds;
    int startIndex;
    int endIndex;
  private:
};

Strip::Strip(int startIndex, int endIndex , CRGB* leds) {
 this->leds = leds;
 this->startIndex = startIndex;
 this->endIndex = endIndex;
}

void Strip::updateLedColor(int pos, int r, int g, int b) {
  if (inBounds(pos)) {
    leds[pos].setRGB(r,g,b);
  }
}

void Strip::updateLedHSV(int pos, int h, int s, int v) {
  if (inBounds(pos)) {
    leds[pos].setHSV(h,s,v);
  }
}

bool Strip::inBounds(int position) {
  return position >= startIndex && position < endIndex;
}

void Strip::clearLeds(int start,int end) {
  for(int i = start; i < end ; i++){
    this->updateLedColor(i,0,0,0);
  }
}

CRGB leds1[NUM_LEDS_STRIP_1];
CRGB leds2[NUM_LEDS_STRIP_2];
Strip strip1(0,NUM_LEDS_STRIP_1, leds1);
Strip strip2(0,NUM_LEDS_STRIP_2, leds2);
