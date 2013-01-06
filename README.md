clang-serv
====

Standalone Clang service for easier integration with various editors and IDEs


## About
The goal of clang-serv is to provide platform independent, persistent service which:

* Provide API similar to libclang and can do everything which libclang can
* Can be accessed easily from any programming language without need to writing C bindings
* [Future] Provide useful refactoring tools

Some of the goals are quite similar to the ones which you can find here:  
http://clang-developers.42468.n3.nabble.com/RFC-A-proposal-for-a-Clang-based-service-architecture-td4024449.html  
However, there are also some differences:

* Even if clang-serv will be standalone server which can communicate through sockets it's intended to use only on localhost.
  This can look like unnecessary limitation, but it's here for a purpose. Architecture of external service which can be 
  hosted remotely and used by multiple users would need to be totally different and probably much more complicated.
* I'm not going to invent any special binary protocol or whatever. Clang-serv will be based on Thrift, because it will be 
  easier to implement and more versatile (clients for many languages for free). I'm aiming for 0 (zero) logic needed on
  the client side. Only the code provided by Thrift automatically. This leads to the next point.
* There will be no .clangrc files. They would require additional logic for every possible client, and I can imagine situation where someone 
  want to implement this in other way. Whole administration of the service will be possible through RPC API.
  Well, except starting the service, this will be responsibility of the editor.

Whole idea is still young and there is high chance that something will change in the meantime.
All adjustments will be made after minimum viable prototype will be ready.
