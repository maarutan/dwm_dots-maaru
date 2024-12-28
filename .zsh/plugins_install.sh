#!/bin/sh

PLUGIN_DIR="${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/plugins"
THEME_DIR="${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/themes"

PLUGINS=(
    "https://github.com/zdharma-continuum/fast-syntax-highlighting"
    "https://github.com/djui/alias-tips"
    "https://github.com/Aloxaf/fzf-tab"
    "https://github.com/paulirish/git-open"
    "https://github.com/zsh-users/zsh-autosuggestions"
    "https://github.com/zsh-users/zsh-completions"
    "https://github.com/joel-porquet/zsh-dircolors-solarized"
    "https://github.com/zsh-users/zsh-history-substring-search"
)

THEME="https://github.com/romkatv/powerlevel10k"

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

install_theme() {
    local repo_url=$1
    local theme_name=$(basename "$repo_url" .git)
    local theme_path="${THEME_DIR}/${theme_name}"

    if [ -d "$theme_path" ]; then
        echo "Theme '${theme_name}' is already installed."
    else
        echo "Cloning theme '${theme_name}'..."
        if git clone "$repo_url" "$theme_path"; then
            echo "Successfully cloned theme '${theme_name}'."
        else
            echo "Failed to clone theme '${theme_name}'. Please check the repository URL or your network connection."
        fi
    fi
}

# Ensure plugin and theme directories exist
mkdir -p "$PLUGIN_DIR"
mkdir -p "$THEME_DIR"

# Install plugins
for repo in "${PLUGINS[@]}"; do
    clone_plugin "$repo"
done

# Install theme
install_theme "$THEME"
echo "Plugin and theme installation complete."
sleep 1
source ~/.zshrc
