local lspconfig = require("lspconfig")
local cmp_nvim_lsp = require("cmp_nvim_lsp")

local capabilities = cmp_nvim_lsp.default_capabilities()

lspconfig.jsonls.setup({
	capabilities = capabilities,
	settings = {
		json = {
			schemas = {
				{
					description = "Package.json schema",
					fileMatch = { "package.json" },
					url = "https://json.schemastore.org/package.json",
				},
				{
					description = "ESLint config schema",
					fileMatch = { ".eslintrc.json", ".eslintrc" },
					url = "https://json.schemastore.org/eslintrc.json",
				},
				{
					description = "Prettier config schema",
					fileMatch = { ".prettierrc", ".prettierrc.json", "prettier.config.json" },
					url = "https://json.schemastore.org/prettierrc",
				},
				{
					description = "TypeScript config schema",
					fileMatch = { "tsconfig.json", "tsconfig.*.json" },
					url = "https://json.schemastore.org/tsconfig.json",
				},
			},
			validate = { enable = true },
		},
	},
})
