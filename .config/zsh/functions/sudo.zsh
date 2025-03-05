add_sudo_to_start() {
    # If the buffer is empty, initialize it with "sudo"
    if [[ -z $BUFFER ]]; then
        BUFFER="sudo "
        # If the buffer starts with "sudo", remove it
    elif [[ $BUFFER == sudo\ * ]]; then
        BUFFER="${BUFFER#sudo }"
        # Otherwise, add "sudo" to the start of the buffer
    else
        BUFFER="sudo $BUFFER"
    fi
    zle end-of-line
}
zle -N add_sudo_to_start
