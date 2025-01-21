---- data base ----

return {
	{
		"kristijanhusak/vim-dadbod-ui",
		init = function()
			-- vim.g.db_ui_win_position = "right"
			vim.g.db_ui_use_nerd_fonts = 1
			vim.g.db_ui_disable_info_notifications = 1
		end,
	},

	{ "tpope/vim-dadbod" },
	{ "kristijanhusak/vim-dadbod-completion" },
}
