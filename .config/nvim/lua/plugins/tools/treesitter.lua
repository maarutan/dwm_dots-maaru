require("nvim-treesitter.configs").setup({
	ensure_installed = {
		"c",
		"cpp",
		"lua",
		"vim",
		"vimdoc",
		"query",
		"markdown",
		"markdown_inline",
		"python",
		"javascript",
		"typescript",
		"html",
		"css",
		"bash",
		"json",
		"sql",
		"dockerfile",
		"yaml",
		"toml",
		"rust",
		"go",
		"todotxt",
	},
	build = ":TSUpdate",

	matchup = {
		enable = true, -- mandatory, false will disable the whole extension
		disable = { "" }, -- optional, list of languages to be disabled
	},

	sync_install = false,

	auto_install = true,

	ignore_install = { "javascript" },

	highlight = {
		enable = true,
		custom_captures = {
			["keyword"] = "italic",
			["comment"] = "italic",
		},
		-- disable = { "" },

		disable = function(lang, buf)
			local max_filesize = 100 * 1024 -- 100 KB
			local ok, stats = pcall(vim.loop.fs_stat, vim.api.nvim_buf_get_name(buf))
			if ok and stats and stats.size > max_filesize then
				return true
			end
		end,

		additional_vim_regex_highlighting = false,
	},

	indent = {
		enable = true,
	},

	rainbow = {
		enable = true,
		extended_mode = true,
		max_file_lines = 1000,
	},
})
