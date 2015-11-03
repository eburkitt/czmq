/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/

#include "QmlZsock.h"


///
//  Bind a socket to a formatted endpoint. For tcp:// endpoints, supports   
//  ephemeral ports, if you specify the port number as "*". By default      
//  zsock uses the IANA designated range from C000 (49152) to FFFF (65535). 
//  To override this range, follow the "*" with "[first-last]". Either or   
//  both first and last may be empty. To bind to a random port within the   
//  range, use "!" in place of "*".                                         
//                                                                          
//  Examples:                                                               
//      tcp://127.0.0.1:*           bind to first free port from C000 up    
//      tcp://127.0.0.1:!           bind to random port from C000 to FFFF   
//      tcp://127.0.0.1:*[60000-]   bind to first free port from 60000 up   
//      tcp://127.0.0.1:![-60000]   bind to random port from C000 to 60000  
//      tcp://127.0.0.1:![55000-55999]                                      
//                                  bind to random port from 55000 to 55999 
//                                                                          
//  On success, returns the actual port number used, for tcp:// endpoints,  
//  and 0 for other transports. On failure, returns -1. Note that when using
//  ephemeral ports, a port may be reused by different services without     
//  clients being aware. Protocols that run on ephemeral ports should take  
//  this into account.                                                      
int QmlZsock::bind (const QString &format) {
    return zsock_bind (self, "%s", format.toUtf8().data());
};

///
//  Returns last bound endpoint, if any.
const QString QmlZsock::endpoint () {
    return QString (zsock_endpoint (self));
};

///
//  Unbind a socket from a formatted endpoint.                     
//  Returns 0 if OK, -1 if the endpoint was invalid or the function
//  isn't supported.                                               
int QmlZsock::unbind (const QString &format) {
    return zsock_unbind (self, "%s", format.toUtf8().data());
};

///
//  Connect a socket to a formatted endpoint        
//  Returns 0 if OK, -1 if the endpoint was invalid.
int QmlZsock::connect (const QString &format) {
    return zsock_connect (self, "%s", format.toUtf8().data());
};

///
//  Disconnect a socket from a formatted endpoint                  
//  Returns 0 if OK, -1 if the endpoint was invalid or the function
//  isn't supported.                                               
int QmlZsock::disconnect (const QString &format) {
    return zsock_disconnect (self, "%s", format.toUtf8().data());
};

///
//  Attach a socket to zero or more endpoints. If endpoints is not null,     
//  parses as list of ZeroMQ endpoints, separated by commas, and prefixed by 
//  '@' (to bind the socket) or '>' (to connect the socket). Returns 0 if all
//  endpoints were valid, or -1 if there was a syntax error. If the endpoint 
//  does not start with '@' or '>', the serverish argument defines whether   
//  it is used to bind (serverish = true) or connect (serverish = false).    
int QmlZsock::attach (const QString &endpoints, bool serverish) {
    return zsock_attach (self, endpoints.toUtf8().data(), serverish);
};

///
//  Returns socket type as printable constant string.
const QString QmlZsock::typeStr () {
    return QString (zsock_type_str (self));
};

///
//  Send a 'picture' message to the socket (or actor). The picture is a   
//  string that defines the type of each frame. This makes it easy to send
//  a complex multiframe message in one call. The picture can contain any 
//  of these characters, each corresponding to one or two arguments:      
//                                                                        
//      i = int (signed)                                                  
//      1 = uint8_t                                                       
//      2 = uint16_t                                                      
//      4 = uint32_t                                                      
//      8 = uint64_t                                                      
//      s = char *                                                        
//      b = byte *, size_t (2 arguments)                                  
//      c = zchunk_t *                                                    
//      f = zframe_t *                                                    
//      h = zhashx_t *                                                    
//      U = zuuid_t *                                                     
//      p = void * (sends the pointer value, only meaningful over inproc) 
//      m = zmsg_t * (sends all frames in the zmsg)                       
//      z = sends zero-sized frame (0 arguments)                          
//      u = uint (deprecated)                                             
//                                                                        
//  Note that s, b, c, and f are encoded the same way and the choice is   
//  offered as a convenience to the sender, which may or may not already  
//  have data in a zchunk or zframe. Does not change or take ownership of 
//  any arguments. Returns 0 if successful, -1 if sending failed for any  
//  reason.                                                               
int QmlZsock::send (const QString &picture) {
    return zsock_send (self, picture.toUtf8().data());
};

