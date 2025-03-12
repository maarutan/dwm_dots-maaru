require("illuminate").configure({
	providers = {
		"regex",
	},
	delay = 200,
	under_cursor = true,
	filetypes_denylist = {
		"neo-tree",
		"dashboard",
		"help",
		"toggleterm",
		"gitgraph",
	},
})
