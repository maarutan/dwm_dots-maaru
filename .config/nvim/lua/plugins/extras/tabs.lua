local tabs_on_4 = {
	"python",
	"lua",
	"bash",
	"sh",
	"zsh",
	"c",
	"cpp",
	"cmake",
	"haskell",
	"rust",
}

local tabs_on_2 = {
	"html",
	"css",
	"javascript",
	"tsx",
	"jsx",
	"markdown",
	"md",
	"json",
	"jsonc",
	"yaml",
	"toml",
}

-- tabs on 4
vim.api.nvim_create_autocmd("FileType", {
	pattern = tabs_on_4,
	callback = function()
		vim.opt_local.tabstop = 4
		vim.opt_local.shiftwidth = 4
		vim.opt_local.expandtab = true
	end,
})

-- tabs on 2
vim.api.nvim_create_autocmd("FileType", {
	pattern = tabs_on_2,
	callback = function()
		vim.opt_local.tabstop = 2
		vim.opt_local.shiftwidth = 2
		vim.opt_local.expandtab = true
	end,
})
