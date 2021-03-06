SKALL
-----
SKALL is a minimal, experimental UNIX shell.

License
-------
No; it's put in the public domain by the author.

Current Features
----------------
Not much yet, but:

* Command execution :-)
* Readline support with history and simple globbing
* Catches a few signals
* Get and set shell variables
* Get and set environment variables
* Quoted strings with some escape sequences
* Tab-completion for files (via readline)

Glaringly missing features
--------------------------

* Separating commands with semicolon
* Process pipe plumbing
* Complete signaling support
* Globbing
* Job control
* More escape sequences
* ... and much more

Building from source
--------------------

You need autotools, sorun

    $ ./autogen.sh
    $ ./configure
    $ make -j
    $ src/skall

If you don't have autotools, you may be able to do

    $ gcc -std=C99 -o skall -Iinclude src/*.c

Example session
---------------

    $ ./skall
    skall> help
    skall is a minimal, experimental unix shell

    builtin commands:
    help cd $? exit
    skall> ls
    Makefile	README.md	skall		skall.c
    skall> cd /
    chdir to '/'
    skall> pwd
    /
    skall> cd private
    chdir to 'private'
    skall> ls
    etc		tftpboot	tmp		var
    skall> ls -la
    total 0
    drwxr-xr-x@   6 root  wheel   204 21 jul  2011 .
    drwxr-xr-x   35 root  wheel  1258 29 mai 09:56 ..
    drwxr-xr-x  110 root  wheel  3740 14 mai 19:53 etc
    drwxr-xr-x    2 root  wheel    68 13 jun  2011 tftpboot
    drwxrwxrwt   19 root  wheel   646 31 mai 02:37 tmp
    drwxr-xr-x   29 root  wheel   986 22 jul  2011 var
    skall> uname
    Darwin
    skall> echo ribbit
    ribbit
    skall> exit

Author
------
Christian Stigen Larsen, http://csl.name
