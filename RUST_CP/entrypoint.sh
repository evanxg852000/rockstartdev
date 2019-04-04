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
  run           : test the application  
  """
}

case "$1" in

  bash )
    bash
  ;;

  eval )
    eval "${@:2}"
  ;;

  build )
    eval "cargo build ${@:2}"
  ;;

  test )
    eval "cargo test ${@:2}"
  ;;

  run )
    eval "./target/release/app ${@:2}"
  ;;

  * )
    show_help
  ;;

esac
