#!/bin/bash

c_name="main"
build="build.sh"

if [[ ! -f $c_name ]] ; then
	echo -e "C programm not found, launching Makefile..."
	if [[ ! -f "makefile" ]] ; then
		echo "Error : Makefile not found" >&2
		exit 1
	else
		output_make=$(make 2>&1)
		success_make=$?
		if [[ $success_make -ne 0 ]] ; then
			echo "Error with Makefile : $output_make" >&2
			exit 1
		fi
        echo -e "COMPILE DONE"
        echo -e "LAUNCHING EXE..."

        ./$c_name

        rm *.o
	fi
else
    echo -e "C programm found, recompile it..."
    rm main

    ./$build
fi

