/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/

#include "qczmq.h"

///
//  Copy-construct to return the proper wrapped c types
QZhashx::QZhashx (zhashx_t *self, QObject *qObjParent) : QObject (qObjParent)
{
    this->self = self;
}


///
//  Create a new, empty hash container
QZhashx::QZhashx (QObject *qObjParent) : QObject (qObjParent)
{
    this->self = zhashx_new ();
}

///
//  Unpack binary frame into a new hash table. Packed data must follow format
//  defined by zhashx_pack. Hash table is set to autofree. An empty frame    
//  unpacks to an empty hash table.                                          
QZhashx* QZhashx::unpack (QZframe *frame, QObject *qObjParent)
{
    return new QZhashx (zhashx_unpack (frame->self), qObjParent);
}

///
//  Same as unpack but uses a user-defined deserializer function to convert
//  a longstr back into item format.                                       
QZhashx* QZhashx::unpackOwn (QZframe *frame, zhashx_deserializer_fn deserializer, QObject *qObjParent)
{
    return new QZhashx (zhashx_unpack_own (frame->self, deserializer), qObjParent);
}

///
//  Destroy a hash container and all items in it
QZhashx::~QZhashx ()
{
    zhashx_destroy (&self);
}

///
//  Insert item into hash table with specified key and item.               
//  If key is already present returns -1 and leaves existing item unchanged
//  Returns 0 on success.                                                  
int QZhashx::insert (const void *key, void *item)
{
    int rv = zhashx_insert (self, key, item);
    return rv;
}

///
//  Update or insert item into hash table with specified key and item. If the
//  key is already present, destroys old item and inserts new one. If you set
//  a container item destructor, this is called on the old value. If the key 
//  was not already present, inserts a new item. Sets the hash cursor to the 
//  new item.                                                                
void QZhashx::update (const void *key, void *item)
{
    zhashx_update (self, key, item);
    
}

///
//  Remove an item specified by key from the hash table. If there was no such
//  item, this function does nothing.                                        
void QZhashx::deleteNoConflict (const void *key)
{
    zhashx_delete (self, key);
    
}

///
//  Delete all items from the hash table. If the key destructor is  
//  set, calls it on every key. If the item destructor is set, calls
//  it on every item.                                               
void QZhashx::purge ()
{
    zhashx_purge (self);
    
}

///
//  Return the item at the specified key, or null
void * QZhashx::lookup (const void *key)
{
    void * rv = zhashx_lookup (self, key);
    return rv;
}

///
//  Reindexes an item from an old key to a new key. If there was no such
//  item, does nothing. Returns 0 if successful, else -1.               
int QZhashx::rename (const void *oldKey, const void *newKey)
{
    int rv = zhashx_rename (self, oldKey, newKey);
    return rv;
}

///
//  Set a free function for the specified hash table item. When the item is
//  destroyed, the free function, if any, is called on that item.          
//  Use this when hash items are dynamically allocated, to ensure that     
//  you don't have memory leaks. You can pass 'free' or NULL as a free_fn. 
//  Returns the item, or NULL if there is no such item.                    
void * QZhashx::freefn (const void *key, zhashx_free_fn freeFn)
{
    void * rv = zhashx_freefn (self, key, freeFn);
    return rv;
}

///
//  Return the number of keys/items in the hash table
size_t QZhashx::size ()
{
    size_t rv = zhashx_size (self);
    return rv;
}

///
//  Return a zlistx_t containing the keys for the items in the       
//  table. Uses the key_duplicator to duplicate all keys and sets the
//  key_destructor as destructor for the list.                       
QZlistx * QZhashx::keys ()
{
    QZlistx *rv = new QZlistx (zhashx_keys (self));
    return rv;
}

///
//  Return a zlistx_t containing the values for the items in the  
//  table. Uses the duplicator to duplicate all items and sets the
//  destructor as destructor for the list.                        
QZlistx * QZhashx::values ()
{
    QZlistx *rv = new QZlistx (zhashx_values (self));
    return rv;
}

///
//  Simple iterator; returns first item in hash table, in no given order, 
//  or NULL if the table is empty. This method is simpler to use than the 
//  foreach() method, which is deprecated. To access the key for this item
//  use zhashx_cursor(). NOTE: do NOT modify the table while iterating.   
void * QZhashx::first ()
{
    void * rv = zhashx_first (self);
    return rv;
}

///
//  Simple iterator; returns next item in hash table, in no given order, 
//  or NULL if the last item was already returned. Use this together with
//  zhashx_first() to process all items in a hash table. If you need the 
//  items in sorted order, use zhashx_keys() and then zlistx_sort(). To  
//  access the key for this item use zhashx_cursor(). NOTE: do NOT modify
//  the table while iterating.                                           
void * QZhashx::next ()
{
    void * rv = zhashx_next (self);
    return rv;
}

///
//  After a successful first/next method, returns the key for the item that
//  was returned. This is a constant string that you may not modify or     
//  deallocate, and which lasts as long as the item in the hash. After an  
//  unsuccessful first/next, returns NULL.                                 
const void * QZhashx::cursor ()
{
    const void * rv = zhashx_cursor (self);
    return rv;
}

///
//  Add a comment to hash table before saving to disk. You can add as many   
//  comment lines as you like. These comment lines are discarded when loading
//  the file. If you use a null format, all comments are deleted.            
void QZhashx::comment (const QString &param)
{
    zhashx_comment (self, "%s", param.toUtf8().data());
    
}

