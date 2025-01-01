zstyle ':completion:*:descriptions' format '[%d]'
zstyle ':completion:*' list-colors ${(s.:.)LS_COLORS}
zstyle ':completion:*' menu select
zstyle ':fzf-tab:complete:*' fzf-preview \
  'if [[ -d $realpath ]]; then eza --tree --level=2 --icons $realpath; else bat --style=numbers --color=always $realpath || cat $realpath; fi'
zstyle ':fzf-tab:complete:*' fzf-preview-window down:15:wrap
zstyle ':fzf-tab:*' fzf-flags --height=70% \
                              --border \
                              --color=fg:#cdd6f4,bg:#1e1e2e,hl:#a6e3a1,fg+:#cdd6f4,bg+:#45475a,hl+:#f38ba8 \
                              --color=info:#89b4fa,prompt:#f5c2e7,pointer:#f38ba8,marker:#fab387,spinner:#94e2d5,border:#585b70
