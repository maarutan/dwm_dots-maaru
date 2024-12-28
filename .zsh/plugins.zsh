# ██████╗ ██╗     ██╗   ██╗ ██████╗ ██╗███╗   ██╗███████╗
# ██╔══██╗██║     ██║   ██║██╔════╝ ██║████╗  ██║██╔════╝
# ██████╔╝██║     ██║   ██║██║  ███╗██║██╔██╗ ██║███████╗
# ██╔═══╝ ██║     ██║   ██║██║   ██║██║██║╚██╗██║╚════██║
# ██║     ███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║███████║
# ╚═╝     ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝
# 
plugins=(
    git
    zsh-autosuggestions
    z
    fzf-tab
    zsh-completions
    alias-tips
    fast-syntax-highlighting
    zsh-history-substring-search
    zsh-dircolors-solarized
    git-open
    sudo
    copypath
)


############
#   init   #
############

for file in $HOME/.zsh/plugins/*.zsh; do
    source "$file"
done;
