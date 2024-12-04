#!/bin/bash

select option in "Start Process" "Stop Process" "Exit"
do
    case $option in
        "Start Process")
            echo "Starting the process..."
            # ここにプロセスを開始するコマンドを記述
            cc main.c -Iincludes -Ilibft -o pipex -Llibft -lft
            ./pipex
            break
            ;;
        "Stop Process")
            echo "Stopping the process..."
            # ここにプロセスを停止するコマンドを記述
            break
            ;;
        "Exit")
            echo "Exiting the program."
            break
            ;;
        *)
            echo "Invalid option. Please try again."
            ;;
    esac
done
