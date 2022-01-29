#!/bin/bash

cd .build/

cmake ..

make

cp -r cache_app ../