///
//  Save hash table to a text file in name=value format. Hash values must be
//  printable strings; keys may not contain '=' character. Returns 0 if OK, 
//  else -1 if a file error occurred.                                       
int QZhashx::save (const QString &filename)
{
    int rv = zhashx_save (self, filename.toUtf8().data());
    return rv;
}

///
//  Load hash table from a text file in name=value format; hash table must 
//  already exist. Hash values must printable strings; keys may not contain
//  '=' character. Returns 0 if OK, else -1 if a file was not readable.    
int QZhashx::load (const QString &filename)
{
    int rv = zhashx_load (self, filename.toUtf8().data());
    return rv;
}

///
//  When a hash table was loaded from a file by zhashx_load, this method will
//  reload the file if it has been modified since, and is "stable", i.e. not 
//  still changing. Returns 0 if OK, -1 if there was an error reloading the  
//  file.                                                                    
int QZhashx::refresh ()
{
    int rv = zhashx_refresh (self);
    return rv;
}

///
//  Serialize hash table to a binary frame that can be sent in a message.
//  The packed format is compatible with the 'dictionary' type defined in
//  http://rfc.zeromq.org/spec:35/FILEMQ, and implemented by zproto:     
//                                                                       
//     ; A list of name/value pairs                                      
//     dictionary      = dict-count *( dict-name dict-value )            
//     dict-count      = number-4                                        
//     dict-value      = longstr                                         
//     dict-name       = string                                          
//                                                                       
//     ; Strings are always length + text contents                       
//     longstr         = number-4 *VCHAR                                 
//     string          = number-1 *VCHAR                                 
//                                                                       
//     ; Numbers are unsigned integers in network byte order             
//     number-1        = 1OCTET                                          
//     number-4        = 4OCTET                                          
//                                                                       
//  Comments are not included in the packed data. Item values MUST be    
//  strings.                                                             
QZframe * QZhashx::pack ()
{
    QZframe *rv = new QZframe (zhashx_pack (self));
    return rv;
}

///
//  Same as pack but uses a user-defined serializer function to convert items
//  into longstr.                                                            
QZframe * QZhashx::packOwn (zhashx_serializer_fn serializer)
{
    QZframe *rv = new QZframe (zhashx_pack_own (self, serializer));
    return rv;
}

///
//  Make a copy of the list; items are duplicated if you set a duplicator 
//  for the list, otherwise not. Copying a null reference returns a null  
//  reference. Note that this method's behavior changed slightly for CZMQ 
//  v3.x, as it does not set nor respect autofree. It does however let you
//  duplicate any hash table safely. The old behavior is in zhashx_dup_v2.
QZhashx * QZhashx::dup ()
{
    QZhashx *rv = new QZhashx (zhashx_dup (self));
    return rv;
}

///
//  Set a user-defined deallocator for hash items; by default items are not
//  freed when the hash is destroyed.                                      
void QZhashx::setDestructor (zhashx_destructor_fn destructor)
{
    zhashx_set_destructor (self, destructor);
    
}

///
//  Set a user-defined duplicator for hash items; by default items are not
//  copied when the hash is duplicated.                                   
void QZhashx::setDuplicator (zhashx_duplicator_fn duplicator)
{
    zhashx_set_duplicator (self, duplicator);
    
}

///
//  Set a user-defined deallocator for keys; by default keys are freed
//  when the hash is destroyed using free().                          
void QZhashx::setKeyDestructor (zhashx_destructor_fn destructor)
{
    zhashx_set_key_destructor (self, destructor);
    
}

///
//  Set a user-defined duplicator for keys; by default keys are duplicated
//  using strdup.                                                         
void QZhashx::setKeyDuplicator (zhashx_duplicator_fn duplicator)
{
    zhashx_set_key_duplicator (self, duplicator);
    
}

///
//  Set a user-defined comparator for keys; by default keys are
//  compared using strcmp.                                     
void QZhashx::setKeyComparator (zhashx_comparator_fn comparator)
{
    zhashx_set_key_comparator (self, comparator);
    
}

///
//  Set a user-defined comparator for keys; by default keys are
//  compared using strcmp.                                     
void QZhashx::setKeyHasher (zhashx_hash_fn hasher)
{
    zhashx_set_key_hasher (self, hasher);
    
}

///
//  Make copy of hash table; if supplied table is null, returns null.    
//  Does not copy items themselves. Rebuilds new table so may be slow on 
//  very large tables. NOTE: only works with item values that are strings
//  since there's no other way to know how to duplicate the item value.  
QZhashx * QZhashx::dupV2 ()
{
    QZhashx *rv = new QZhashx (zhashx_dup_v2 (self));
    return rv;
}

///
//  Set hash for automatic value destruction. This method is deprecated
//  and you should use set_destructor instead.                         
void QZhashx::autofree ()
{
    zhashx_autofree (self);
    
}

///
//  Apply function to each item in the hash table. Items are iterated in no
//  defined order. Stops if callback function returns non-zero and returns 
//  final return code from callback function (zero = success). This method 
//  is deprecated and you should use zhashx_first/_next instead.           
int QZhashx::foreachNoConflict (zhashx_foreach_fn callback, void *argument)
{
    int rv = zhashx_foreach (self, callback, argument);
    return rv;
}

///
//  Self test of this class.
void QZhashx::test (bool verbose)
{
    zhashx_test (verbose);
    
}
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/
