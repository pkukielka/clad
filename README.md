Clad
====
  
Standalone Clang service for easier integration with various editors and IDEs
  
## About
The goal of Clad is to provide platform independent, persistent service which provides API very similar to libclang C API, but can be accessed easily from any programming language without need to write C bindings.  
This should significantly simplify process of building stateless commandline utilities based on Clang (state is moved to service instead, you don't need to reparse all files every time you run your tool) as well as testing Clang using other languages, even exotic ones.  
  
## Demo
In the 'example' directory you can find demo of in-browser C++ editor built with Clad and javascript client.  
To run it you need to compile and run Clad server, and then start  web server in the 'example' directory:  

```bash
~/clad/build/src$ ./clad_serv &
~/clad/example$ python -m SimpleHTTPServer 8080
```

For now functionality is limited to marking errors in the code and showind diagnostic messages,  
but I'm planning to add fix-its and live-completion as well. So far it looks like this:  
![alt text](https://github.com/pkukielka/clad/raw/master/example/img/editor.png "Simple editor build with Clad")  

## Building the server
To build Clad you need to have:
- Clang 3.2
- CMake 2.6
- Thrift 0.9
- GTest 1.6
  
You don't need to have full Clang installation but CMake must be able to find libclang 3.2 headers and library.
If you will try to use other Clang version there is high chance that it wont compile or will break on runtime.  
Your Thrift and GTest versions can be different, but I cannot guarantee that it will work then.  
Building Clad is pretty straightforward:

```bash
~/$ git clone https://github.com/pkukielka/clad.git  
~/$ cd clad && mkdir build && cd build  
~/clad/build$ cmake ..  
~/clad/build$ make
```

You can also run tests to ensure that everything works as intended:

```bash
~/clad/build$ make test
```

## Client API
Clients APIs are not part of the Clad distribution because of two reasons:
- there is ~14 languages supported, a it too many to manage them easily (you can find full list inside Thrift documentation: http://thrift.apache.org/docs/features/)
- it's very easy to generate all the files:

```bash
~/clad/build$ thrift -r --gen java ../thrift/Clang.thrift
```

This will generate full API for java. To see list of all available generators open terminal and type:

```
thrift -help
```

##Roadmap
Plan for now looks like that:  

* Finish demo of using Clad with javascript
* Add missing libclang API functions (like for cursors)
* Cover existing Clad API with tests; also do some performance checks
* Experiment with libtooling, clang refactoring tools, etc.

I would say it can take another month to cover first 3 points.
