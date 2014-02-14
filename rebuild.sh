#!/usr/bin/env bash
#
# \file  rebuild.sh
# \brief rebuild project
#


# vars

echo "******************** Git ********************"
git pull --rebase && git submodule foreach git pull
echo ""

echo "******************** xLib ********************"
cd ./xLib/Build
./makefile_gcc.sh
cd ../..
echo ""

echo "******************** Widgets ********************"
cd ./Widgets/CDbImage
./rebuild_unix.sh
cd ../..
echo ""

echo "******************** XXXDb ********************"
qmake && make clean && qmake && make
echo ""
