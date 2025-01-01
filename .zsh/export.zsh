# ███████╗██╗  ██╗██████╗  ██████╗ ██████╗ ████████╗
# ██╔════╝╚██╗██╔╝██╔══██╗██╔═══██╗██╔══██╗╚══██╔══╝
# █████╗   ╚███╔╝ ██████╔╝██║   ██║██████╔╝   ██║   
# ██╔══╝   ██╔██╗ ██╔═══╝ ██║   ██║██╔══██╗   ██║   
# ███████╗██╔╝ ██╗██║     ╚██████╔╝██║  ██║   ██║   
# ╚══════╝╚═╝  ╚═╝╚═╝      ╚═════╝ ╚═╝  ╚═╝   ╚═╝  
# export
export QT_QPA_PLATFORMTHEME=qt5ct
export NVM_DIR="$HOME/.nvm"
export VISUAL=nvim;
export EDITOR=nvim;
export PATH=$PATH:$HOME/.local/bin
export PATH=$HOME/.local/bin:$PATH
export XMODIFIERS="@im=none"
export ZSH="$HOME/.oh-my-zsh"
export PATH=~/.npm-global/bin:$PATH
export XDG_CURRENT_DESKTOP=dwm
setopt CORRECT
setopt CORRECT_ALL
HISTFILE=$HOME/.zsh/.zsh_history          
HISTSIZE=10000                   
SAVEHIST=10000                   
setopt HIST_IGNORE_DUPS          
setopt SHARE_HISTORY             
setopt INC_APPEND_HISTORY        
setopt HIST_REDUCE_BLANKS        
export TERM=xterm-kitty
export FZF_DEFAULT_OPTS="
--reverse --ansi --no-multi
--bind=ctrl-u:up,ctrl-e:down,ctrl-n:backward-char,ctrl-i:forward-char,ctrl-b:backward-word,ctrl-h:forward-word
                              --border \
                              --color=fg:#cdd6f4,bg:#1e1e2e,hl:#a6e3a1,fg+:#cdd6f4,bg+:#45475a,hl+:#f38ba8 \
                              --color=info:#89b4fa,prompt:#f5c2e7,pointer:#f38ba8,marker:#fab387,spinner:#94e2d5,border:#585b70
"
if [[ -v __FZF_PREVIEW ]]; then
	unset __FZF_PREVIEW
	FZF_DEFAULT_OPTS="$FZF_DEFAULT_OPTS
--preview='(
	bat --color=always {} ||
	tree -ahpCL 3 $__TREE_IGNORE {}
) 2>/dev/null | head -n 100'"
fi

# eva
eval "$(zoxide init zsh)"

# Load NVM
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion
