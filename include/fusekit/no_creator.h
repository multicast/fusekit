
#ifndef __FUSEKIT__NO_CREATOR_H
#define __FUSEKIT__NO_CREATOR_H

#include <fusekit/entry.h>

namespace fusekit{

  struct no_creator{
    entry* operator()(){
      return 0;
    }
  };

  template< class T1 >
  struct no_creator_arg{
    entry* operator()(T1){
      return 0;
    }
  };

}

#endif


