#!/usr/bin/env bash
set -euo pipefail

DIR=$(dirname "$0")

TEST_FILES=$(find $DIR/../ -maxdepth 3 -regex .*/tests/.*_test\.c | sort)
TESTS=$(ctags -x --c-types=f $TEST_FILES | awk 'NR==1{print $1}')
DECLARATIONS=$(echo $TESTS | sed -E 's/^.*$/void \0 ();/g')
INVOCATIONS=$(echo $TESTS | sed -E 's/^.*$/\0();/g')

MANIFEST_HEADER=$(dirname "$0")/include/manifest.h
MANIFEST_SOURCE=$(dirname "$0")/src/manifest.c


echo -e "void __run_all_tests ();\n" > $MANIFEST_HEADER
echo $DECLARATIONS >> $MANIFEST_HEADER
echo -e "\n" >> $MANIFEST_HEADER

echo -e '#include "manifest.h"\n' > $MANIFEST_SOURCE
echo -e "void __run_all_tests () {\n" >> $MANIFEST_SOURCE
echo $INVOCATIONS >> $MANIFEST_SOURCE
echo -e "\n}" >> $MANIFEST_SOURCE
