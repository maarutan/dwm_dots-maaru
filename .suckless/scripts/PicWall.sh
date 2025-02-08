#!/bin/bash
# Directory with wallpapers
WALLPAPER_DIR="${HOME}/wallpapers"
CURRENT_WALLPAPER_FILE="${HOME}/.current_wallpaper"

# Check if the directory exists
if [[ ! -d "$WALLPAPER_DIR" ]]; then
  echo "The directory $WALLPAPER_DIR does not exist."
  exit 1
fi

# Check if chafa is installed
if ! command -v chafa &> /dev/null; then
  echo "'chafa' is required for image previews. Please install it and try again."
  exit 1
fi

# Check if feh is installed
if ! command -v feh &> /dev/null; then
  echo "'feh' is required to set wallpapers. Please install it and try again."
  exit 1
fi

# Calculate terminal dimensions
TERMINAL_WIDTH=$(tput cols)
TERMINAL_HEIGHT=$(tput lines)

# Calculate dynamic preview size, limiting to small dimensions
PREVIEW_WIDTH=$(( TERMINAL_WIDTH / 4 ))  # 1/4 of the terminal width
PREVIEW_HEIGHT=$(( TERMINAL_HEIGHT / 4 ))  # 1/4 of the terminal height

# Ensure preview size is not less than 20x10
if (( PREVIEW_WIDTH < 20 )); then
  PREVIEW_WIDTH=30
fi
if (( PREVIEW_HEIGHT < 10 )); then
  PREVIEW_HEIGHT=20
fi

# Main loop
while true; do
  # Display the menu
  echo "\nSelect a wallpaper or press Ctrl+C to exit."
  selected=$(find "$WALLPAPER_DIR" -type f \( -iname "*.jpg" -o -iname "*.png" -o -iname "*.jpeg" \) | \
    fzf --preview "chafa --fill=block --size=${PREVIEW_WIDTH}x${PREVIEW_HEIGHT} --colors=256 {}" \
        --preview-window=right:50%:wrap)

  if [[ -n "$selected" ]]; then
    echo "You selected:"
    echo "Name: $(basename "$selected")"
    echo "Path: $(realpath "$selected")"


    # Set the wallpaper using feh
    feh --bg-scale "$selected"

    # Save the current wallpaper path
    echo "$(realpath "$selected")" > "$CURRENT_WALLPAPER_FILE"
    echo "Wallpaper set and path saved to $CURRENT_WALLPAPER_FILE."
  else
    echo "Nothing selected. Returning to menu."
  fi

done
