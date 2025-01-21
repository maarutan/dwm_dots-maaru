function copypath {
  local file="${1:-.}"

  # Ensure absolute path
  [[ $file = /* ]] || file="$PWD/$file"

  # Clipboard command detection
  if command -v clipcopy &> /dev/null; then
    print -n "${file:a}" | clipcopy
  elif command -v xclip &> /dev/null; then
    print -n "${file:a}" | xclip -selection clipboard
  elif command -v pbcopy &> /dev/null; then
    print -n "${file:a}" | pbcopy
  else
    echo -e "\e[38;2;255;0;0mNo clipboard tool found. Install 'clipcopy', 'xclip', or 'pbcopy'.\e[0m" >&2
    return 1
  fi

  # Confirmation message with color #8AADF4
  echo -e "\e[38;2;138;173;244m${file:a} copied to clipboard.\e[0m"
}
