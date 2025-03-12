local cmp_nvim_lsp = require("cmp_nvim_lsp")

require("lspconfig").lua_ls.setup({
	capabilities = cmp_nvim_lsp.default_capabilities(),
	settings = {
		Lua = {
			runtime = {
				version = "LuaJIT",
			},
			diagnostics = {
				globals = { "vim" },
			},
			workspace = {
				library = {
					vim.fn.expand("$VIMRUNTIME"),
					vim.fn.stdpath("config"),
				},
				checkThirdParty = false,
				preloadFileSize = 150,
				ignoreDir = { ".git", "node_modules" },
			},
			telemetry = {
				enable = false,
			},
		},
	},
})
