require("nvim_comment").setup({
	line_mapping = "<leader>cl",
	operator_mapping = "<leader>c",

	----- for sql -----

	hook = function()
		local ft = vim.api.nvim_buf_get_option(0, "filetype")
		if ft == "sql" then
			vim.api.nvim_buf_set_option(0, "commentstring", "-- %s")
		end
	end,

	----- for sql -----
})
