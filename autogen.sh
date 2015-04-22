#!/bin/bash

echo "Generating autotools files; this may take a while ..."
aclocal
autoheader
automake --include-deps --add-missing --copy
autoconf
