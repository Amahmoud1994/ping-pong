#include <arduino.h>

bool inBounds(int position) {
  return position >= START_INDEX && position < END_INDEX;
}
