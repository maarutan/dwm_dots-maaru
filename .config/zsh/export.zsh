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
export VISUAL=code
export EDITOR=nvim
export XMODIFIERS="@im=none"
export XDG_CURRENT_DESKTOP=dwm
export TERM=xterm-kitty

# History settings
HISTFILE=$HOME/.config/zsh/.zsh_history
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
--height=100%
--border
--preview '([[ -d {} ]] && eza --tree --level=2 --icons {} || bat --style=numbers --color=always {} || cat {})'
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

# Ensure paths are clean
export PATH=$(echo $PATH | tr ':' '\n' | awk '!seen[$0]++' | tr '\n' ':' | sed 's/:$//')

