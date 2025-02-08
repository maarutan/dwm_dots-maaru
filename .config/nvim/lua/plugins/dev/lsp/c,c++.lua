require("lspconfig").clangd.setup({
	cmd = { "clangd" },
	filetypes = { "c", "cpp", "objc", "objcpp", "c++" },
	root_dir = require("lspconfig.util").root_pattern("compile_commands.json", ".git"),
	capabilities = require("cmp_nvim_lsp").default_capabilities(),
})
