require("gitgraph").setup({

	layout = "floating", -- Options: "floating", "vertical", "horizontal"
	floating_width = 80, -- Width for floating window (percentage of the screen)
	floating_height = 80, -- Height for floating window (percentage of the screen)
	border = "double", -- Options: "single", "double", "rounded", "solid", "shadow"
	toggle_keymap = "<leader>gi", -- Default keymap for toggling GitGraph
	key_close = "q", -- Keymap to close GitGraph buffer

	symbols = {
		merge_commit = "",
		commit = "",
		merge_commit_end = "",
		commit_end = "",

		-- Advanced symbols
		GVER = "",
		GHOR = "",
		GCLD = "",
		GCRD = "╭",
		GCLU = "",
		GCRU = "",
		GLRU = "",
		GLRD = "",
		GLUD = "",
		GRUD = "",
		GFORKU = "",
		GFORKD = "",
		GRUDCD = "",
		GRUDCU = "",
		GLUDCD = "",
		GLUDCU = "",
		GLRDCL = "",
		GLRDCR = "",
		GLRUCL = "",
		GLRUCR = "",
	},

	hooks = {
		on_select_commit = function(commit)
			log.info("Selected commit:", commit.hash)
		end,
		on_select_range_commit = function(from, to)
			log.info("Selected range:", from.hash, to.hash)
		end,
	},
	format = {
		timestamp = "%H:%M:%S %d-%m-%Y",
		fields = { "hash", "timestamp", "author", "branch_name", "tag" },
	},
	log_level = vim.log.levels.ERROR,
})
