#!/bin/bash
FILES=".gitignore `find . -name '*.cpp'` `find . -name '*.h'` *cpp2 *h2 assets/* *.xml *.sh  Makefile *.pro"
git add $FILES
git commit $FILES $*

