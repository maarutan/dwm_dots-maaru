--Telescope configuration
local telescope = require("telescope")
local builtin = require("telescope.builtin")

-- Main key bindings
vim.keymap.set("n", "<leader>ff", builtin.find_files, { desc = " Find files" })
vim.keymap.set("n", "<leader>fb", builtin.buffers, { desc = " Open buffers" })
vim.keymap.set("n", "<leader>fw", builtin.live_grep, { desc = " Search text" })
vim.keymap.set("n", "<leader>fh", builtin.help_tags, { desc = " Help tags" })

-- Check for .git directory
local function check_git_and_run(callback)
	if vim.fn.isdirectory(".git") == 1 then
		callback()
	else
		vim.notify("No Git repository found", vim.log.levels.WARN, {
			title = "Git",
			icon = "󰊢",
		})
	end
end

-- Git key bindings
vim.keymap.set("n", "<leader>gb", function()
	check_git_and_run(builtin.git_branches)
end, { desc = "Git branches" })

vim.keymap.set("n", "<leader>gc", function()
	check_git_and_run(builtin.git_commits)
end, { desc = "Git commits" })

vim.keymap.set("n", "<leader>gs", function()
	check_git_and_run(builtin.git_status)
end, { desc = "Git status" })

-- Additional functions
vim.keymap.set("n", "<leader>cs", builtin.colorscheme, {
	desc = " Select colorscheme",
})
vim.keymap.set("n", "<leader>u", "<cmd>Telescope undo<CR>", { desc = "󰣜 Open undo tree" })
vim.keymap.set("n", "<leader>fn", "<cmd>Telescope notify<CR>", { desc = "󰍡 Notification history" })

local function open_file_browser()
	telescope.extensions.file_browser.file_browser({
		prompt_title = "Select Directory",
		cwd = vim.fn.getcwd(),
		attach_mappings = function(_, map)
			local actions = require("telescope.actions")
			local action_state = require("telescope.actions.state")
			map("i", "<CR>", function(prompt_bufnr)
				local selected_path = action_state.get_selected_entry().path
				actions.close(prompt_bufnr)
				vim.cmd("cd " .. selected_path)
				vim.cmd("edit .")
			end)
			return true
		end,
	})
end

vim.keymap.set("n", "<leader>wd", open_file_browser, { desc = "Open file_browser" })

-- Telescope setup

telescope.setup({
	defaults = {
		file_ignore_patterns = {
			"%.png",
			"%.jpg",
			"%.jpeg",
			"%.gif",
			"%.bmp",
			"%.svg",
			"%.webp",
			"%.mp4",
			"%.mkv",
			"%.avi",
			"%.mov",
			"%.flv",
			"%.wmv",
			"%.webm",
			"%.m4v",
		},
	},
	extensions = {
		undo = {
			side_by_side = true,
			layout_strategy = "vertical",
			layout_config = { preview_height = 0.8 },
			use_delta = true,
			mappings = {
				i = {
					["<CR>"] = require("telescope-undo.actions").yank_additions,
					["<S-CR>"] = require("telescope-undo.actions").yank_deletions,
				},
				n = {
					["<CR>"] = require("telescope-undo.actions").restore,
					["<S-CR>"] = require("telescope-undo.actions").yank_deletions,
				},
			},
		},
	},
})

-- Load Telescope extensions
telescope.load_extension("notify")
telescope.load_extension("file_browser")
telescope.load_extension("undo")