///
//  Send a 'picture' message to the socket (or actor). This is a va_list 
//  version of zsock_send (), so please consult its documentation for the
//  details.                                                             
int QmlZsock::vsend (const QString &picture, va_list argptr) {
    return zsock_vsend (self, picture.toUtf8().data(), argptr);
};

///
//  Receive a 'picture' message to the socket (or actor). See zsock_send for
//  the format and meaning of the picture. Returns the picture elements into
//  a series of pointers as provided by the caller:                         
//                                                                          
//      i = int * (stores signed integer)                                   
//      4 = uint32_t * (stores 32-bit unsigned integer)                     
//      8 = uint64_t * (stores 64-bit unsigned integer)                     
//      s = char ** (allocates new string)                                  
//      b = byte **, size_t * (2 arguments) (allocates memory)              
//      c = zchunk_t ** (creates zchunk)                                    
//      f = zframe_t ** (creates zframe)                                    
//      U = zuuid_t * (creates a zuuid with the data)                       
//      h = zhashx_t ** (creates zhashx)                                    
//      p = void ** (stores pointer)                                        
//      m = zmsg_t ** (creates a zmsg with the remaing frames)              
//      z = null, asserts empty frame (0 arguments)                         
//      u = uint * (stores unsigned integer, deprecated)                    
//                                                                          
//  Note that zsock_recv creates the returned objects, and the caller must  
//  destroy them when finished with them. The supplied pointers do not need 
//  to be initialized. Returns 0 if successful, or -1 if it failed to recv  
//  a message, in which case the pointers are not modified. When message    
//  frames are truncated (a short message), sets return values to zero/null.
//  If an argument pointer is NULL, does not store any value (skips it).    
//  An 'n' picture matches an empty frame; if the message does not match,   
//  the method will return -1.                                              
int QmlZsock::recv (const QString &picture) {
    return zsock_recv (self, picture.toUtf8().data());
};

///
//  Receive a 'picture' message from the socket (or actor). This is a    
//  va_list version of zsock_recv (), so please consult its documentation
//  for the details.                                                     
int QmlZsock::vrecv (const QString &picture, va_list argptr) {
    return zsock_vrecv (self, picture.toUtf8().data(), argptr);
};

///
//  Send a binary encoded 'picture' message to the socket (or actor). This 
//  method is similar to zsock_send, except the arguments are encoded in a 
//  binary format that is compatible with zproto, and is designed to reduce
//  memory allocations. The pattern argument is a string that defines the  
//  type of each argument. Supports these argument types:                  
//                                                                         
//   pattern    C type                  zproto type:                       
//      1       uint8_t                 type = "number" size = "1"         
//      2       uint16_t                type = "number" size = "2"         
//      4       uint32_t                type = "number" size = "3"         
//      8       uint64_t                type = "number" size = "4"         
//      s       char *, 0-255 chars     type = "string"                    
//      S       char *, 0-2^32-1 chars  type = "longstr"                   
//      c       zchunk_t *              type = "chunk"                     
//      f       zframe_t *              type = "frame"                     
//      u       zuuid_t *               type = "uuid"                      
//      m       zmsg_t *                type = "msg"                       
//      p       void *, sends pointer value, only over inproc              
//                                                                         
//  Does not change or take ownership of any arguments. Returns 0 if       
//  successful, -1 if sending failed for any reason.                       
int QmlZsock::bsend (const QString &picture) {
    return zsock_bsend (self, picture.toUtf8().data());
};

///
//  Receive a binary encoded 'picture' message from the socket (or actor).  
//  This method is similar to zsock_recv, except the arguments are encoded  
//  in a binary format that is compatible with zproto, and is designed to   
//  reduce memory allocations. The pattern argument is a string that defines
//  the type of each argument. See zsock_bsend for the supported argument   
//  types. All arguments must be pointers; this call sets them to point to  
//  values held on a per-socket basis. Do not modify or destroy the returned
//  values. Returns 0 if successful, or -1 if it failed to read a message.  
int QmlZsock::brecv (const QString &picture) {
    return zsock_brecv (self, picture.toUtf8().data());
};

///
//  Return socket routing ID if any. This returns 0 if the socket is not
//  of type ZMQ_SERVER or if no request was already received on it.     
uint32_t QmlZsock::routingId () {
    return zsock_routing_id (self);
};

///
//  Set routing ID on socket. The socket MUST be of type ZMQ_SERVER.        
//  This will be used when sending messages on the socket via the zsock API.
void QmlZsock::setRoutingId (uint32_t routingId) {
    zsock_set_routing_id (self, routingId);
};

