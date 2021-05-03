
#ifndef __FUSEKIT__SYMLINK_BUFFER_H
#define __FUSEKIT__SYMLINK_BUFFER_H

#include <fusekit/entry.h>
#include <string.h>

namespace fusekit{

  template< 
    class Derived 
    >
  struct symlink_buffer {

    int open( fuse_file_info& ){
      return -EISDIR;
    }

    int close( fuse_file_info& ){
      return -EISDIR;
    }

    int size(){
      return _target.size();
    }

    int read( char*, size_t, off_t, fuse_file_info& ){
      return -EISDIR;
    }

    int write( const char*, size_t, off_t, fuse_file_info& ){
      return -EISDIR;
    }

    int flush( fuse_file_info& ){
      return -EISDIR;
    }

    int truncate( off_t offset ){
      return -EISDIR;
    }

    int readlink( char *buf, size_t bufsize ){
      strncpy(buf, _target.c_str(), bufsize);
      return 0;
    }

    void initlink( const char* target ){
      *((std::string*)&_target) = target;
    }

  private:
    const std::string _target;
  };

}

#endif


