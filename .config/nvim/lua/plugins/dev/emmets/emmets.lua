local lspconfig = require("lspconfig")

lspconfig.emmet_ls.setup({
	filetypes = { "html", "css", "javascriptreact", "typescriptreact", "vue", "blade.php" },

	init_options = {
		emmet = {
			showExpandedAbbreviation = "always",
			showAbbreviationSuggestions = true,
			showSuggestionsAsSnippets = true,
		},
	},
})
