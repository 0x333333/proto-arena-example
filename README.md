# Arena Proto Buffer Example

This repository is an example of how to use arena pointer with proto buffer.

These examples are part of the Protocol Buffers tutorial, located at:
  https://developers.google.com/protocol-buffers/docs/tutorials

## Build the example using bazel

The example requires bazel 0.5.4 or newer to build. You can download/install
the latest version of bazel from bazel's release page:

    https://github.com/bazelbuild/bazel/releases

Once you have bazel installed, simply run the following command in this examples
directory to build the code:

    $ bazel build :all

Then you can run the built binary:

    $ bazel-bin/add_person_cpp addressbook.data

To use protobuf in your own bazel project, please follow instructions in the
[BUILD](BUILD) file and [WORKSPACE](WORKSPACE) file.

## Build the example using make

You must install the protobuf package before you can build it using make. The
minimum requirement is to install protocol compiler (i.e., the protoc binary)
and the protobuf runtime for the language you want to build.

You can simply run "make" to build the example for all languages (except for
Go). However, since different language has different installation requirement,
it will likely fail. It's better to follow individual instrutions below to
build only the language you are interested in.

### C++

You can follow instructions in [../src/README.md](../src/README.md) to install
protoc and protobuf C++ runtime from source.

Then run "make cpp" in this examples directory to build the C++ example. It
will create two executables: add_person_cpp and list_people_cpp. These programs
simply take an address book file as their parameter. The add_person_cpp
programs will create the file if it doesn't already exist.

To run the examples:

    $ ./add_person_cpp addressbook.data
    $ ./list_people_cpp addressbook.data

Note that on some platforms you may have to edit the Makefile and remove
"-lpthread" from the linker commands (perhaps replacing it with something else).
We didn't do this automatically because we wanted to keep the example simple.