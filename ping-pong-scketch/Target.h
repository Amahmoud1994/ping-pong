
class Target
{
  public:
    Target();
    void spawn();
    void draw();
    void kill();
    bool contains(int pos);
    bool alive();
    int position ;
    int range;
    float intensity;
    int hue;
  private:
    int _alive;
};
Target::Target() {
    spawn();
}
void Target::spawn(){
  this->range = (int)(3+random(3));
  this->position = this->range + (int)(random(strip1.endIndex - 2*(range)));
  this->hue = random(255);
  this->intensity = 200;
  _alive = 1;
}
bool Target::contains(int pos){
  return abs(pos- position) < range;
}
bool Target::alive(){
    return _alive;
}

void Target::kill(){
    _alive = 0;
    for (int i = 0; i < range ; i++)
    {
     strip1.updateLedColor(position + i,0,0,0);
     strip1.updateLedColor(position - i,0,0,0);
    }

}
void Target::draw(){
  if(alive())
  {
    for (int i = 0; i < range ; i++)
    {
      strip1.updateLedHSV(position + i, hue, 255, intensity);
      strip1.updateLedHSV(position - i, hue, 255, intensity);

      intensity -= 0.15;
      if(intensity < 0)
      {
        kill();
      }
    }
  }
}
