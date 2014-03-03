#!/bin/bash
FILES=".gitignore `find . -name '*.cpp'` `find . -name '*.h'` *2 assets/* *.xml *.sh  Makefile *.pro*"
git add $FILES
git commit $FILES

