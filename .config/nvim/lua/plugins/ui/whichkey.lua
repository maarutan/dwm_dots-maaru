local wk = require("which-key")

wk.setup({
	preset = "modern", --  "classic" | "modern" | "helix"
})

wk.add({
	{ "<leader>f", group = "Find" },
	{ "<leader>ff", desc = "Find File" },
	{ "<leader>ft", desc = "Find Word" },
	{ "<leader>fb", desc = "Find Buffer" },
	{ "<leader>fh", desc = "Find Help" },
	{ "<leader>fn", desc = "Find Notify" },
	{ "<leader>fr", desc = "Find Recent" },
	{ "<leader>fR", desc = "Find Recent and change directory" },

	{ "<leader>g", group = "Git" },
	{ "<leader>gb", desc = "Open Branches" },
	{ "<leader>gc", desc = "Open Commits" },
	{ "<leader>gs", desc = "Open Status" },
	{ "<leader>gd", desc = "Open Diff View" },

	{ "<leader>m", group = "Map" },
	{ "<leader>mm", desc = "Map Toggle" },
	{ "<leader>mc", desc = "Map Close" },
	{ "<leader>mr", desc = "Map Refresh" },
	{ "<leader>ms", desc = "Map Rescan" },
	{ "<leader>mu", desc = "Map Update Highlight" },

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

	{ "<leader>p", desc = "Postion Cursor" },

	{ "<leader>l", group = "LSP" },
	{ "<leader>ld", desc = "Definition" },
	{ "<leader>lD", desc = "Declaration" },
	{ "<leader>lh", desc = "Hover Doc" },
	{ "<leader>li", desc = "Implementation" },
	{ "<leader>lk", desc = "Hover" },
	{ "<leader>lI", desc = "Info" },
	{ "<leader>lR", desc = "Restart" },
	{ "<leader>lr", desc = "References" },
	{ "<leader>lc", desc = "Code Action" },
	{ "<leader>le", desc = "Open_float" },
	{ "<leader>l[", desc = "Goto Prev" },
	{ "<leader>l]", desc = "Goto Next" },

	{ "<leader>c", group = "Color Schemes" },
	{ "<leader>cs", desc = "Open" },

	{ "<leader>o", group = "Option" },
	{ "<leader>or", desc = "Relaod config" },
}, { prefix = "<leader>" })
