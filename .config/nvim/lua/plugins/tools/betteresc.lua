require("better_escape").setup({
	timeout = 200,
	mappings = {
		i = {
			j = {
				k = function()
					local filetype = { "terminal", "term", "toggleterm", "yazi" }
					if vim.bo.filetype == filetype then
						-- Type 'jk' normally when inside filetype 'Yourfiletype'
						-- <c-v> is used to avoid mappings
						return "<c-v>j<c-v>k"
					end
					return "<esc>"
				end,
			},
		},
		t = {
			j = {
				k = function()
					-- Escape insert mode when jk is pressed
					local filetype = { "terminal", "term", "toggleterm", "yazi" }
					if vim.bo.filetype == filetype then
						return "<c-v>j<c-v>k"
					end
					return "<esc>"
				end,
				-- k = "<Esc>",
			},
		},
	},
})

-- vim.keymap.set("i", "jk", "<Esc>", { noremap = true, silent = true })
