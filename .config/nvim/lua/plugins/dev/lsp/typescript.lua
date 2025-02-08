local lspconfig = require("lspconfig")

lspconfig.ts_ls.setup({
	capabilities = require("cmp_nvim_lsp").default_capabilities(),
	on_attach = function(client, bufnr)
		client.server_capabilities.documentFormattingProvider = false

		print("TypeScript LSP attached " .. bufnr)
	end,
	settings = {
		javascript = {
			format = {
				semicolons = "insert",
			},
		},
		typescript = {
			format = {
				semicolons = "insert",
			},
		},
	},
	filetypes = {
		"typescript",
		"javascript",
		"typescriptreact",
		"javascriptreact",
		"javascript.jsx",
		"typescript.tsx",
	},
})
