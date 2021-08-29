
#ifndef __FUSEKIT__BASIC_ENTRY_H
#define __FUSEKIT__BASIC_ENTRY_H

#include <fusekit/entry.h>
#include <fusekit/time_fields.h>

namespace fusekit{
  
  /// the template host class for file entries, which follows the so called 
  /// "Curiously Recurring Template Pattern" described in ....
  /// compile time polymorphism.
  ///
  ///
  template< 
    template <class> class TimePolicy,
    template <class> class PermissionPolicy,
    template <class> class BufferPolicy,
    template <class> class NodePolicy,
    template <class> class AttributesPolicy,
    int TypeFlag
    >
  struct basic_entry 
    : public entry
    , public TimePolicy< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, AttributesPolicy, TypeFlag > >
    , public PermissionPolicy< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, AttributesPolicy, TypeFlag > >
    , public BufferPolicy< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, AttributesPolicy, TypeFlag > >
    , public NodePolicy< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, AttributesPolicy, TypeFlag > >
    , public AttributesPolicy< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, AttributesPolicy, TypeFlag > >{

    template< template <class> class Base >
    inline 
    Base< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, AttributesPolicy, TypeFlag > >& base() {
      return static_cast< Base< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, AttributesPolicy, TypeFlag > >& >(*this);
    }

    virtual entry* child( const char* name ){
      return base< NodePolicy >().find( name );
    }

    virtual int stat( struct stat& stbuf){
      stbuf.st_mode = TypeFlag | base< PermissionPolicy >().mode();
      stbuf.st_nlink = base< NodePolicy >().links();
      stbuf.st_size = base< BufferPolicy >().size();
      stbuf.st_ctim = base< TimePolicy >().change_time();
      stbuf.st_atim = base< TimePolicy >().access_time();
      stbuf.st_mtim = base< TimePolicy >().modification_time();
      return 0;
    }

    virtual int access( int mode ){
      return base< PermissionPolicy >().access( mode );
    }

    virtual int chmod( mode_t permission ){
      return base< PermissionPolicy >().chmod( permission );
    }

    virtual int open( fuse_file_info& fi ){
      return base< BufferPolicy >().open(fi);
    }

    virtual int release( fuse_file_info& fi ){
      return base< BufferPolicy >().close(fi);
    }

    virtual int read( char* buf, size_t size, off_t offset, fuse_file_info& fi ){      
      return base< BufferPolicy >().read( buf, size, offset, fi );
    }

    virtual int write( const char* buf, size_t size, off_t offset, fuse_file_info& fi ){
      return base< BufferPolicy >().write( buf, size, offset, fi );
    }

    virtual int opendir( fuse_file_info& fi ){
      return base< NodePolicy >().opendir( fi );
    }

    virtual int readdir( void *buf, fuse_fill_dir_t filler, off_t offset, fuse_file_info& fi ){
      return base< NodePolicy >().readdir( buf, filler, offset, fi );
    }

    virtual int releasedir( fuse_file_info& fi ){
      return base< NodePolicy >().releasedir( fi );
    }

    virtual int mknod( const char* name, mode_t mode, dev_t type ){
      return base< NodePolicy >().mknod( name, mode, type );
    }

    virtual int unlink( const char* name ){
      return base< NodePolicy >().unlink( name );
    }

    virtual int mkdir( const char* name, mode_t mode ){
      return base< NodePolicy >().mkdir( name, mode );
    }

    virtual int rmdir( const char* name ){
      return base< NodePolicy >().rmdir( name );
    }

    virtual int flush( fuse_file_info& fi ){ 
      return base< BufferPolicy >().flush( fi );
    }

    virtual int truncate( off_t off ){ 
      return base< BufferPolicy >().truncate( off );
    }

    virtual int utimens( const timespec[2] ){
      // TODO: Changes to using the arguments
      base< TimePolicy >().update( fusekit::access_time | fusekit::modification_time );
      return 0;
    }

    virtual int readlink( char *buf, size_t bufsize ){
      return base< BufferPolicy >().readlink(buf, bufsize);
    }

    virtual int symlink( const char *name, const char *target ){
      return base< NodePolicy >().symlink(name, target);
    }

    virtual int setxattr( const char *name, const char *value, size_t size, int flags ){
      return base< AttributesPolicy >().setxattr(name, value, size, flags);
    }

    virtual int getxattr( const char *name, char *value, size_t size ){
      return base< AttributesPolicy >().getxattr(name, value, size);
    }

    virtual int listxattr( char *list, size_t size ){
      return base< AttributesPolicy >().listxattr(list, size);
    }

    virtual int removexattr( const char *name ){
      return base< AttributesPolicy >().removexattr(name);
    }
  };
}

#endif


