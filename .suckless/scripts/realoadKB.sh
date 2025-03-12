#!/bin/bash

# Check if the script is run as root
if [[ $EUID -ne 0 ]]; then
    # Use kdialog to prompt for a sudo password
    SUDO_PASSWORD=$(kdialog --password "Enter your sudo password" --title "Sudo Request")

    # If the user cancels the input
    if [ $? -ne 0 ]; then
        exit 1
    fi

    # Verify the entered password
    echo "$SUDO_PASSWORD" | sudo -S echo "" >/dev/null 2>&1
    if [ $? -ne 0 ]; then
        exit 1
    fi
else
    SUDO_PASSWORD=""
fi

# Find the keyboard device (from /proc/bus/input/devices)
KEYBOARD=$(grep -E "Handlers|EV=" /proc/bus/input/devices | grep -B1 "EV=120013" | grep -Po 'Handlers=.*?event\K\d+')

if [ -z "$KEYBOARD" ]; then
    exit 1
fi

DEVICE_PATH="/dev/input/event$KEYBOARD"

# Find the keyboard ID for xinput
XINPUT_ID=$(xinput list | grep -i 'keyboard' | grep -Po 'id=\d+' | grep -Po '\d+')

if [ -z "$XINPUT_ID" ]; then
    exit 1
fi

# Completely disable the keyboard via udevadm and xinput
echo "$SUDO_PASSWORD" | sudo -S udevadm control --stop-exec-queue
echo "$SUDO_PASSWORD" | sudo -S udevadm trigger --action=remove --subsystem-match=input --name-match="$DEVICE_PATH"

# Also disable via xinput for safety
xinput disable "$XINPUT_ID"

# Wait to simulate "removal"
sleep 2

# Re-add the keyboard device
echo "$SUDO_PASSWORD" | sudo -S udevadm trigger --action=add --subsystem-match=input --name-match="$DEVICE_PATH"
echo "$SUDO_PASSWORD" | sudo -S udevadm control --start-exec-queue

# Re-enable via xinput
xinput enable "$XINPUT_ID"

# Configure keyboard layouts
setxkbmap -option 'ctrl:nocaps'

# Notify user of success
notify-send -i none "🔃 Reload Keyboard" "The keyboard has been successfully reset and configured!"
