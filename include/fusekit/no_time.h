
#ifndef __FUSEKIT__NO_TIME_H
#define __FUSEKIT__NO_TIME_H

#include <time.h>

namespace fusekit{

  template<
    class Derived
    >
  struct no_time {
    timespec modification_time() {
      return 0;
    }

    timespec change_time() {
      return 0;
    }

    timespec access_time() {
      return 0;
    }

    void update( int ) {
    }
  };

}

#endif


