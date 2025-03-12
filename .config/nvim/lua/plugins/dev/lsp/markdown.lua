local lspconfig = require("lspconfig")
local cmp_nvim_lsp = require("cmp_nvim_lsp")

local capabilities = cmp_nvim_lsp.default_capabilities()

lspconfig.marksman.setup({
	capabilities = capabilities,
	settings = {
		marksman = {
			workingDirectory = { mode = "auto" },
		},
	},
})
