local prettierd = require("plugins.dev.formatting.prettierd")
local prettier = require("plugins.dev.formatting.prettier")
local ruff = require("plugins.dev.formatting.ruff")
local stylua = require("plugins.dev.formatting.stylua")
local beautysh = require("plugins.dev.formatting.beautysh")
local black = require("plugins.dev.formatting.black")
local djlint = require("plugins.dev.formatting.djlint")

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
	},
	------------
	-- djinja --
	------------
	html = { djlint.format },
	django = { djlint.format },
})

----------------------------
------ format on save ------
vim.api.nvim_exec(
	[[
augroup FormatAutogroup
  autocmd!
  autocmd BufWritePost * FormatWrite | w!
augroup END
]],
	true
)
----------------------------
