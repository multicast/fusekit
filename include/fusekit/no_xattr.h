
#ifndef __FUSEKIT__NO_XATTR_H
#define __FUSEKIT__NO_XATTR_H

namespace fusekit{

  template<
    class Derived
    >
  struct no_xattr {
    int setxattr( const char*, const char*, size_t, int ){
      return -ENOTSUP;
    }
    int getxattr( const char*, char*, size_t ){
      return -ENOTSUP;
    }
    int listxattr( char*, size_t ){
      return -ENOTSUP;
    }
    int removexattr( const char* ){
      return -ENOTSUP;
    }
  };

}

#endif


