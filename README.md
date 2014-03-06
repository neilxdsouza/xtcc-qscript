xtcc-qscript
============

Open Source Compilers for Data Collection and Cross Tabulation

Requirements:
g++, flex, bison. For Mobile - emscripten and phonegap (we are using 2.7.0)
emscripten itself requires clang .
compilation to Wt and wxWidgets is lagging behind the mobile build

Build:

>git clone https://github.com/neilxdsouza/xtcc-qscript qscript-other-specify

>cd qscript-other-specify

>git checkout other-specify

>cd xtcc/qscript/stubs/simple_compiler

>make -f CustomQScriptMakefile local_install

The binary should be copied to simple_compiler/bin
>ls bin

==> output
 qscript_wq2

pwd

==> output
/home/nxd/Progs/qscript-other-specify/xtcc/qscript/stubs/simple_compiler

```> export QSCRIPT_HOME=`pwd` ```

test scripts are in inputs

>cd inputs

try building one of the scripts there

> $QSCRIPT_HOME/bin/qscript_wq2  -om --emscripten   -f  geocode_in_for_loop.qscript 


 our android app is in the Google app store - search and install QScript. 
 Deploying to qscript requires an account on our server
 if you want to try it out - ask me (n x d underscore i n at yahoo dot com) for an account
 http://xtcc-qscript.com
 





