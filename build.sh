#!/bin/bash

# ######################################
# Script de build du projet SITL
# Author : bmathieugit
# Project : sitl
# ######################################

echo "###########################"
echo "# Chargement des arguments"
echo "###########################"

[[ $@ == *"-src"* ]] && buildsrc=false || buildsrc=true
[[ $@ == *"-lib"* ]] && buildlib=false || buildlib=true
[[ $@ == *"-test"* ]] && buildtest=false || buildtest=true
[[ $@ == *"-main"* ]] && buildmain=false || buildmain=true
[[ $@ == *"-clean"* ]] && buildclean=false || buildclean=true

echo "###########################"
echo "# Chargement des variables"
echo "###########################"

srcdir="sources"
libsdir="libs"
testsdir="tests"
objectsdir="objects"

libsdirs="$libsdir/lib"

compiler="g++"
program="sitl.exe"
main="sitl.cpp"
4
cflags="-Wall -Werror -pedantic -O3 -std=c++20 -save-temps"

cilibs="-Ilibs"
cisources="-Isources"
citests="-Itests"

tempsdirs="$objectsdir"

mkdir -p $objectsdir

if [ $buildlib = true ]; then

  echo "###########################"
  echo "# Build des libs"
  echo "###########################"

  for dir in $libsdirs; do
    for fcpp in $dir/*.cpp; do
      bn="lib-$(basename $fcpp)"
      echo "$compiler -o $objectsdir/$bn.o -c $fcpp $cflags $cilibs"
      $compiler -o $objectsdir/$bn.o -c $fcpp $cflags $cilibs
    done
  done
fi

if [ $buildsrc = true ]; then

  echo "###########################"
  echo "# Build des sources"
  echo "###########################"

  for fcpp in $srcdir/*.cpp; do
    bn="src-$(basename $fcpp)"
    echo "$compiler -o $objectsdir/$bn.o -c $fcpp $cflags $cilibs $cisources"
    $compiler -o $objectsdir/$bn.o -c $fcpp $cflags $cilibs $cisources
  done
fi

if [ $buildtest = true ]; then

  echo "###########################"
  echo "# Build des tests"
  echo "###########################"

  objects=""

  for o in $objectsdir/lib-*.o; do
    objects+="$o "
  done

  for o in $objectsdir/src-*.o; do
    objects+="$o "
  done

  for fcpp in $testsdir/*.cpp; do
    bn="test-$(basename $fcpp)"
    echo "$compiler -o $objectsdir/$bn.o -c $fcpp $cflags $cilibs $cisources $citests"
    $compiler -o $objectsdir/$bn.o -c $fcpp $cflags $cilibs $cisources $citests
    $compiler -o $objectsdir/$bn.exe $objects $objectsdir/$bn.o
    ./$objectsdir/$bn.exe
  done
fi

if [ $buildmain = true ]; then

  echo "###########################"
  echo "# Build du main"
  echo "###########################"

  objects=""

  for o in $objectsdir/lib-*.o; do
    objects+="$o "
  done

  for o in $objectsdir/src-*.o; do
    objects+="$o "
  done

  echo "$compiler -o $objectsdir/main-$main.o -c $main $cflags $cilibs $cisources"
  $compiler -o $objectsdir/main-$main.o -c $main $cflags $cilibs $cisources
  echo "$compiler -o $objectsdir/$program $objects $objectsdir/main-$main.o $cflags"
  $compiler -o $objectsdir/$program $objects $objectsdir/main-$main.o $cflags
  ./$objectsdir/$program
fi

echo "###########################"
echo "# Mesure des fichiers asm"
echo "###########################"
wc -l $objectsdir/*.s;


if [ $buildclean = true ]; then

  echo "###########################"
  echo "# Clean des fichiers temporaires"
  echo "###########################"

  rm -rf $tempsdirs
fi
