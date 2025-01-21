#!/bin/bash

# The first parameter is passed as $1
image=$1

# File to store the current wallpaper path
wallpaper_file="$HOME/.current_wallpaper"

# Check if a parameter is provided
if [ -z "$image" ]; then
    echo "Please specify an image!"
    echo "Usage: $0 <path to image>"
    exit 1
fi

# Check if the specified file exists
if [ ! -f "$image" ]; then
    echo "File '$image' not found. Please check the path and try again."
    exit 1
fi

# Set the image as wallpaper using feh
feh --bg-scale "$image"

# Save the selected image path to ~/.current_wallpaper
echo "$image" > "$wallpaper_file"

# Success message
echo "Wallpaper successfully set: $image"
echo "Current wallpaper saved in: $wallpaper_file"

