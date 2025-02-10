--Telescope configuration
local telescope = require("telescope")
local builtin = require("telescope.builtin")
telescope.load_extension("notify")
telescope.load_extension("file_browser")
telescope.load_extension("undo")
local actions = require("telescope.actions")
local action_state = require("telescope.actions.state")

-- Main key bindings
vim.keymap.set("n", "<leader>ff", builtin.find_files, { desc = "Find files" })
vim.keymap.set("n", "<leader>fb", builtin.buffers, { desc = "Open buffers" })
vim.keymap.set("n", "<leader>fw", builtin.live_grep, { desc = "Search text" })
vim.keymap.set("n", "<leader>fh", builtin.help_tags, { desc = "Help tags" })

vim.api.nvim_set_keymap(
	"n",
	"<leader>df",
	"<cmd>Telescope diagnostics bufnr=0<CR>",
	{ desc = "diagnostics file", noremap = true, silent = true }
)
vim.api.nvim_set_keymap(
	"n",
	"<leader>da",
	"<cmd>Telescope diagnostics<CR>",
	{ desc = "diagnostics all", noremap = true, silent = true }
)

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
vim.keymap.set("n", "<leader>fu", "<cmd>Telescope undo<CR>", { desc = "󰣜 Open undo tree" })
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

vim.keymap.set("n", "<leader>fd", open_file_browser, { desc = "Open file_browser" })

-- Custom function to move selection up by 4 items
local function custom_move_selection_previous(prompt_bufnr)
	local picker = action_state.get_current_picker(prompt_bufnr)
	for _ = 1, 4 do
		actions.move_selection_previous(prompt_bufnr)
	end
end

-- Custom function to move selection down by 4 items
local function custom_move_selection_next(prompt_bufnr)
	local picker = action_state.get_current_picker(prompt_bufnr)
	for _ = 1, 4 do
		actions.move_selection_next(prompt_bufnr)
	end
end

local function custom_set_prompt_to_selection(prompt_bufnr)
	local picker = action_state.get_current_picker(prompt_bufnr)
	local entry = action_state.get_selected_entry()
	if entry then
		picker:set_prompt(entry.value)
	else
		print("No selection available")
	end
end
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

		-- initial_mode = "normal",

		layout_config = {
			preview_width = 0.5, -- window size (50% from width)
		},
		layout_strategy = "horizontal",
		mappings = {
			i = {
				["<C-u>"] = custom_move_selection_previous,
				["<C-d>"] = custom_move_selection_next,
				["<A-u>"] = actions.preview_scrolling_up,
				["<A-d>"] = actions.preview_scrolling_down,
				["<C-j>"] = actions.move_selection_next,
				["<C-k>"] = actions.move_selection_previous,
				["<C-l>"] = custom_set_prompt_to_selection,
			},
			n = {
				["<C-u>"] = custom_move_selection_previous,
				["<C-d>"] = custom_move_selection_next,
				["<A-u>"] = actions.preview_scrolling_up,
				["<A-d>"] = actions.preview_scrolling_down,
				["<C-j>"] = actions.move_selection_next,
				["<C-k>"] = actions.move_selection_previous,
				["<C-l>"] = custom_set_prompt_to_selection,
			},
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

function _G.check_diagnostics(bufnr)
	local diagnostics = vim.diagnostic.get(bufnr)
	if #diagnostics == 0 then
		vim.notify("No diagnostics found", vim.log.levels.WARN)
		return false
	end
	return true
end

function _G.check_project_diagnostics()
	local diagnostics = vim.diagnostic.get()
	if #diagnostics == 0 then
		vim.notify("No diagnostics found", vim.log.levels.WARN)
		return false
	end
	return true
end

vim.api.nvim_set_keymap(
	"n",
	"<leader>df",
	"<cmd>lua if _G.check_diagnostics(0) then require('telescope.builtin').diagnostics({ bufnr = 0 }) end<CR>",
	{ desc = "Diagnostics for current file", noremap = true, silent = true }
)

vim.api.nvim_set_keymap(
	"n",
	"<leader>da",
	"<cmd>lua if _G.check_project_diagnostics() then require('telescope.builtin').diagnostics() end<CR>",
	{ desc = "Diagnostics for entire project", noremap = true, silent = true }
)

vim.keymap.set("n", "<leader>fR", function()
	local action_state = require("telescope.actions.state")
	local telescope = require("telescope.builtin")

	telescope.oldfiles({
		attach_mappings = function(prompt_bufnr, map)
			local function open_and_change_dir()
				local selection = action_state.get_selected_entry()
				if not selection then
					print("[Telescope] No selection")
					return
				end
				local filepath = selection.path or selection.filename
				if filepath then
					local dir = vim.fn.fnamemodify(filepath, ":h")
					vim.cmd("cd " .. dir)
					vim.cmd("e! " .. filepath)
				end
				vim.cmd("Bdelete " .. prompt_bufnr)
			end

			map("i", "<CR>", open_and_change_dir)
			map("n", "<CR>", open_and_change_dir)
			return true
		end,
	})
end, { noremap = true, silent = true, desc = "Open Recent Files and change directory" })

vim.api.nvim_set_keymap(
	"n",
	"<leader>fr",
	"<cmd>Telescope oldfiles<CR>",
	{ desc = "Open Recent Files", noremap = true, silent = true }
)
