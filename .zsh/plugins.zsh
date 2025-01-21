# ██████╗ ██╗     ██╗   ██╗ ██████╗ ██╗███╗   ██╗███████╗
# ██╔══██╗██║     ██║   ██║██╔════╝ ██║████╗  ██║██╔════╝
# ██████╔╝██║     ██║   ██║██║  ███╗██║██╔██╗ ██║███████╗
# ██╔═══╝ ██║     ██║   ██║██║   ██║██║██║╚██╗██║╚════██║
# ██║     ███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║███████║
# ╚═╝     ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝

# Zinit Plugins
source "$HOME/.local/share/zinit/zinit.git/zinit.zsh"

# fast run load now
zinit light Aloxaf/fzf-tab
zinit light zsh-users/zsh-autosuggestions

# fast run load later
zinit wait lucid for agkozak/zsh-z
zinit wait lucid for zsh-users/zsh-completions
zinit wait lucid for djui/alias-tips
zinit wait lucid for zsh-users/zsh-history-substring-search
zinit wait lucid for seebi/dircolors-solarized
zinit wait lucid for paulirish/git-open
zinit wait lucid for MichaelAquilina/zsh-auto-notify

#run load
zinit wait lucid for zdharma-continuum/fast-syntax-highlighting
zinit wait lucid for hlissner/zsh-autopair


############
#   init   #
############
typeset -A ZSH_HIGHLIGHT_REGEXP
ZSH_HIGHLIGHT_REGEXP+=('[0-9]' fg=cyan)
ZSH_HIGHLIGHT_HIGHLIGHTERS+=(main regexp)

# user scripts
for file in $HOME/.zsh/plugins/*.zsh; do
    source "$file"
done



