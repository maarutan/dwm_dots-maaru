local lspconfig = require("lspconfig")

lspconfig.bashls.setup({
	capabilities = require("cmp_nvim_lsp").default_capabilities(),
	on_attach = function(client, bufnr)
		print("Bash lsp connect " .. bufnr)
	end,
	settings = {
		bash = {
			shellcheck = {
				enable = true,
			},
			explainShell = {
				enable = true,
			},
		},
	},
	filetypes = { "sh", "bash", "zsh" },
})
