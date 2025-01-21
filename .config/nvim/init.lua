----------
-- core --
----------
--------------------------------
require("core.keymaps")
require("core.options")
require("core.lazyplug.config")

require("core.colorscheme")
require("core.gui")
-------------
-- PLUGINS --
-------------
--------------------------------
-- tools
require("plugins.tools.nocut")
require("plugins.tools.betteresc")
require("plugins.tools.cmp")
require("plugins.tools.codeium")
require("plugins.tools.coderunner")
require("plugins.tools.comments")
require("plugins.tools.hop")
require("plugins.tools.kitty-clipboard")
require("plugins.tools.lazygit")
require("plugins.tools.lifeshare")
require("plugins.tools.lorem")
require("plugins.tools.multicursor")
require("plugins.tools.neotree")
require("plugins.tools.renamer")
require("plugins.tools.scope")
require("plugins.tools.surround")
require("plugins.tools.telescope")
require("plugins.tools.terminal")
require("plugins.tools.treesitter")
require("plugins.tools.yazinvim")
require("plugins.tools.autotag")
require("plugins.tools.autopairs")
require("plugins.tools.splitResizer")
require("plugins.tools.eyeliner")
require("plugins.tools.gitgraph")
require("plugins.tools.ddifview")

-- ui
require("plugins.ui.cinnamon")
require("plugins.ui.neoscroll")
require("plugins.ui.colorizer")
require("plugins.ui.image")
require("plugins.ui.noice")
require("plugins.ui.dashboard")
require("plugins.ui.gitsing")
require("plugins.ui.illuminate")
require("plugins.ui.indentLine")
require("plugins.ui.keycalm")
require("plugins.ui.lualine")
require("plugins.ui.macros-notify")
require("plugins.ui.matchup")
require("plugins.ui.mini")
require("plugins.ui.notify")
require("plugins.ui.pacman_anims")
require("plugins.ui.scrollview")
require("plugins.ui.smoothcursor")
require("plugins.ui.todo")
require("plugins.ui.treesitter-context")
require("plugins.ui.whichkey")
require("plugins.ui.bufferline")
require("plugins.ui.DayOrNight")
require("plugins.ui.lspsaga")
require("plugins.ui.lspkind")
require("plugins.ui.rainbow")
require("plugins.ui.whichkey")
require("plugins.ui.minimap")
require("plugins.ui.beacon")
-- require("plugins.ui.cursor-anims")
require("plugins.ui.space")

-- snippets
require("plugins.snippets.snippets")
require("plugins.snippets.pyright")
require("plugins.snippets.config")

-- extras
require("plugins.extras.buffer-del")
require("plugins.extras.buffer-name")
require("plugins.extras.buffer-new")
require("plugins.extras.whoami")
require("plugins.extras.showfile")
require("plugins.extras.floutBuffer")
require("plugins.extras.tabs")

-- dev
require("plugins.dev.config")
