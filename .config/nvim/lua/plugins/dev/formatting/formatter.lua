local prettierd = require("plugins.dev.formatting.prettierd")
local prettier = require("plugins.dev.formatting.prettier")
local ruff = require("plugins.dev.formatting.ruff")
local stylua = require("plugins.dev.formatting.stylua")
local beautysh = require("plugins.dev.formatting.beautysh")
local black = require("plugins.dev.formatting.black")
local djlint = require("plugins.dev.formatting.djlint")
local clang_format = require("plugins.dev.formatting.clang_format")
local augroup = vim.api.nvim_create_augroup
local autocmd = vim.api.nvim_create_autocmd

require("formatter").setup({
	filetype = {
		---------------
		-- prettierd --
		---------------
		javascript = { prettierd.format },
		typescript = { prettierd.format },
		typescriptreact = { prettierd.format },
		javascriptreact = { prettierd.format },
		html = { prettierd.format },
		css = { prettierd.format },
		json = { prettierd.format },
		markdown = { prettierd.format },

		---------------
		-- prettier --
		---------------
		-- javascript = { prettierd.format },
		-- typescript = { prettierd.format },
		-- typescriptreact = { prettierd.format },
		-- javascriptreact = { prettierd.format },
		-- html = { prettierd.format },
		-- css = { prettierd.format },
		-- json = { prettierd.format },
		-- markdown = { prettierd.format },

		----------
		-- ruff --
		----------
		python = { ruff.format },

		-----------
		-- black --
		-----------
		-- python = { black.format },

		------------
		-- stylua --
		------------
		lua = { stylua.format },

		--------------
		-- beautysh --
		--------------
		sh = { beautysh.format },
		bash = { beautysh.format },
		zsh = { beautysh.format },

		------------
		-- djinja --
		------------
		html = { djlint.format },
		django = { djlint.format },

		------------
		-- c, c++ --
		------------
		c = { clang_format.format },
		cpp = { clang_format.format },
	},
})

----------------------------
------ format on save ------
augroup("__formatter__", { clear = true })
autocmd("BufWritePost", {
	group = "__formatter__",
	command = ":FormatWrite",
})
----------------------------
