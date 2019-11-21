#!/bin/bash

absolute_fname=`readlink -e "$0"`
current_dir=`dirname "$absolute_fname"` 

if [ -n $1 ]
then
	python3 $current_dir/run_tests.py $1
fi
