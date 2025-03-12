import curses
import os
import subprocess

menu = ["connections", "connect list", "get ip", "radio", "exit"]


def main(stdscr):
    while True:
        stdscr.clear()
        win = curses.newwin(20, 50, 0, 40)
        win.box()
        win.addstr(0, 2, "Network Manager")
        win.refresh()
        for i, m in enumerate(menu):
            win.addstr(i + 1, 2, m)
        win.refresh()
        key = win.getch()
        if key == ord("q"):
            break


curses.wrapper(main)
