#!/bin/bash

absolute_fname=`readlink -e "$0"`
current_dir=`dirname "$absolute_fname"` 

if [ -n $1 ]
then
	for file in $current_dir/tests/$1/*
	do
		test_string=`line < "$file"`
		expected_out=`tail -n +2 < "$file"`
		out=`$current_dir/bin/$1 "$test_string"`

		if [ `echo $?` != "0" ]
		then
			echo "Bad exit code"
		fi

		if [ "$expected_out" != "$out" ]
		then
			echo "Wrong output"
		fi
	done
fi
