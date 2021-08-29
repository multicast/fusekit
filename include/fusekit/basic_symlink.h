
#ifndef __FUSEKIT__BASIC_SYMLINK_H
#define __FUSEKIT__BASIC_SYMLINK_H

#include <fusekit/basic_entry.h>
#include <fusekit/symlink_buffer.h>
#include <fusekit/symlink_node.h>
#include <fusekit/default_time.h>
#include <fusekit/default_permissions.h>
#include <fusekit/default_xattr.h>

namespace fusekit{
  template<
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_symlink_permissions,
    template <class> class AttributesPolicy = default_xattr
    >
  struct basic_symlink
    : public basic_entry<
    TimePolicy,
    PermissionPolicy,
    symlink_buffer,
    symlink_node,
    AttributesPolicy,
    S_IFLNK
    >{
    basic_symlink( const char* target ){
      static_cast<symlink_buffer<basic_entry<TimePolicy, PermissionPolicy, symlink_buffer, symlink_node, AttributesPolicy, S_IFLNK> >& >(*this).initlink(target);
    }
  };
}

#endif


