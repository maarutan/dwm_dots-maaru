# ██╗  ██╗███████╗██╗   ██╗███╗   ███╗ █████╗ ██████╗
# ██║ ██╔╝██╔════╝╚██╗ ██╔╝████╗ ████║██╔══██╗██╔══██╗
# █████╔╝ █████╗   ╚████╔╝ ██╔████╔██║███████║██████╔╝
# ██╔═██╗ ██╔══╝    ╚██╔╝  ██║╚██╔╝██║██╔══██║██╔═══╝
# ██║  ██╗███████╗   ██║   ██║ ╚═╝ ██║██║  ██║██║
# ╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝
#
bindkey "^W" backward-kill-word
bindkey "^?" backward-delete-char

bindkey '^N' history-beginning-search-forward # ctrl + n
bindkey '^P' history-beginning-search-backward # ctrl + p

# complete
bindkey "^I" fzf-tab-complete # tab
bindkey "^[[105;5u"  autosuggest-accept # ctrl + i


#fzf history
bindkey '^H' fzf_history_search # ctrl + h


# abbr
bindkey ' ' expand-abbr  # space
bindkey '^M' smart_enter # retrun | enter
bindkey '^ ' magic-space # ctrl + space

# sudo
bindkey '^R' add_sudo_to_start
