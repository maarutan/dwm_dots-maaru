#  █████╗ ██╗     ██╗ █████╗ ███████╗███████╗███████╗
# ██╔══██╗██║     ██║██╔══██╗██╔════╝██╔════╝██╔════╝
# ███████║██║     ██║███████║███████╗█████╗  ███████╗
# ██╔══██║██║     ██║██╔══██║╚════██║██╔══╝  ╚════██║
# ██║  ██║███████╗██║██║  ██║███████║███████╗███████║
# ╚═╝  ╚═╝╚══════╝╚═╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝


EXPLORE="yazi"
ROOTEXPLORE="yazi"

EDITOR="nvim"
ROOTEDITOR="nvim"

# change directory
alias ..="cd .."
alias ...="cd ../.."
alias ~="cd ~"
alias go="cd"

# system
alias cls="clear && exec $(basename $SHELL)"
alias cls!="clear"
alias rzh="rm -rf $HOME/.zsh/.zsh_history"
alias nzh="nvim $HOME/.zsh/.zsh_history"
alias ex="exit"
alias pg="ping google.com"
alias fl="touch"
alias dr="mkdir"
alias rm!="rm -rf"
alias rm="rm -r"
alias ll="eza -l -g --icons"
alias la='exa -a --icons --color'
alias lt='exa --tree --icons --color'
alias ls='exa --icons --color=auto'
alias e=$"EXPLORE"
alias re="sudo -E \${ROOTEXPLORE}"
alias n=$"EDITOR"
alias rn="sudo -E \${ROOTEDITOR}"
alias cpp="copypath"

# utils
alias g="z"
alias walchoice="$HOME/wallpapers/.choise.sh"
alias gay="$HOME/.suckless/scripts/gay.sh"
alias nzsh="nvim ~/.zshrc"
alias hzsh="nvim $HOME/.zsh/.zsh_history"
alias matrix="unimatrix -b -s 95  -c blue"
alias neo="$HOME/.config/neofetch/.startFetch.sh"
alias bfetch="$HOME/.suckless/scripts/bestfetch.sh"
alias fetch="$HOME/.suckless/scripts/fetch.sh"
alias pwall="$HOME/.suckless/scripts/PicWall.sh"
alias clock="peaclock"
alias goo="/usr/bin/go"
