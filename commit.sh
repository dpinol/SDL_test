#!/bin/bash
FILES=".gitignore utils/*.cpp utils/*.h *2 assets/* *.xml *.sh  *.cpp *.h Makefile *.pro*"
git add $FILES
git commit $FILES