///
//  Set socket to use unbounded pipes (HWM=0); use this in cases when you are
//  totally certain the message volume can fit in memory. This method works  
//  across all versions of ZeroMQ. Takes a polymorphic socket reference.     
void QmlZsock::setUnbounded () {
    zsock_set_unbounded (self);
};

///
//  Send a signal over a socket. A signal is a short message carrying a   
//  success/failure code (by convention, 0 means OK). Signals are encoded 
//  to be distinguishable from "normal" messages. Accepts a zock_t or a   
//  zactor_t argument, and returns 0 if successful, -1 if the signal could
//  not be sent. Takes a polymorphic socket reference.                    
int QmlZsock::signal (byte status) {
    return zsock_signal (self, status);
};

///
//  Wait on a signal. Use this to coordinate between threads, over pipe  
//  pairs. Blocks until the signal is received. Returns -1 on error, 0 or
//  greater on success. Accepts a zsock_t or a zactor_t as argument.     
//  Takes a polymorphic socket reference.                                
int QmlZsock::wait () {
    return zsock_wait (self);
};

///
//  If there is a partial message still waiting on the socket, remove and    
//  discard it. This is useful when reading partial messages, to get specific
//  message types.                                                           
void QmlZsock::flush () {
    zsock_flush (self);
};


QObject* QmlZsock::qmlAttachedProperties(QObject* object) {
    return new QmlZsockAttached(object);
}


///
//  Create a PUB socket. Default action is bind.
QmlZsock *QmlZsockAttached::newPub (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_pub (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a SUB socket, and optionally subscribe to some prefix string. Default
//  action is connect.                                                          
QmlZsock *QmlZsockAttached::newSub (const QString &endpoint, const QString &subscribe) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_sub (endpoint.toUtf8().data(), subscribe.toUtf8().data());
    return retQ_;
};

///
//  Create a REQ socket. Default action is connect.
QmlZsock *QmlZsockAttached::newReq (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_req (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a REP socket. Default action is bind.
QmlZsock *QmlZsockAttached::newRep (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_rep (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a DEALER socket. Default action is connect.
QmlZsock *QmlZsockAttached::newDealer (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_dealer (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a ROUTER socket. Default action is bind.
QmlZsock *QmlZsockAttached::newRouter (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_router (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a PUSH socket. Default action is connect.
QmlZsock *QmlZsockAttached::newPush (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_push (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a PULL socket. Default action is bind.
QmlZsock *QmlZsockAttached::newPull (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_pull (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create an XPUB socket. Default action is bind.
QmlZsock *QmlZsockAttached::newXpub (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_xpub (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create an XSUB socket. Default action is connect.
QmlZsock *QmlZsockAttached::newXsub (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_xsub (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a PAIR socket. Default action is connect.
QmlZsock *QmlZsockAttached::newPair (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_pair (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a STREAM socket. Default action is connect.
QmlZsock *QmlZsockAttached::newStream (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_stream (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a SERVER socket. Default action is bind.
QmlZsock *QmlZsockAttached::newServer (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_server (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a CLIENT socket. Default action is connect.
QmlZsock *QmlZsockAttached::newClient (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_client (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Probe the supplied object, and report if it looks like a zsock_t.
//  Takes a polymorphic socket reference.                            
bool QmlZsockAttached::is (void *self) {
    return zsock_is (self);
};

///
//  Probe the supplied reference. If it looks like a zsock_t instance, return
//  the underlying libzmq socket handle; else if it looks like a file        
//  descriptor, return NULL; else if it looks like a libzmq socket handle,   
//  return the supplied value. Takes a polymorphic socket reference.         
void *QmlZsockAttached::resolve (void *self) {
    return zsock_resolve (self);
};

///
//  Self test of this class
void QmlZsockAttached::test (bool verbose) {
    zsock_test (verbose);
};

///
//  Create a new socket. Returns the new socket, or NULL if the new socket
//  could not be created. Note that the symbol zsock_new (and other       
//  constructors/destructors for zsock) are redirected to the *_checked   
//  variant, enabling intelligent socket leak detection. This can have    
//  performance implications if you use a LOT of sockets. To turn off this
//  redirection behaviour, define ZSOCK_NOCHECK.                          
QmlZsock *QmlZsockAttached::construct (int type) {
    QmlZsock *qmlSelf = new QmlZsock ();
    qmlSelf->self = zsock_new (type);
    return qmlSelf;
};

///
//  Destroy the socket. You must use this for any socket created via the
//  zsock_new method.                                                   
void QmlZsockAttached::destruct (QmlZsock *qmlSelf) {
    zsock_destroy (&qmlSelf->self);
};

/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
