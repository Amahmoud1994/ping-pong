

class Strip
{
  public:
    Strip(int startIndex, int endIndex, CRGB* leds);
    void updateLedColor(int pos, int r, int g, int b);
    void clear();
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
    leds[pos].r = r;
    leds[pos].g = g;
    leds[pos].b = b;
  }
}

bool Strip::inBounds(int position) {
  return position >= startIndex && position < endIndex;
}
void Strip::clear() {
  for(int i = startIndex; i < endIndex; i++)
     updateLedColor(i,0,0,0);
}
