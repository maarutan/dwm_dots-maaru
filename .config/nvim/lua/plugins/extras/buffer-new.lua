local M = {}

function M.create_new_buffer()
	local new_name = vim.fn.input("New file name: ", "")
	if new_name == "" then
		vim.notify("Buffer creation canceled.", vim.log.levels.WARN, {
			icon = "ℹ️",
			title = "NewBuffer",
		})
		return
	end

	if vim.fn.filereadable(new_name) == 1 then
		vim.notify("Error: File already exists.", vim.log.levels.ERROR, {
			icon = "🚨",
			title = "NewBuffer",
		})
		return
	end

	local ok, err = pcall(function()
		vim.cmd("edit " .. new_name)
		vim.cmd("setlocal buftype=")
	end)

	if not ok then
		vim.notify("Error creating buffer: " .. err, vim.log.levels.ERROR, {
			icon = "🚨",
			title = "NewBuffer",
		})
		return
	end

	vim.notify("New buffer successfully created: " .. new_name, vim.log.levels.WARN, {
		icon = "✅",
		title = "NewBuffer",
	})
end

vim.api.nvim_create_user_command("NewBuffer", function()
	M.create_new_buffer()
end, { desc = "Create a new buffer and associate with a file" })

vim.keymap.set("n", "<Leader>bn", function()
	M.create_new_buffer()
end, { noremap = true, silent = true, desc = "Create new buffer" })

return M
