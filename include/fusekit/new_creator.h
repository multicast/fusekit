
#ifndef __FUSEKIT__NEW_CREATOR_H
#define __FUSEKIT__NEW_CREATOR_H

#include <fusekit/entry.h>

namespace fusekit{

  template< class T >
  struct new_creator{
    T* operator()(){
      return new T;
    }
  };

  template< class T, class T1 >
  struct new_creator{
    T* operator()(T1 a1){
      return new T(a1);
    }
  };

}

#endif


