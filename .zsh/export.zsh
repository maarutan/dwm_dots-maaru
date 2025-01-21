# ███████╗██╗  ██╗██████╗  ██████╗ ██████╗ ████████╗
# ██╔════╝╚██╗██╔╝██╔══██╗██╔═══██╗██╔══██╗╚══██╔══╝
# █████╗   ╚███╔╝ ██████╔╝██║   ██║██████╔╝   ██║
# ██╔══╝   ██╔██╗ ██╔═══╝ ██║   ██║██╔══██╗   ██║
# ███████╗██╔╝ ██╗██║     ╚██████╔╝██║  ██║   ██║
# ╚══════╝╚═╝  ╚═╝╚═╝      ╚═════╝ ╚═╝  ╚═╝   ╚═╝

# Export variables
export QT_QPA_PLATFORMTHEME=qt5ct
export PATH="$HOME/.local/share/nvim/mason/bin:$HOME/.cargo/bin:$HOME/.local/bin:$HOME/.npm-global/bin:$PATH"
export NVM_DIR="$HOME/.nvm"
export VISUAL=nvim
export EDITOR=nvim
export XMODIFIERS="@im=none"
export XDG_CURRENT_DESKTOP=dwm
export TERM=xterm-kitty

# History settings
HISTFILE=$HOME/.zsh/.zsh_history
HISTSIZE=10000
SAVEHIST=10000
setopt HIST_IGNORE_DUPS
setopt SHARE_HISTORY
setopt INC_APPEND_HISTORY
setopt HIST_REDUCE_BLANKS
setopt hist_ignore_all_dups
setopt hist_save_no_dups

# Autoload completion and configure
autoload -Uz compinit && compinit
zstyle ':completion:*' menu select
zstyle ':completion:*:descriptions' format '%B%d%b'
zstyle ':completion:*:messages' format '%B%U%S%m%u%s%b'
zstyle ':completion:*:warnings' format '%B%U%S%w%u%s%b'

# Disable automatic correction (if needed)
unsetopt CORRECT
unsetopt CORRECT_ALL

# FZF configuration
export FZF_DEFAULT_OPTS="
--reverse --ansi --no-multi
--bind=ctrl-u:up,ctrl-e:down,ctrl-n:backward-char,ctrl-i:forward-char,ctrl-b:backward-word,ctrl-h:forward-word
--border \
    --color=fg:#cdd6f4,bg:#1e1e2e,hl:#a6e3a1,fg+:#cdd6f4,bg+:#45475a,hl+:#f38ba8 \
    --color=info:#89b4fa,prompt:#f5c2e7,pointer:#f38ba8,marker:#fab387,spinner:#94e2d5,border:#585b70
"

# Preview support for FZF
if [[ -v __FZF_PREVIEW ]]; then
	unset __FZF_PREVIEW
FZF_DEFAULT_OPTS="$FZF_DEFAULT_OPTS
--preview='(
    bat --color=always {} ||
    tree -ahpCL 3 $__TREE_IGNORE {}
) 2>/dev/null | head -n 100'"
fi

# Initialize Zoxide
eval "$(zoxide init zsh)"

# Load NVM
[ -s "$NVM_DIR/nvm.sh" ] && . "$NVM_DIR/nvm.sh"  # Load NVM
[ -s "$NVM_DIR/bash_completion" ] && . "$NVM_DIR/bash_completion"  # Load NVM bash_completion

# Key bindings for deletion
bindkey "^H" backward-delete-char
bindkey "^W" backward-kill-word
bindkey "^?" backward-delete-char

# Ensure paths are clean
export PATH=$(echo $PATH | tr ':' '\n' | awk '!seen[$0]++' | tr '\n' ':' | sed 's/:$//')

