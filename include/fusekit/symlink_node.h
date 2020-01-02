
#ifndef __FUSEKIT__SYMLINK_NODE_H
#define __FUSEKIT__SYMLINK_NODE_H

#include <string.h>
#include <fusekit/entry.h>

namespace fusekit{

  template<
    class Derived
    >
  struct symlink_node {

    static const int type_flag = S_IFLNK;

    typedef symlink_node node;

    entry* find( const char* ){
      return 0;
    }
    
    int links(){
      return 1;
    }

    int opendir( fuse_file_info& ){
      return -ENOTDIR;
    }

    int readdir( void*, fuse_fill_dir_t, off_t, fuse_file_info& ){
      return -ENOTDIR;
    }

    int releasedir( fuse_file_info& ){
      return 0;
    }

    int mknod( const char* name, mode_t mode, dev_t type){
      return -ENOTDIR;
    }

    int unlink( const char* name ){
      return -ENOTDIR;
    }

    int mkdir( const char* name, mode_t mode ){
      return -ENOTDIR;
    }

    int rmdir( const char* name ){
      return -ENOTDIR;
    }

    int symlink( const char* name, const char* target ){
      return -ENOTDIR;
    }
  };
}

#endif


