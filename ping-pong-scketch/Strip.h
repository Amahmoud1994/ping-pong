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

CRGB leds1[270];
CRGB leds2[30];
Strip strip1(0,270, leds1);
Strip strip2(0,30, leds2);
