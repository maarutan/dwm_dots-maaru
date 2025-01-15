function custom_fzf_tab_directory_only() {
    if [[ -z "$BUFFER" ]]; then
        local dir
        dir=$(find . -mindepth 1 -maxdepth 1 -type d ! -name ".*" -print 2> /dev/null | fzf \
                --preview 'eza --tree --level=1 --icons {}' \
                --preview-window=right:50%:wrap \
                --height=70% \
                --border \
                --color=fg:#cdd6f4,hl:#a6e3a1,fg+:#cdd6f4,bg+:#45475a,hl+:#f38ba8 \
            --color=info:#89b4fa,prompt:#f5c2e7,pointer:#f38ba8,marker:#fab387,spinner:#94e2d5,border:#585b70)
        if [[ -n "$dir" ]]; then
            BUFFER="${dir/#.\//}"
            zle end-of-line
        fi
    else
        if [[ "$BUFFER" == *.* ]]; then
            local dir
            dir=$(find . -mindepth 1 -maxdepth 1 -type d -print 2> /dev/null | fzf \
                    --preview 'eza --tree --level=1 --icons {}' \
                    --preview-window=right:50%:wrap \
                    --height=70% \
                    --border \
                    --color=fg:#cdd6f4,hl:#a6e3a1,fg+:#cdd6f4,bg+:#45475a,hl+:#f38ba8 \
                --color=info:#89b4fa,prompt:#f5c2e7,pointer:#f38ba8,marker:#fab387,spinner:#94e2d5,border:#585b70)
            if [[ -n "$dir" ]]; then
                BUFFER="${dir/#.\//}"
                zle end-of-line
            fi
        else
            zle expand-or-complete
        fi
    fi
}

zle -N custom_fzf_tab_directory_only
bindkey '^E' custom_fzf_tab_directory_only

