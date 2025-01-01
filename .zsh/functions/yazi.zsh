function yazi() {
    local tmp="$(mktemp -t "yazi-cwd.XXXXXX")"
    command yazi --cwd-file="$tmp"
    
    if cwd="$(cat -- "$tmp")" && [ -n "$cwd" ] && [ "$cwd" != "$PWD" ]; then
        builtin cd -- "$cwd"
    fi

    rm -f -- "$tmp"
}

if [[ -n "$YAZI_ID" ]]; then
	function _yazi_cd() {
		ya emit cd "$PWD"
	}
	add-zsh-hook zshexit _yazi_cd
fi
