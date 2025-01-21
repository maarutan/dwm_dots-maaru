local lspconfig = require("lspconfig")
local cmp_nvim_lsp = require("cmp_nvim_lsp")

local capabilities = cmp_nvim_lsp.default_capabilities()

lspconfig.yamlls.setup({
	capabilities = capabilities,
	settings = {
		yaml = {
			schemas = {
				["https://json.schemastore.org/github-workflow.json"] = ".github/workflows/*",
				["https://json.schemastore.org/github-action.json"] = ".github/action.{yml,yaml}",
				["https://json.schemastore.org/kubernetes.json"] = "/*.k8s.yaml",
			},
			validate = true,
			format = { enable = true },
			hover = true,
		},
	},
})
