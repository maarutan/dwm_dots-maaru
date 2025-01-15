local M = {}

function M.rename()
	local current_path = vim.fn.expand("%:p")
	if current_path == "" or vim.fn.filereadable(current_path) == 0 then
		vim.notify("Error: File does not exist or is not associated with a buffer.", vim.log.levels.ERROR, {
			icon = "🚨",
			title = "BufferRename",
		})
		return
	end

	local new_name = vim.fn.input("New name for buffer: ", vim.fn.expand("%:t"))
	if new_name == "" or new_name == vim.fn.expand("%:t") then
		vim.notify("Rename canceled.", vim.log.levels.WARN, {
			icon = "ℹ️",
			title = "BufferRename",
		})
		return
	end

	local new_path = vim.fn.fnamemodify(current_path, ":h") .. "/" .. new_name

	local ok, err = os.rename(current_path, new_path)
	if not ok then
		vim.notify("Error renaming file: " .. err, vim.log.levels.ERROR, {
			icon = "🚨",
			title = "BufferRename",
		})
		return
	end

	local current_buf = vim.fn.bufnr("%")

	vim.cmd("edit " .. new_path)

	if vim.fn.bufexists(current_buf) == 1 then
		vim.cmd("bwipeout " .. current_buf)
	end

	vim.notify("File successfully renamed to: " .. new_name, vim.log.levels.WARN, {
		icon = "😄",
		title = "BufferRename",
	})
end

vim.api.nvim_create_user_command("Rename", function()
	M.rename()
end, { desc = "Rename current buffer's file" })

vim.keymap.set("n", "<Leader>br", function()
	M.rename()
end, { noremap = true, silent = true, desc = "Rename buffer" })

return M
