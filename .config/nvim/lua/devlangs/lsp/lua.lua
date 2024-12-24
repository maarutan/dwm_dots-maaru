local lspconfig = require("lspconfig")

-- Проверяем, активен ли Lua LSP
if not lspconfig.lua_ls.manager then
	lspconfig.lua_ls.setup({
		capabilities = require("cmp_nvim_lsp").default_capabilities(),
		settings = {
			Lua = {
				runtime = {
					version = "LuaJIT",
					path = vim.split(package.path, ";"),
				},
				diagnostics = {
					globals = { "vim" },
				},
				workspace = {
					library = vim.api.nvim_get_runtime_file("", true),
					checkThirdParty = false,
				},
				telemetry = {
					enable = false,
				},
			},
		},
	})
end
