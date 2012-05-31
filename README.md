SKALL
-----
SKALL is a minimal, experimental UNIX shell.

License
-------
No; it's put in the public domain by the author.

Current Features
----------------
Command execution. :-)

Missing features
----------------
It should at least handle signals and support pipe redirection.  We'll see.

Example session
---------------
    Script started on Thu May 31 02:38:18 2012
    [?1034h~/devel/skall csl$ make
    cc     skall.c   -o skall
    ~/devel/skall csl$ ./skall 
    skall> help
    skall is a minimal, experimental unix shell
    
    builtin commands:
    help cd $? 
    skall> ls
    Makefile	README.md	skall		skall.c
    skall> cd /
    chdir to '/'
    skall> cd    pwd
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
    skall> echo nice    c ribbit
    ribbit
    skall> exit    ^D~/devel/skall csl$ exit

Author
------
Christian Stigen Larsen, http://csl.sublevel3.org
