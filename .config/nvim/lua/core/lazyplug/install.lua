return {
	-- color themes
	{ "catppuccin/nvim" },
	{ "ellisonleao/gruvbox.nvim" },
	{ "folke/tokyonight.nvim" },
	{ "rebelot/kanagawa.nvim" },
	{ "mofiqul/vscode.nvim" },
	{ "sainnhe/everforest" },
	{ "binhtran432k/dracula.nvim" },
	--nocut
	{ "maarutan/nvim-nocut" },
	-- treesitter
	{ "nvim-treesitter/nvim-treesitter" },
	-- telescope
	{ "nvim-telescope/telescope.nvim" },
	{ "nvim-lua/plenary.nvim" },
	{ "debugloop/telescope-undo.nvim" },
	{ "nvim-telescope/telescope-file-browser.nvim" },
	-- lua line
	{ "nvim-lualine/lualine.nvim" },
	-- devicons
	{ "nvim-tree/nvim-web-devicons" },
	-- neo tree
	{ "nvim-neo-tree/neo-tree.nvim", branch = "v2.x" },
	-- nvim ui
	{ "MunifTanjim/nui.nvim" },
	-- highlight colors
	{ "brenoprata10/nvim-highlight-colors" },
	-- multi cursor
	{ "maarutan/nvim-visual-multi", branch = "main" },
	-- bufferline
	{ "akinsho/bufferline.nvim" },
	-- smoothcursor
	{ "gen740/smoothcursor.nvim" },
	-- hop move
	{ "hadronized/hop.nvim" },
	-- terminal
	{ "akinsho/toggleterm.nvim" },
	-- noice
	{ "folke/noice.nvim" },
	-- notifysend
	{ "rcarriga/nvim-notify" },
	-- comments
	{ "terrortylor/nvim-comment" },
	-- code runner
	{ "maarutan/betterRun.nvim" },
	-- yazi for nvim
	{ "mikavilpas/yazi.nvim" },
	--todo:
	{ "folke/todo-comments.nvim" },
	-- gitsigns
	{ "lewis6991/gitsigns.nvim" },
	-- cinnamon for cursor
	{ "declancm/cinnamon.nvim" },
	-- neoscroll
	{ "karb94/neoscroll.nvim" },
	-- blankline
	{ "lukas-reineke/indent-blankline.nvim" },
	{ "echasnovski/mini.indentscope" },
	-- context
	{ "nvim-treesitter/nvim-treesitter-context" },
	-- func control
	{ "SmiteshP/nvim-navic" },
	-- lazygit
	{ "kdheepak/lazygit.nvim" },
	-- cmp
	{ "hrsh7th/nvim-cmp" },
	{ "hrsh7th/cmp-nvim-lsp" },
	{ "hrsh7th/cmp-buffer" },
	{ "hrsh7th/cmp-path" },
	{ "hrsh7th/cmp-cmdline" },
	{ "saadparwaiz1/cmp_luasnip" },
	{ "onsails/lspkind-nvim" },
	-- lsp
	{ "neovim/nvim-lspconfig" },
	-- dashboard
	{ "glepnir/dashboard-nvim" },
	-- mason
	{ "williamboman/mason.nvim" },
	{ "WhoIsSethDaniel/mason-tool-installer.nvim" },
	--formatter
	{ "mhartington/formatter.nvim" },
	-- snippets
	{ "L3MON4D3/LuaSnip" },
	{ "rafamadriz/friendly-snippets" },
	-- scope
	{ "tiagovla/scope.nvim" },
	-- scroll view
	{ "dstein64/nvim-scrollview" },
	-- ai code
	{ "Exafunction/codeium.vim" },
	-- bdelete
	{ "famiu/bufdelete.nvim" },
	-- database
	{ require("plugins.dev.database.dadbod") },
	-- matchup
	{ "andymass/vim-matchup" },
	-- illuminate
	{ "RRethy/vim-illuminate" },
	--rename
	{ "filipdutescu/renamer.nvim" },
	--filename
	{ "tpope/vim-eunuch" },
	--pacman animshttps
	{ "maarutan/pacman-anims-nvim" },
	--keycalm
	{ "maarutan/keycalm.nvim" },
	--cursor anims
	{ "echasnovski/mini.animate", version = "*" },
	-- mini animate
	{ "echasnovski/mini.icons", version = "*" },
	--whichkey
	{ "folke/which-key.nvim", event = "VeryLazy" },
	--autopairs
	{ "windwp/nvim-autopairs" },
	--nvim-surround
	{ "kylechui/nvim-surround", version = "*", event = "VeryLazy" },
	--lorem for nvim
	{ "maarutan/lorem.nvim" },
	--smoothcursor
	{ "sphamba/smear-cursor.nvim" },
	--macro notify
	{ "maarutan/macro-notify.nvim" },
	--kitty clipboard mode
	{ "mikesmithgh/kitty-scrollback.nvim" },
	--nvim linting
	{ "mfussenegger/nvim-lint" },
	--quickfix ui for nvim
	{ "kevinhwang91/nvim-bqf" },
	--lspsaga better ui for lsp
	{ "nvimdev/lspsaga.nvim" },
	--auto autotag
	{ "windwp/nvim-ts-autotag" },
	--cmp view lsp
	{ "onsails/lspkind.nvim" },
	--rainbow
	{ "hiphish/rainbow-delimiters.nvim" },
	-- buffResize
	{ "maarutan/splitResizer.nvim" },
	-- eyeliner
	{ "jinh0/eyeliner.nvim" },
	--gitgraph
	{ "maarutan/gitgraph.nvim" },
	-- diffview
	{ "sindrets/diffview.nvim" },
	-- cellular automaton
	{ "Eandrju/cellular-automaton.nvim" },
	--  movengine
	{ "booperlv/nvim-gomove" },
	-- nvim ufo
	{ "kevinhwang91/nvim-ufo", dependencies = "kevinhwang91/promise-async" },
}
