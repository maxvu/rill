#!/bin/bash
for test_file in `ls -1a test | grep .test.c`; do
    echo "#include \"$test_file\""
done
