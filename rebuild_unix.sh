#!/usr/bin/env bash
#
# \file  rebuild_unix.sh
# \brief full rebuild
#


qmake && make clean && qmake && make
