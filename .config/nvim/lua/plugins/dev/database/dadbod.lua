---- data base ----

return {
	{
		"kristijanhusak/vim-dadbod-ui",
		init = function()
			-- vim.g.db_ui_win_position = "right"
			vim.g.db_ui_use_nerd_fonts = 1
			vim.g.db_ui_disable_info_notifications = 1

			local api = vim.api
			local counter = 0

			local function setup_dbui_keymap()
				local bufnr = api.nvim_get_current_buf()
				local bufname = api.nvim_buf_get_name(bufnr)

				if bufname:match("dbui") then
					local function handle_keypress()
						counter = counter + 1
						if counter == 5 then
							counter = 0
							api.nvim_feedkeys(api.nvim_replace_termcodes("<Left>", true, false, true), "n", false)
						else
							api.nvim_feedkeys(
								api.nvim_replace_termcodes("<Plug>(DBUI_SelectLine)", true, false, true),
								"n",
								false
							)
						end
					end

					vim.keymap.set("n", "l", handle_keypress, { silent = true, buffer = bufnr })
					vim.keymap.set("n", "h", handle_keypress, { silent = true, buffer = bufnr })
				end
			end

			api.nvim_create_autocmd("BufEnter", {
				pattern = "*",
				callback = function()
					setup_dbui_keymap()
				end,
			})
		end,
	},

	{ "tpope/vim-dadbod" },
	{ "kristijanhusak/vim-dadbod-completion" },
}
