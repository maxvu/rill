#!/usr/bin/env bash
set -euo pipefail

DIR=$(dirname "$0")

TEST_FILES=$(find $DIR/tests/ -regex .*\.c)
TESTS=$(ctags -x --c-types=f $TEST_FILES | awk 'NR==1{print $1}')
DECLARATIONS=$(echo $TESTS | sed -E 's/^.*$/void \0 ();/g')
INVOCATIONS=$(echo $TESTS | sed -E 's/^.*$/\0();/g')

MANIFEST_HEADER=$(dirname "$0")/manifest.h
MANIFEST_SOURCE=$(dirname "$0")/manifest.c

BANNER_MSG="// automatically-generated file - see 'generate.sh'\n"

echo -e $BANNER_MSG > $MANIFEST_HEADER
echo -e "#ifndef MANIFEST_H" >> $MANIFEST_HEADER
echo -e "#define MANIFEST_H" >> $MANIFEST_HEADER

echo -e "void __run_all_tests ();\n" >> $MANIFEST_HEADER
echo $DECLARATIONS >> $MANIFEST_HEADER
echo -e "\n" >> $MANIFEST_HEADER

echo -e "#endif" >> $MANIFEST_HEADER

echo -e $BANNER_MSG > $MANIFEST_SOURCE
echo -e '#include "test/manifest.h"\n' >> $MANIFEST_SOURCE
echo -e "void __run_all_tests () {\n" >> $MANIFEST_SOURCE
echo $INVOCATIONS >> $MANIFEST_SOURCE
echo -e "\n}" >> $MANIFEST_SOURCE
