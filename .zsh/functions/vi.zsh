bindkey -v 
zle-keymap-select() {
    if [[ $KEYMAP == vicmd ]]; then
        echo -n "⭠ Normal Mode"
    fi
}

zle -N zle-keymap-select

# Настройка jk как Esc
bindkey -M viins 'jk' vi-cmd-mode

