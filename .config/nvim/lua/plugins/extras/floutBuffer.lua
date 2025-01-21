_G.focus_on_flout_buffer = function()
	local float_windows = vim.api.nvim_list_wins()
	for _, win in ipairs(float_windows) do
		if vim.api.nvim_win_get_config(win).relative ~= "" then
			vim.api.nvim_set_current_win(win)
			return
		end
	end
	vim.notify("No diagnostic window found.", vim.log.levels.WARN)
end

vim.api.nvim_set_keymap(
	"n",
	"<leader>bf",
	"<cmd>lua focus_on_flout_buffer()<CR>",
	{ noremap = true, silent = true, desc = "Focus on flout buffer" }
)
