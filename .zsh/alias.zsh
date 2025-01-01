#  █████╗ ██╗     ██╗ █████╗ ███████╗███████╗███████╗
# ██╔══██╗██║     ██║██╔══██╗██╔════╝██╔════╝██╔════╝
# ███████║██║     ██║███████║███████╗█████╗  ███████╗
# ██╔══██║██║     ██║██╔══██║╚════██║██╔══╝  ╚════██║
# ██║  ██║███████╗██║██║  ██║███████║███████╗███████║
# ╚═╝  ╚═╝╚══════╝╚═╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
 


# change directory
alias ..="cd .."
alias ...="cd ../.."
alias ~="cd ~"
alias go="cd"

# git
alias gs="git status"
alias gib="git init -b"
alias gi="git init"
alias ga="git add -A"
alias gcv="git commit -v"
alias gc="git commit -m"
alias gcv!="git commit -v --amend --no-edit"
alias gl="git pull"
alias gp="git push"
alias gp!="git push --force"
alias gcl="git clone --depth 1 --single-branch"
alias gf="git fetch --all"
alias gb="git branch"
alias gr="git rebase"
alias gt='cd "$(git rev-parse --show-toplevel)"'
alias gra="git remote add"
alias gr="git remote"
alias grr="git remote rm"
alias grsu="git remote set-url"
alias gco="git checkout"
alias grs="git reset"
alias gon="git open"

# system
alias cls="clear"
alias rzh="rm -rf $HOME/.zsh/.zsh_history"
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
alias y="yazi" 
alias cpp="copypath" 
alias gp="grep"

# utils
alias g="z"
alias gay="$HOME/suckless/scripts/gay.sh"
alias nzsh="nvim ~/.zshrc"
alias szsh="nvim ~/.zshrc"
alias matrix="unimatrix -b -s 95  -c blue"
alias neo="$HOME/.config/neofetch/.startFetch.sh"
alias fetch="$HOME/.suckless/scripts/fetch.sh"
alias pwall="$HOME/.suckless/scripts/PicWall.sh"
alias clock="peaclock"
alias goo="/usr/bin/go"
