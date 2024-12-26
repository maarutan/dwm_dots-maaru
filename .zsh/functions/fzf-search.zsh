function fzf_files() {
  local selection=$(find . -maxdepth 1 -type f -exec echo "{}" \; \
    | fzf --preview 'bat --style=numbers --color=always {} || ls -la {}' \
          --preview-window=right:60% \
          --height=80% \
          --layout=reverse \
          --border \
          --ansi \
          --header="Search Files")

  if [[ -n "$selection" ]]; then
    LBUFFER+="$selection "
    zle redisplay
  fi
}

function fzf_directories() {
  local selection=$(find . -maxdepth 1 -type d -exec echo "{}" \; \
    | fzf --preview 'ls -la --color=always {}' \
          --preview-window=right:60% \
          --height=80% \
          --layout=reverse \
          --border \
          --ansi \
          --header="Search Directories")

  if [[ -n "$selection" ]]; then
    LBUFFER+="$selection "
    zle redisplay
  fi
}

zle -N fzf_files
zle -N fzf_directories

bindkey '^F' fzf_files
bindkey '^G' fzf_directories
