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


# eva
eval "$(zoxide init zsh)"

# Load NVM
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion
