#! Quick setup for emscripten

This project demonstrates a very simple example of getting [emscripten][] up and running with the smallest effort.  It assumes only that you have installed [Vagrant][] and are comfortable with the idea of working inside a VM.

## Getting started

The only real pre-requisite is that you have [Vagrant][] installed on your machine.  If not, you should install it now.  The following steps assume familiarity with a command line interface and basic usage of Vagrant.

* Navigate to this directory in a terminal.
* Provision the VM by running the command: `vagrant up`
* Get a cup of coffee.  Maybe read a book.  Provisioning a new VM from scratch will take a while.
* Once provisioned, enter into the VM using `vagrant ssh`
* Navigate to the `vagrant` folder at the root of the VM (`cd /vagrant`).
* Use emscripten to compile example.js from example.cpp: `~/dev/emscripten/emcc --post-js post.js --bind -std=c++11 example.cpp -o example.js`
* Return from the VM to your primary environment and open example.html in a web browser.

You should see a bare page with a couple of lines of text indicating values.  If you, then you've just compiled and run C++ in the browser using emscripten.

## Breaking down the `emcc` command

If you're familiar with vagrant and the command line, few of the commands above are confusing.  If you're familiar with running `gcc` or `clang` from the command line, the compilation phase probably isn't that confusing.  However, if you're unfamiliar with that step (always use Xcode or Visual Studio, eh?) or didn't recognize the emscripten-specific flags, this is a brief breakdown of the command.

    ~/dev/emscripten/emcc --post-js post.js --bind -std=c++11 example.cpp -o example.js	

* `~/dev/emscripten/emcc` -- This is a path to `emcc`, the emscripten compiler.  This is a drop in replacement for `gcc`/`clang` for your C and C++ code.
* `--post-js post.js` -- This flag and file path are used to bundle additional javascript code.  There's also a "pre" version, if that suits your fancy.
* `--bind` -- This flag tells emscripten to create bindings.  This is important if you're hosting the C++ inside a Javascript application.  Otherwise, you'd have to provide an implementation for `main` and do all of your coding in C++.
* `-std=c++11` -- Use c++11 semantics.  I think you should use "c++14" if possible.  Keep up with the standard.
* `example.cpp` -- A filepath that represents our C++ code.
* `-o example.js` -- The output flag and location.  You can specify different output types based on the extension of the output file.

## What is demonstrated

This project demonstrates primarily a simple Vagrant file to set up an emscripten development environment.  The shell script in the Vagrantfile can theoretically be run on any system with `apt-get` or be easily converted to use any other means to install emscripten's requirements.  The VM created by Vagrant is a simple and reliable environment that can be used for the compilation of C++ into JS.

This also has a very basic demonstration of using emscripten's bindings to bridge the interaction from a Javascript application to the C++ backing.

post.js demonstrates using `onRuntimeInitialized` to indicate when you can interact with C++-compiled code.  You can't just start interacting with the C++ functions and objects as soon as the Javascript file is loaded.

## Where to go from here

The VM's `/vagrant` directory should mirror this repository.  You can deleted all of the files (I'd leave the Vagrantfile in case you wanted to re-provision in the future, but that's up to you) in this folder and start developing an awesome JS library in C++ or leveraging existing C++ code in your JS application.

The generated Javascript is pretty big for what little is being done.  You can mess around with optimization flags (`-O<x>`) and see how much smaller the generated JS file can be.  This codebase is too insignificant to actually measure speed optimizations, but if you wind up with some complex C++ code you could swing back around and try the various options.

You could create multiple C++ files, compile them to object files, and then link them into a JS file using emscripten (`emcc foo.cpp -o foo.bc && emcc bar.cpp -o bar.bc && emcc foo.bc bar.bc -o baz.js`).  Note that I'm using a relatively agnostic bit code object file in the example rather than `.o` files.  It doesn't really matter for our purposes here.

You could compile a third party library using `emconfigure` or `emmake` or `emcmake`.  Or write your own on top of these idioms.

## Contact information

[Grayson Hansard](mailto:grayson.hansard@gmail.com)  
[@Grayson](http://twitter.com/Grayson)

[emscripten]: https://kripken.github.io/emscripten-site/index.html
[Vagrant]: https://www.vagrantup.com