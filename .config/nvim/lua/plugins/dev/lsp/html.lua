local lspconfig = require("lspconfig")

lspconfig.html.setup({
	capabilities = require("cmp_nvim_lsp").default_capabilities(),

	settings = {
		html = {
			validate = true,
			hover = true,
			format = {
				enable = true,
			},
		},
	},

	filetypes = { "html", "htm", "xhtml", "handlebars", "erb", "liquid" },
	root_dir = lspconfig.util.root_pattern("package.json", ".git", "."),
})
