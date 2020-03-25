#!/bin/bash

cd ../res/
rm ../obj/default_res.zip
zip -r ../obj/default_res.zip *

pushd .
cd ../packer
premake5 gmake || exit 
make || exit
popd 

cd ..
./packer/packer obj/default_res.zip src/Gen/default_res DEFAULT_RES_SRC