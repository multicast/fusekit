
#ifndef __FUSEKIT__BASIC_DIRECTORY_H
#define __FUSEKIT__BASIC_DIRECTORY_H

#include <fusekit/basic_entry.h>
#include <fusekit/no_buffer.h>
#include <fusekit/default_time.h>
#include <fusekit/default_permissions.h>
#include <fusekit/default_xattr.h>

namespace fusekit{
  template<
    template <class> class NodePolicy, 
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_directory_permissions,
    template <class> class AttributesPolicy = default_xattr
    >
  struct basic_directory
    : public basic_entry<
    TimePolicy,
    PermissionPolicy,
    no_buffer,
    NodePolicy,
    AttributesPolicy,
    S_IFDIR
    >{
  };
}

#endif


