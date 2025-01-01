local wk = require("which-key")

wk.add({
	{ "<leader>f", group = "Find" },
	{ "<leader>ff", desc = "Find File" },
	{ "<leader>ft", desc = "Find Word" },
	{ "<leader>fb", desc = "Find Buffer" },
	{ "<leader>fh", desc = "Find Help" },
	{ "<leader>fn", desc = "Find Notify" },

	{ "<leader>g", group = "Git" },
	{ "<leader>gb", desc = "Open Branches" },
	{ "<leader>gc", desc = "Open Commits" },
	{ "<leader>gs", desc = "Open Status" },

	{ "<leader>e", desc = "Open Neotree" },
	{ "<leader>t", desc = "Tabs" },
	{ "<leader>u", desc = "Undo" },
	{ "<leader>b", desc = "Buffer" },
	{ "<leader>w", desc = "Tile" },
	{ "<leader>s", desc = "Select" },
	{ "<leader>h", desc = "hop" },
	{ "<leader>sf", desc = "File" },
	{ "<leader>T", desc = "New Buffer and Terminal" },

	{ "<leader>r", group = "R - zone" },
	{ "<leader>rn", desc = "Rename" },

	{ "<leader>l", group = "LSP" },
	{ "<leader>lD", desc = "Declaration" },
	{ "<leader>ld", desc = "Definition" },
	{ "<leader>lk", desc = "Hover" },

	{ "<leader>c", group = "Color Schemes" },
	{ "<leader>cs", desc = "Open" },

	{ "<leader>o", group = "Option" },
	{ "<leader>or", desc = "Relaod config" },
}, { prefix = "<leader>" })
