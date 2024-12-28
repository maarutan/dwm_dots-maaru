-- lua/devlangs/formatters/prettier.lua
local null_ls = require("null-ls")
return null_ls.builtins.formatting.prettierd.with({
	filetypes = {
		"javascript",
		"javascriptreact",
		"typescript",
		"typescriptreact",
		"jsx",
		"tsx",
		"json",
		-- "html",
		"css",
		"scss",
		"markdown",
		"yaml",
		"vue",
		"graphql",
	},
})
