vim.keymap.set("n", "<leader>lm", ":Mason<CR>")

------------------
--- Mason Setup ---
------------------

require("mason").setup({
	ui = {
		width = 120,
		height = 28,
		border = "double",
		icons = {
			package_installed = "󰄲  ",
			package_pending = "   ",
			package_uninstalled = "  ",
		},
	},
})
----------------------
--- Tool Installer ---
----------------------

require("mason-tool-installer").setup({
	ensure_installed = {
		--- LSP (Language Servers) ---
		"bash-language-server", -- Bash
		"django-template-lsp", -- Django Templates
		"html-lsp", -- HTML
		"emmet-ls", -- Emmet
		"css-lsp", -- CSS
		"clangd", -- C/C++
		"lua-language-server", -- Lua
		"marksman", -- Markdown
		"yaml-language-server", -- YAML
		"json-lsp", -- JSON
		"typescript-language-server", -- TypeScript/JavaScript
		"sqlls", -- SQL
		"taplo", -- TOML

		--- Linters ---
		"beautysh", -- Shell scripts
		"cpplint", -- C/C++
		"djlint", -- Django templates
		"eslint_d", -- JavaScript/TypeScript
		"htmlhint", -- HTML
		"markdownlint", -- Markdown
		"pyright", -- Python (also acts as an LSP)
		"ruff", -- Python
		"selene", -- Lua
		"shellcheck", -- Shell scripts
		"stylelint", -- CSS
		"yamllint", -- YAML

		--- Formatters ---
		"black", -- Python
		"prettier", -- General-purpose (JS, CSS, HTML)
		"prettierd", -- Lightweight Prettier
		"stylua", -- Lua
	},
	auto_update = true, -- Automatically update tools
	run_on_start = true, -- Install tools on startup
})
