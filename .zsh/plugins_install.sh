#!/bin/sh

PLUGIN_DIR="${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/plugins"

clone_plugin() {
    local repo_url=$1
    local plugin_name=$(basename "$repo_url" .git)
    local plugin_path="${PLUGIN_DIR}/${plugin_name}"

    if [ -d "$plugin_path" ]; then
        echo "Plugin '${plugin_name}' is already installed."
    else
        echo "Cloning '${plugin_name}'..."
        if git clone "$repo_url" "$plugin_path"; then
            echo "Successfully cloned '${plugin_name}'."
        else
            echo "Failed to clone '${plugin_name}'. Please check the repository URL or your network connection."
        fi
    fi
}

PLUGINS=(
    "https://github.com/zdharma-continuum/fast-syntax-highlighting"
    "https://github.com/djui/alias-tips.git"
    "https://github.com/Aloxaf/fzf-tab"
    "https://github.com/paulirish/git-open"
    "https://github.com/zsh-users/zsh-autosuggestions"
    "https://github.com/zsh-users/zsh-completions"
    "https://github.com/joel-porquet/zsh-dircolors-solarized"
    "https://github.com/zsh-users/zsh-history-substring-search"
)

mkdir -p "$PLUGIN_DIR"

for repo in "${PLUGINS[@]}"; do
    clone_plugin "$repo"
done

echo "Plugin check and installation complete."
