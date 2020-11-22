#!/bin/bash

pushd .
cd ./res
rm ../obj/default_res.zip
zip -r ../obj/default_res.zip *

pushd .
cd ../modules/packer
premake5 gmake || exit 
make || exit
popd 

popd 
# ./modules/packer obj/default_res.zip src/Gen/default_res DEFAULT_RES_SRC
./modules/packer/packer -c -i obj/default_res.zip -o src/Gen/default_res.c -d src/Gen/default_res.h -v DEFAULT_RES_SRC