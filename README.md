# Jam Game Engine

Just a small multimedia framework. 

## Compiling the library

The library is static and contains all of the symbols used in most of its dependencies.

 - Compile all submodules (completed in build_deps.sh/bat scripts)
 - Compress the default resources into a single archive (compress_res.sh/bat script)
 - Generate the build files for the library (premake gmake/vs2019)
 - Run the build system (make or visual studio etc)