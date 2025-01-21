local cmp = require("cmp")
local luasnip = require("luasnip")
local lspkind = require("lspkind")

cmp.setup({
	snippet = {
		expand = function(args)
			luasnip.lsp_expand(args.body)
		end,
	},

	mapping = {
		-- C-Space: Toggle autocomplete menu
		["<C-Space>"] = cmp.mapping(function(fallback)
			if cmp.visible() then
				cmp.close() -- Close the autocomplete menu
			else
				cmp.complete() -- Open the autocomplete menu and select the first item
				cmp.select_next_item({ behavior = cmp.SelectBehavior.Select })
			end
		end, { "i", "c" }),

		-- C-e: Close autocomplete menu
		["<C-e>"] = cmp.mapping.close(),

		-- Tab / Shift-Tab: Confirm or navigate snippets
		["<Tab>"] = cmp.mapping(function(fallback)
			if cmp.visible() then
				cmp.select_next_item({ behavior = cmp.SelectBehavior.Select }) -- Navigate to the next item
			elseif luasnip.expand_or_jumpable() then
				luasnip.expand_or_jump() -- Expand snippet or jump forward
			else
				fallback() -- Default behavior
			end
		end, { "i", "s" }),

		["<S-Tab>"] = cmp.mapping(function(fallback)
			if luasnip.jumpable(-1) then
				luasnip.jump(-1) -- Jump backward in snippet
			else
				fallback() -- Default behavior
			end
		end, { "i", "s" }),

		-- C-j / C-k: Navigate autocomplete suggestions
		["<C-j>"] = cmp.mapping.select_next_item({ behavior = cmp.SelectBehavior.Select }),
		["<C-k>"] = cmp.mapping.select_prev_item({ behavior = cmp.SelectBehavior.Select }),

		-- C-d / C-u: Scroll through autocomplete menu in larger steps
		["<C-d>"] = cmp.mapping(function(fallback)
			cmp.select_next_item({ behavior = cmp.SelectBehavior.Select, count = 4 })
		end, { "i", "c" }),

		["<C-u>"] = cmp.mapping(function(fallback)
			cmp.select_prev_item({ behavior = cmp.SelectBehavior.Select, count = 4 })
		end, { "i", "c" }),

		-- A-u / A-d: Switch focus to documentation popup and scroll
		["<A-u>"] = cmp.mapping.scroll_docs(-4),
		["<A-d>"] = cmp.mapping.scroll_docs(4),

		-- Confirm selection with Enter, C-l, or C-Return
		["<CR>"] = cmp.mapping.confirm({ select = true, behavior = cmp.ConfirmBehavior.Replace }), -- Confirm only on manual confirmation
		["<C-l>"] = cmp.mapping.confirm({ select = true, behavior = cmp.ConfirmBehavior.Replace }),
		["<C-Return>"] = cmp.mapping.confirm({ select = true, behavior = cmp.ConfirmBehavior.Replace }),
	},

	sources = cmp.config.sources({
		{ name = "vim-dadbod-completion" },
		{ name = "nvim_lsp" },
		{ name = "luasnip" },
		{ name = "buffer" },
		{ name = "path" },
	}),

	window = {
		completion = {
			border = "rounded",
			winhighlight = "Normal:NormalFloat,FloatBorder:FloatBorder,CursorLine:PmenuSel,Search:None",
			col_offset = 4,
		},
		documentation = {
			border = "rounded",
			winhighlight = "Normal:NormalFloat,FloatBorder:FloatBorder,CursorLine:PmenuSel,Search:None",
		},
	},

	formatting = {
		format = lspkind.cmp_format({
			mode = "symbol_text",
			maxwidth = 50,
			ellipsis_char = "...",
			-- menu = {
			-- nvim_lsp = "[LSP]",
			-- luasnip = "[Snippet]",
			-- buffer = "[Buffer]",
			-- path = "[Path]",
			-- },
		}),
	},

	experimental = {
		ghost_text = false,
	},
	cmp.setup.cmdline({ "/", "?" }, {
		mapping = {
			["<C-j>"] = cmp.mapping(function(fallback)
				if cmp.visible() then
					cmp.select_next_item()
				else
					fallback()
				end
			end, { "c" }),

			["<C-k>"] = cmp.mapping(function(fallback)
				if cmp.visible() then
					cmp.select_prev_item()
				else
					fallback()
				end
			end, { "c" }),

			["<CR>"] = cmp.mapping.confirm({ select = true }),
		},
		sources = {
			{ name = "path" },
			{ name = "buffer" },
		},
	}),
})
cmp.setup.cmdline(":", {
	mapping = vim.tbl_extend("force", cmp.mapping.preset.cmdline(), {
		["<C-j>"] = cmp.mapping(function(fallback)
			if cmp.visible() then
				cmp.select_next_item()
			else
				fallback()
			end
		end, { "c" }),

		["<C-k>"] = cmp.mapping(function(fallback)
			if cmp.visible() then
				cmp.select_prev_item()
			else
				fallback()
			end
		end, { "c" }),

		["<CR>"] = cmp.mapping.confirm({ select = true }),
	}),
	sources = cmp.config.sources({
		{ name = "path" },
		{ name = "cmdline" },
	}),
})

--commands
vim.cmd([[
    cnoremap <C-j> <C-n>
    cnoremap <C-k> <C-p>
]])
