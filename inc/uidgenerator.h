#ifndef INC_UIDGENERATOR
#define INC_UIDGENERATOR

namespace console {
  long currentID = 0;
  
  static long getNextID() {
    return currentID++;
  }
}

#endif