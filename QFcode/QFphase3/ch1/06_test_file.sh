#! /bin/bash

echo "please input a filename >>> "
read FILE

test -e $FILE
echo "存在？$?"