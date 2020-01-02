
#ifndef __FUSEKIT__DEFAULT_TIME_H
#define __FUSEKIT__DEFAULT_TIME_H

#include <time.h>
#include <fusekit/time_fields.h>

namespace fusekit{

  template<
    class Derived
    >
  struct default_time {

    default_time() : 
      _change_time( now() ),
      _modification_time( _change_time ),
      _access_time( _change_time ) {
    }
	 
    timespec modification_time() {
      return _modification_time;
    }

    timespec change_time() {
      return _change_time;
    }

    timespec access_time() {
      return _access_time;
    }

    void update( int mask ){
      const struct timespec now = default_time::now();
      if( mask & fusekit::change_time ) {
        _change_time = now;
      }
      if( mask & fusekit::modification_time ) {
        _modification_time = now;
      }
      if( mask & fusekit::access_time ) {
        _access_time = now;
      }
    }

  private:
    struct timespec _change_time;
    struct timespec _modification_time;
    struct timespec _access_time;

    static timespec now(){
      struct timespec time;
      clock_gettime(CLOCK_REALTIME, &time);
      return time;
    }
  };
}

#endif


