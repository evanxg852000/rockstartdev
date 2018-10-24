#!/bin/bash
set -e

# Define help message
show_help() {
  echo """
  Commands
  ---------------------------------------------------------
  bash          : run bash
  eval          : eval shell command
  build         : build the app [arg: path to cmake folder] 
  run           : run the application [arg: path to program] 
  """
}

build(){
    cd "$1/build"
    cmake ..
    cmake --build .
}

case "$1" in

  bash )
    bash
  ;;

  eval )
    eval "${@:2}"
  ;;

  build )
    build "${@:2}"
  ;;

  run )
    eval "${@:2}"
  ;;

  * )
    show_help
  ;;

esac
