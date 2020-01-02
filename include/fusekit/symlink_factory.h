
#ifndef __FUSEKIT__SYMLINK_FACTORY_H
#define __FUSEKIT__SYMLINK_FACTORY_H

#include <string>
#include <tr1/unordered_map>
#include <fusekit/no_lock.h>
#include <fusekit/entry.h>
#include <fusekit/symlink_node.h>
#include <fusekit/no_creator.h>

namespace fusekit{

  struct no_symlink_creator : public no_creator_arg<const char*>{
  };

  template< class Creator = no_symlink_creator, class LockingPolicy = no_lock >
  struct symlink_factory : public LockingPolicy{
    typedef std::tr1::unordered_map< std::string, entry* > map_t;
    typedef typename file_factory< Creator, LockingPolicy >::lock lock;

    ~symlink_factory() {
      lock guard(*this);
      map_t::const_iterator e = _added_symlinks.begin();
      while( e != _added_symlinks.end() ){
        delete e->second;
        ++e;
      }
      e = _created_symlinks.begin();
      while( e != _created_symlinks.end() ){
        delete e->second;
        ++e;
      }
    }

    entry* find( const char* name ) {
      lock guard(*this);
      map_t::const_iterator e = _added_symlinks.find( name );
      if( e != _added_symlinks.end() ) {
        return e->second;
      }
      e = _created_symlinks.find( name );
      if( e != _created_symlinks.end() ) {
        return e->second;
      }
      return 0;
    }

    template< class Child >
    Child& add_symlink( const char* name, Child* child ) {
      lock guard(*this);
      const map_t::key_type key( name );
      map_t::iterator e = _added_symlinks.find( name );
      if( e != _added_symlinks.end() ) {
        delete e->second;
      }
      _added_symlinks[ name ] = child;
      return *child;
    }
    
    int size() {
      lock guard(*this);
      return _added_symlinks.size() + _created_symlinks.size();
    }

    name_container_t names() {
      lock guard(*this);
      name_container_t names;
      map_t::const_iterator i = _added_symlinks.begin();
      while( i != _added_symlinks.end() ) {
        names.insert( i->first.c_str() );
        ++i;
      }
      i = _created_symlinks.begin();
      while( i != _created_symlinks.end() ) {
        names.insert( i->first.c_str() );
        ++i;
      }
      return names;
    }

    int create( const char* name, const char* target ){
      lock guard(*this);
      if( find( name ) ){
        return -EEXIST;
      }
      entry* d = _creator(target);
      if( !d ){
        return -EROFS;
      }
      _created_symlinks[name] = d;
      return 0;
    }

    int destroy( const char* name ){
      lock guard(*this);
      entry* ep = 0;
      map_t::const_iterator e = _added_symlinks.find( name );
      if( e != _added_symlinks.end() ) {
        ep = e->second;
        _added_symlinks.erase(e);
      }
      else if( (e = _created_symlinks.find( name )) != _created_symlinks.end() ){
        ep = e->second;
        _created_symlinks.erase(e);
      }
      
      if( ep ){
        delete ep;
        return 0;
      }
      else{
        return -ENOENT;
      }
    }
  private:
    Creator _creator;
    map_t _added_symlinks;
    map_t _created_symlinks;
  };

}

#endif


