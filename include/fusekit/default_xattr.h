
#ifndef __FUSEKIT__DEFAULT_XATTR_H
#define __FUSEKIT__DEFAULT_XATTR_H

#include <string>
#include <map>
#include <vector>
#include <array>

namespace fusekit{

  template<
    class Derived
    >
  struct default_xattr {
    int setxattr( const char *name, const char *value, size_t size, int flags ){
      const std::string key(name);
      attributes_type::const_iterator element = _attributes.find(key);
      if( element != _attributes.end() && flags == 1 ){
        return -EEXIST;
      }
      if( element == _attributes.end() && flags == 2 ){
        return -ENODATA;
      }
      _attributes[key].clear();
      _attributes[key].assign(value, value + size);
      return 0;
    }
    int getxattr( const char *name, char *value, size_t size ){
      const std::string key(name);
      attributes_type::const_iterator element = _attributes.find(key);
      if( element == _attributes.end() ){
        return -ENODATA;
      }
      if( size != 0 ){
        if( element->second.size() > size ){
          return -ERANGE;
        }
        std::copy(element->second.begin(), element->second.end(), value);
      }
      return element->second.size();
    }
    int listxattr( char *list, size_t size ){
      size_t needed_size = 0;
      for( attributes_type::const_iterator it = _attributes.begin(); it != _attributes.end(); it++){
        needed_size += it->first.size() + 1;
      }
      if( size != 0 ){
        if( needed_size > size ){
          return -ERANGE;
        }
        for( attributes_type::const_iterator it = _attributes.begin(); it != _attributes.end(); it++){
          size_t name_size = it->first.size();
          std::copy(it->first.begin(), it->first.end(), list);
          list += name_size;
          *(list++) = 0;
        }
      }
      return needed_size;
    }
    int removexattr( const char *name ){
      const std::string key(name);
      attributes_type::const_iterator element = _attributes.find(key);
      if( element == _attributes.end() ){
        return -ENODATA;
      }
      _attributes.erase(element);
      return 0;
    }
  private:
    typedef std::map<std::string, std::vector<char>> attributes_type;
    attributes_type _attributes;
  };

}

#endif


