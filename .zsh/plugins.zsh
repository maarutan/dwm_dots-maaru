# ██████╗ ██╗     ██╗   ██╗ ██████╗ ██╗███╗   ██╗███████╗
# ██╔══██╗██║     ██║   ██║██╔════╝ ██║████╗  ██║██╔════╝
# ██████╔╝██║     ██║   ██║██║  ███╗██║██╔██╗ ██║███████╗
# ██╔═══╝ ██║     ██║   ██║██║   ██║██║██║╚██╗██║╚════██║
# ██║     ███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║███████║
# ╚═╝     ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝

# Zinit Plugins
source "$HOME/.local/share/zinit/zinit.git/zinit.zsh"

zinit light zsh-users/zsh-autosuggestions
# zinit light nixpulvis/zsh-error-correct 
zinit snippet OMZ::plugins/git
zinit light agkozak/zsh-z
zinit light Aloxaf/fzf-tab
zinit light zsh-users/zsh-completions
zinit light djui/alias-tips
zinit light zdharma-continuum/fast-syntax-highlighting
zinit light zsh-users/zsh-history-substring-search
zinit light seebi/dircolors-solarized
zinit light paulirish/git-open

############
#   init   #
############

# user scripts
for file in $HOME/.zsh/plugins/*.zsh; do
    source "$file"
done



