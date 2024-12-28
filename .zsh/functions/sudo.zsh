add_sudo_to_start() {
    if [[ -n $BUFFER ]]; then
        BUFFER="sudo $BUFFER"
        zle end-of-line
    fi
}
zle -N add_sudo_to_start
bindkey '^R' add_sudo_to_start
